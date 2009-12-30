#include <math.h>

#include "game/battlescene.hh"

#include "core/configmanager.hh"
#include "core/inputmanager.hh"
#include "game/block.hh"
#include "game/player.hh"
#include "game/updownlayer.hh"
#include "graphic/graphicmanager.hh"
#include "graphic/textelement.hh"
#include "utils/gettext.hh"
#include "utils/timemanager.hh"

namespace game
{
  BattleScene::BattleScene(const char* filename) :
    Scene(),
    isPaused_ (false),
    pauseText_ (0),
    map_ (0),
    outoftime_ (false),
    timer_ (getDefaultBattleLength()),
    skipCount_ (false)
  {
    graphic::GraphicManager* gm = graphic::GraphicManager::get_instance();

    core::ConfigManager* cm = core::ConfigManager::get_instance();
    const char* name =
      cm->queryConfigurationFile("game", "BattleScene", "skipCount_");
    skipCount_ = (!!name && std::string(name) == "true") ? true : false;

    map_ = Map::loadFromXml(filename);

    graphic::GraphicManager::Color col;
    col.r = 255, col.g = 0, col.b = 128;
    pauseText_ = new graphic::TextElement(_("Pause"), col);
    pauseText_->setPosition(
                            (gm->getScreenWidth()-pauseText_->getWidth())/2,
                            (gm->getScreenHeight()-pauseText_->getHeight())/2);
    pauseText_->hide();

    timer_.reset(getDefaultBattleLength());
  }

  BattleScene::BattleScene(const BattleScene& bs) :
    Scene(),
    isPaused_ (bs.isPaused_),
    map_ (bs.map_),
    outoftime_ (bs.outoftime_),
    timer_ (bs.timer_)
  {
    for(unsigned int i = 0; i < bs.players_.size(); ++i)
      players_[i] = bs.players_[i];
  }

  BattleScene::~BattleScene()
  {
    delete pauseText_;
    delete map_;
  }

  BattleScene&
  BattleScene::operator=(const BattleScene& bs)
  {
    for(unsigned int i = 0; i < bs.players_.size(); i++)
      players_[i] = bs.players_[i];

    return *this;
  }

  void BattleScene::addPlayer(Player* newPlayer)
  {
    if (!newPlayer)
      {
        ERROR() << _("Invalid player inserted.") << std::endl;
        assert(0);
      }
    players_.push_back(newPlayer);
  }

  int BattleScene::play()
  {
    graphic::GraphicManager* gm = graphic::GraphicManager::get_instance();
    core::InputManager* im = core::InputManager::get_instance();

    if (!map_)
      return 0;

    if (!skipCount_)
      showCount();

    graphic::GraphicManager::Color col;
    col.r = 255, col.g = 0, col.b = 128;

    while (nbPlayerAlive() >=2  && !timer_.is_time(false)
           && !im->isExiting())
      {
        handle();
        if (!isPaused_)
          playersPlay();
        render();
        gm->flip();
      }

    return 0;
  }

  void
  BattleScene::render()
  {
    map_->render();
    for (players_t::iterator it = players_.begin();
         it < players_.end(); ++it)
      (*it)->render();

    pauseText_->draw();
  }

  void
  BattleScene::handle()
  {
    core::InputManager* im = core::InputManager::get_instance();

    im->handle();
    if(im->isPausePushed())
      switchPause();

    map_->handleEvents(*this);

    if (!outoftime_ && timer_.TimeLeft() < outOfTimeDelay())
      outOfTime();
  }

  void
  BattleScene::playersPlay()
  {
    if (isPaused_)
      return;
    for (players_t::iterator it = players_.begin();
         it < players_.end(); ++it)
      if ((*it)->isAlive())
        (*it)->play(*this);
  }

  void
  BattleScene::outOfTime()
  {
    if (outoftime_)
      return;
    outoftime_ = true;

    game::UpDownLayer* l =
      dynamic_cast<game::UpDownLayer*>(map_->getLayers()[2]);

    for (int x = 0; x < map_->getWidth(); ++x)
      {
        game::Block* elt = 0;

        const unsigned xpos =
          getCurrentMap()->getRenderingZone().x+x*game::Map::SIZE_TILE_X;
        const unsigned ypos1 =
          getCurrentMap()->getRenderingZone().y;
        const unsigned ypos2 =
          getCurrentMap()->getRenderingZone().y+
          (map_->getHeight()-1)*game::Map::SIZE_TILE_Y;

        map_->removeBlocks(xpos, ypos1);
        elt = new game::Block();
        elt->getSprite().setPosition(xpos, ypos1);
        l->pushGameElement(elt);
        for (players_t::iterator it = players_.begin();
             it < players_.end(); ++it)
          if (game::GameElement::collide((*it)->getXPosition(),
                                         (*it)->getYPosition(),
                                         (*it)->getSprite().getWidth(),
                                         (*it)->getSprite().getHeight(),
                                         xpos,
                                         ypos1,
                                         game::Map::SIZE_TILE_X,
                                         game::Map::SIZE_TILE_Y))
            (*it)->die();

        map_->removeBlocks(xpos, ypos2);
        elt = new game::Block();
        elt->getSprite().setPosition(xpos, ypos2);
        l->pushGameElement(elt);

        for (players_t::iterator it = players_.begin();
             it < players_.end(); ++it)
          if (game::GameElement::collide((*it)->getXPosition(),
                                         (*it)->getYPosition(),
                                         (*it)->getSprite().getWidth(),
                                         (*it)->getSprite().getHeight(),
                                         xpos,
                                         ypos2,
                                         game::Map::SIZE_TILE_X,
                                         game::Map::SIZE_TILE_Y))
            (*it)->die();
      }

    for (int y = 0; y < map_->getHeight(); ++y)
      {
        game::Block* elt = 0;

        const unsigned ypos =
          getCurrentMap()->getRenderingZone().y+y*game::Map::SIZE_TILE_Y;

        const unsigned xpos1 =
          getCurrentMap()->getRenderingZone().x;
        const unsigned xpos2 =
          getCurrentMap()->getRenderingZone().x+
          (map_->getWidth()-1)*game::Map::SIZE_TILE_X;

        map_->removeBlocks(xpos1, ypos);
        elt = new game::Block();
        elt->getSprite().setPosition(xpos1, ypos);
        l->pushGameElement(elt);
        for (players_t::iterator it = players_.begin();
             it < players_.end(); ++it)
          if (game::GameElement::collide((*it)->getXPosition(),
                                         (*it)->getYPosition(),
                                         (*it)->getSprite().getWidth(),
                                         (*it)->getSprite().getHeight(),
                                         xpos1,
                                         ypos,
                                         game::Map::SIZE_TILE_X,
                                         game::Map::SIZE_TILE_Y))
              (*it)->die();


        map_->removeBlocks(xpos2, ypos);
        elt = new game::Block();
        elt->getSprite().setPosition(xpos2, ypos);
        l->pushGameElement(elt);
        for (players_t::iterator it = players_.begin();
             it < players_.end(); ++it)
          if (game::GameElement::collide((*it)->getXPosition(),
                                         (*it)->getYPosition(),
                                         (*it)->getSprite().getWidth(),
                                         (*it)->getSprite().getHeight(),
                                         xpos2,
                                         ypos,
                                         game::Map::SIZE_TILE_X,
                                         game::Map::SIZE_TILE_Y))
              (*it)->die();
      }
  }

  unsigned BattleScene::nbPlayerAlive() const
  {
    unsigned nbAlive=0;

    for (players_t::const_iterator it = players_.begin();
         it < players_.end(); ++it)
      if ((*it)->isAlive())
        nbAlive++;
    return nbAlive;
  }

  void
  BattleScene::showCount()
  {
    graphic::GraphicManager* gm = graphic::GraphicManager::get_instance();
    core::InputManager* im = core::InputManager::get_instance();

    graphic::GraphicManager::Color col;
    col.r = 255, col.g = 0, col.b = 128;

    typedef std::vector<graphic::TextElement*> tabcount_t;
    tabcount_t tabCount;
    tabCount.push_back(new graphic::TextElement(_("3"), col));
    tabCount.push_back(new graphic::TextElement(_("2"), col));
    tabCount.push_back(new graphic::TextElement(_("1"), col));
    tabCount.push_back(new graphic::TextElement(_("Go !"), col));

    utils::TimeManager * tm = new utils::TimeManager(1000);

    unsigned c = 0;
    while (c < tabCount.size() && !im->isExiting())
      {
        im->handle();

        tabCount[c]->setPosition(
                     (gm->getScreenWidth()-tabCount[c]->getWidth())/2,
                     (gm->getScreenHeight()-tabCount[c]->getHeight())/2);
        render();
        tabCount[c]->draw();

        if (tm->is_time(true))
          ++c;
        gm->flip();
      }

    for (tabcount_t::iterator it = tabCount.begin();
         it != tabCount.end(); ++it)
      delete *it;
  }

  void
  BattleScene::switchPause()
  {
    isPaused_ = !isPaused_;
    if (isPaused_)
      pauseText_->show();
    else
      pauseText_->hide();
  }

  unsigned
  BattleScene::getDefaultBattleLength() const
  {
    core::ConfigManager* cm = core::ConfigManager::get_instance();
    return cm->getIntFromConfigurationFile("game", "BattleScene", "defaultBattleLength");
  }

  unsigned
  BattleScene::outOfTimeDelay() const
  {
    core::ConfigManager* cm = core::ConfigManager::get_instance();
    return cm->getIntFromConfigurationFile("game", "BattleScene", "outOfTimeDelay");
  }
};
