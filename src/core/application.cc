/*!
 * \file  core/application.cc
 *
 * @brief Implémentation de \c core::Application.
 */
#include <cstdlib>
#include <locale.h>
#include <unistd.h>

#include "config.h"

#include "core/application.hh"
#include "core/configmanager.hh"
#include "core/inputmanager.hh"
#include "game/introscene.hh"
#include "game/menuscene.hh"
#include "game/battleoptionsscene.hh"
#include "game/battlescene.hh"
#include "game/endofbattlescene.hh"
#include "game/iaplayer.hh"
#include "game/humanplayer.hh"
#include "graphic/graphicmanager.hh"
#include "utils/debug.hh"
#include "utils/gettext.hh"

namespace core
{
  char* mygettext(const char* s)
  {
    return ::gettext(s);
  }

  Application::Application() :
    currentScene_ (0),
    players_(),
    skipIntro_ (false)
  {
    setlocale (LC_ALL, "");
    bindtextdomain (PACKAGE, LOCALEDIR);
    textdomain (PACKAGE);

    core::ConfigManager* cm = core::ConfigManager::get_instance();
    const char* name =
      cm->queryConfigurationFile("core", "Application", "skipIntro_");
    skipIntro_ = (!!name && std::string(name) == "true") ? true : false;
  }

  Application::Application(const Application&) :
    currentScene_ (0),
    players_(),
    skipIntro_ (false)
  {
    assert(0);
  }

  // Attention aux dépendances!
  Application::~Application()
  {
    removePlayers();
    InputManager::kill();
    graphic::GraphicManager::kill();
    utils::Debug::kill();
  }

  void
  Application::removePlayers()
  {
    for (players_t::iterator it = players_.begin(); it != players_.end(); ++it)
      delete *it;
    players_.clear();
  }

  unsigned char Application::run(int, const char**)
  {
    intro();
    menu();
    return EXIT_SUCCESS;
  }

  void Application::intro()
  {
    InputManager* im = InputManager::get_instance();

    if (skipIntro_)
      return;
    useOnceScene(new game::IntroScene());
    if (im->isExiting())
      this->exit(EXIT_SUCCESS);
  }

  void Application::menu()
  {
    InputManager* im = InputManager::get_instance();

    game::Scene* menu = new game::MenuScene();
    while (true)
      {
        int retCode = replaceScene(menu);
        if (im->isExiting())
          this->exit(EXIT_SUCCESS);

        switch (retCode)
          {
          case 0:
            normal();
            break;

          case 1:
            battle();
            break;

          case 2:
            options();
            break;

          case 3:
            credits();
            break;

          case 4:
            this->exit(EXIT_SUCCESS);
            break;

          default:
            ERROR() << _("Invalid return type.")
                    << std::endl;
            break;
          }

        if (im->isExiting())
          this->exit(EXIT_SUCCESS);
      }
  }

  void Application::normal()
  {
  }

  void Application::battle()
  {
    typedef game::BattleOptionsScene::BattleSettings::playertypes_t
      playertypes_t;

    game::BattleOptionsScene::BattleSettings settings;
    stackScene(new game::BattleOptionsScene(settings));

    removePlayers();

    unsigned i = 0;
    for (playertypes_t::iterator it = settings.playerTypes.begin();
         it != settings.playerTypes.end(); ++it, ++i)
      switch (*it)
        {
        case game::BattleOptionsScene::BattleSettings::PLAYER_TYPE_HUMAN:
          players_.push_back(new game::HumanPlayer(i, 0, 0));
          break;
        case game::BattleOptionsScene::BattleSettings::PLAYER_TYPE_IA:
          players_.push_back(new game::IAPlayer(i, 0, 0));
          break;
        default:
          ERROR() << _("Unexpected error.") << std::endl;
        }

    game::BattleScene* bs = 0;

    switch (settings.gameType)
      {
      case game::BattleOptionsScene::BattleSettings::GAME_TYPE_CLASSIC:
        bs = new game::BattleScene(settings.mapFilename.c_str());
        break;

      case game::BattleOptionsScene::BattleSettings::GAME_TYPE_SURVIVAL:
        NOTICE() << _("This game mode is not yet implemented.")
                 << std::endl;
        break;

      default:
        ERROR() << _("Unexpected error.") << std::endl;
      }

    for (players_t::iterator it = players_.begin(); it != players_.end(); ++it)
      {
        (*it)->reset(bs->getCurrentMap()->getPlayerInitialPositionX((*it)->getId()),
                     bs->getCurrentMap()->getPlayerInitialPositionY((*it)->getId()));
        bs->addPlayer(*it);
      }

    stackScene(bs);
    stackScene(new game::EndOfBattleScene(players_));
  }

  void Application::options()
  {
  }

  void Application::credits()
  {
  }

  int Application::replaceScene(game::Scene* s)
  {
    if (currentScene_ && s != currentScene_)
      delete currentScene_;
    currentScene_ = s;
    return currentScene_->play();
  }

  int Application::useOnceScene(game::Scene* s)
  {
    int retCode = replaceScene(s);
    delete currentScene_;
    currentScene_ = 0;
    return retCode;
  }

  int Application::stackScene(game::Scene* s)
  {
    game::Scene* cs = currentScene_;
    currentScene_ = s;
    int res = currentScene_->play();
    delete currentScene_;
    currentScene_ = cs;
    return res;
  }

  void Application::exit(int returnValue)
  {
    ::exit(returnValue);
  }
};
