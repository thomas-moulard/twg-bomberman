#include <sys/types.h>
#include <dirent.h>

#include <sstream>

#include "game/battleoptionsscene.hh"
#include "game/battlescene.hh"

#include "core/inputmanager.hh"
#include "core/configmanager.hh"
#include "graphic/graphicmanager.hh"
#include "graphic/textelement.hh"
#include "graphic/gui/choiceelement.hh"
#include "utils/debug.hh"
#include "utils/gettext.hh"
#include "utils/pathmanager.hh"

namespace game
{
  BattleOptionsScene::BattleOptionsScene(BattleSettings& settings) :
    Scene(),
    settings_ (settings),
    title_ (0),
    vcelements_ (),
    currentRow_ (0),
    maps_ (),
    skip_ (false)
  {
    core::ConfigManager* cm = core::ConfigManager::get_instance();
    const char* name =
      cm->queryConfigurationFile("game", "BattleOptionsScene", "skip_");
    skip_ = (!!name && std::string(name) == "true") ? true : false;

    graphic::GraphicManager* gm = graphic::GraphicManager::get_instance();
    graphic::GraphicManager::Color col;
    col.r = 255, col.g = 255, col.b = 255;

    int x = 0;
    int y = 0;

    title_ = new graphic::TextElement(_("Game options"), col);
    x = (gm->getScreenWidth()-title_->getWidth())/2;
    y = (gm->getScreenHeight()-title_->getHeight())/6;
    title_->setPosition(x, y);

    y = (gm->getScreenHeight()-title_->getHeight())/3;

    graphic::gui::ChoiceElement* elt;
    {
      std::stringstream stream;
      stream << _("Game mode") << ": ";
      elt = new graphic::gui::ChoiceElement(stream.str(), col);
      elt->pushChoice(_("Classic"), col);
      elt->pushChoice(_("Survival"), col);
      x = (gm->getScreenWidth()-elt->getWidth())/2;
      y += static_cast<int>(elt->getHeight()*1.5);
      elt->setPosition(x, y);
      vcelements_.push_back(elt);
    }

    y += static_cast<int>(elt->getHeight());

    {
      getMaps(maps_);

      std::stringstream stream;
      stream << _("Map") << ": ";
      elt = new graphic::gui::ChoiceElement(stream.str(), col);

      for (std::vector<std::string>::iterator it = maps_.begin();
           it != maps_.end(); ++it)
        elt->pushChoice(it->c_str(), col);
      x = (gm->getScreenWidth()-elt->getWidth())/2;
      y += static_cast<int>(elt->getHeight()*1.5);
      elt->setPosition(x, y);
      vcelements_.push_back(elt);
    }

    y += static_cast<int>(elt->getHeight());

    for (int i = 0; i < 4; ++i)
      {
        std::stringstream stream;
        stream << _("Player type") << i << ": ";
        elt = new graphic::gui::ChoiceElement(stream.str(), col);
        elt->pushChoice(_("Human"), col).pushChoice(_("AI"), col);
        x = (gm->getScreenWidth()-elt->getWidth())/2;
        y += static_cast<int>(elt->getHeight()*1.5);
        elt->setPosition(x, y);

        if (i == 3)
          elt->setChoice(1);

        vcelements_.push_back(elt);
      }
  }

  BattleOptionsScene::BattleOptionsScene(const BattleOptionsScene& bos) :
    Scene(),
    settings_ (bos.settings_),
    title_ (0),
    vcelements_ (bos.vcelements_),
    currentRow_ (0),
    skip_ (bos.skip_)
  {
    assert(0);
  }

  BattleOptionsScene::~BattleOptionsScene()
  {
    for (vcelements_t::iterator it = vcelements_.begin();
         it != vcelements_.end(); ++it)
      delete *it;
    vcelements_.clear();
    delete title_;
  }

  BattleOptionsScene&
  BattleOptionsScene::operator=(const BattleOptionsScene&)
  {
    assert(0);
    return *this;
  }

  void
  BattleOptionsScene::changeChoice(unsigned currentRow)
  {
    if (currentRow_ == currentRow)
      return;

    currentRow_ = currentRow;
    refreshColors();
  }

  void
  BattleOptionsScene::refreshColors()
  {
    graphic::GraphicManager::Color col;
    col.r = 255, col.g = 255, col.b = 255;

    graphic::GraphicManager::Color colHighlighted;
    colHighlighted.r = 255, colHighlighted.g = 0, colHighlighted.b = 0;

    unsigned i = 0;
    for (vcelements_t::iterator it = vcelements_.begin();
         it != vcelements_.end(); ++it, ++i)
      if (i == currentRow_)
          (*it)->setColor(colHighlighted);
      else
          (*it)->setColor(col);
  }

  void
  BattleOptionsScene::setResults()
  {
    settings_.gameType =
      static_cast<BattleSettings::gameType_t>(vcelements_[0]->getChoice());

    const char* mapFilename = maps_[vcelements_[1]->getChoice()].c_str();
    settings_.mapFilename =
      utils::PathManager::getDataFilename(mapFilename);

    settings_.playerTypes.resize(BattleScene::MAX_PLAYERS);
    for (unsigned i = 0; i < BattleScene::MAX_PLAYERS; ++i)
      settings_.playerTypes[i] =
      static_cast<BattleSettings::playerType_t>(vcelements_[2+i]->getChoice());
  }

  void
  BattleOptionsScene::getMaps(std::vector<std::string>& maps)
  {
    DIR* d = 0;

    d = opendir(utils::PathManager::getDataFilename("/map").c_str());
    if (!d)
      {
        ERROR() << _("Can not read the map directory.")
                << std::endl;
        return;
      }

    dirent* dir = 0;

    while ((dir = readdir(d)))
      {
        std::string filename(dir->d_name);

        if (static_cast<int>(filename.find(".xml",
                                           filename.length() - 4)) != -1)
          {
            std::stringstream stream;
            stream << "/map/" << filename;
            maps.push_back(stream.str());
          }
      }
    closedir(d);
  }

  int
  BattleOptionsScene::play()
  {
    bool isdone = skip_;

    graphic::GraphicManager* gm = graphic::GraphicManager::get_instance();
    core::InputManager* im = core::InputManager::get_instance();

    core::InputManager::Key keyDown = im->KeyboardToKey(SDLK_DOWN);
    core::InputManager::Key keyUp = im->KeyboardToKey(SDLK_UP);
    core::InputManager::Key keyLeft = im->KeyboardToKey(SDLK_LEFT);
    core::InputManager::Key keyRight = im->KeyboardToKey(SDLK_RIGHT);
    core::InputManager::Key keyReturn = im->KeyboardToKey(SDLK_RETURN);

    refreshColors();

    while (!isdone)
      {
        gm->fillScreen(0);

        im->clearBuffer();
        im->handle();

        title_->draw();
        for (vcelements_t::iterator it = vcelements_.begin();
             it != vcelements_.end(); ++it)
          (*it)->draw();

        if (im->isKeyRelease(keyDown))
          if (currentRow_ < vcelements_.size() - 1)
            changeChoice(currentRow_ + 1);
        if (im->isKeyRelease(keyUp))
          if (currentRow_ > 0)
            changeChoice(currentRow_ - 1);
        if (im->isKeyRelease(keyReturn))
          {
            setResults();
            return 0;
          }
        if (im->isExiting())
          {
            setResults();
            return 0;
          }

        vcelements_[currentRow_]->handle(keyLeft, keyRight);

        gm->flip();
      }
    return 0;
  }

}; // End of namespace game

