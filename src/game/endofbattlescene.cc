/*!
 * \file  game/endofbattlescene.cc
 *
 * @brief Implémentation de \c game::EndOfBattleScene .
 */
#include <cassert>
#include <sstream>

#include "game/endofbattlescene.hh"

#include "core/inputmanager.hh"
#include "core/configmanager.hh"
#include "game/player.hh"
#include "graphic/graphicmanager.hh"
#include "graphic/textelement.hh"
#include "utils/debug.hh"

namespace game
{
  EndOfBattleScene::EndOfBattleScene(players_t& players) :
    Scene(),
    players_ (players),
    velements_ (),
    winner_ (0),
    skip_ (false)
  {
    core::ConfigManager* cm = core::ConfigManager::get_instance();
    const char* name =
      cm->queryConfigurationFile("game", "EndOfBattleScene", "skip_");
    skip_ = (!!name && std::string(name) == "true") ? true : false;

    graphic::GraphicManager* gm = graphic::GraphicManager::get_instance();

    graphic::GraphicManager::Color col;
    col.r = 255, col.g = 255, col.b = 255;

    unsigned bestscore = 0;
    for (players_t::const_iterator it = players_.begin(); it != players_.end();
         ++it)
      {
        if ((*it)->getScore() >= bestscore)
          {
            winner_ = *it;
            bestscore = (*it)->getScore();
          }

        std::stringstream stream;
        stream << (*it)->getName() << ": " << (*it)->getScore();

        graphic::TextElement* elt = new graphic::TextElement(stream.str().c_str(), col);
        velements_.push_back(elt);
        int x = (gm->getScreenWidth()-elt->getWidth())/2;
        int y = (gm->getScreenHeight()-elt->getHeight())/3;
        y += (*it)->getId()*(elt->getHeight()+3);

        velements_.back()->setPosition(x, y);
      }

    if (winner_)
      {
        std::stringstream stream;
        stream << _("The winner is") << ": ``"
               << winner_->getName()
               << "''!";

        graphic::TextElement* elt = new graphic::TextElement(stream.str().c_str(), col);
        velements_.push_back(elt);
        int x = (gm->getScreenWidth()-elt->getWidth())/2;
        int y = (gm->getScreenHeight()-elt->getHeight())/6;
        velements_.back()->setPosition(x, y);
      }
    else
      W() << _("No winner has been found.") << std::endl;
  }

  EndOfBattleScene::EndOfBattleScene(const EndOfBattleScene& eobs) :
    Scene(),
    players_ (eobs.players_),
    velements_ (eobs.velements_),
    winner_ (eobs.winner_),
    skip_ (eobs.skip_)
  {
    assert(0);
  }

  EndOfBattleScene::~EndOfBattleScene()
  {
    for (velements_t::iterator it = velements_.begin();
         it != velements_.end(); ++it)
      delete *it;
    velements_.clear();
  }

  EndOfBattleScene& EndOfBattleScene::operator=(const EndOfBattleScene&)
  {
    assert(0);
    return *this;
  }

  int EndOfBattleScene::play()
  {
    bool isdone = skip_;

    graphic::GraphicManager* gm = graphic::GraphicManager::get_instance();
    core::InputManager* im = core::InputManager::get_instance();
    core::InputManager::Key keyReturn = im->KeyboardToKey(SDLK_RETURN);

    while (!isdone)
      {
        gm->fillScreen(0);

        im->clearBuffer();
        im->handle();

        for (velements_t::iterator it = velements_.begin();
             it != velements_.end(); ++it)
          (*it)->draw();

        if (im->isKeyRelease(keyReturn))
          return 0;
        if (im->isExiting())
          return 0;

        gm->flip();
      }

    return 0;
  }

}; // End of namespace game
