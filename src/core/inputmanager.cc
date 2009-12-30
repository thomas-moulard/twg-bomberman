/*!
 * \file  core/application.cc
 *
 * @brief Implémentation de \c core::InputManager.
 */
#include <cassert>
#include <cstdlib>
#include <sstream>
#include <SDL/SDL.h>

#include "core/inputmanager.hh"
#include "core/configmanager.hh"
#include "game/battlescene.hh"
#include "utils/debug.hh"
#include "utils/gettext.hh"

#define STRINGTOKEYBOARD_CASE(x)       \
    if (k == std::string(#x))          \
        return KeyboardToKey(x)

namespace core
{
  InputManager* InputManager::instance_ = 0;

  InputManager::InputManager() :
    isExiting_ (false),
    playerKeys_ (),
    joysticks_ (),
    inversePlayer_ (-1),
    inverseTimer_ (0)
  {
    ConfigManager* cm = ConfigManager::get_instance();

    if (SDL_InitSubSystem(SDL_INIT_JOYSTICK) < 0)
      {
        ERROR() << _("Failed to initialize SDL joystick subsystem.")
                << std::endl;
      }

    SDL_EnableUNICODE(1);

    if (SDL_NumJoysticks() > 0)
      {
        int num_joy = SDL_NumJoysticks();
        NOTICE() << num_joy << " " << _("joysticks found.") << std::endl;
        for(int i = 0; i < num_joy; i++)
          NOTICE() << " " << _("joystick")
                   << " " << SDL_JoystickName(i) << std::endl;
        joysticks_.resize(SDL_NumJoysticks());
        joystickButtonsBuffer_.resize(SDL_NumJoysticks());
        joystickAxesBuffer_.resize(SDL_NumJoysticks());
      }

    playerKeys_.resize(game::BattleScene::MAX_PLAYERS);
    int pl = 0;
    for (playerkeys_t::iterator i = playerKeys_.begin();
         i != playerKeys_.end(); ++i)
      {
        int key = 0;
        i->resize(USED_KEYS);
        for (playerkeys_t::value_type::iterator j = i->begin();
             j != i->end(); ++j)
          {
            std::string attr =
              cm->buildArray(cm->buildArray("playerKeys_", pl).c_str(), key);
            const char* keyStr = cm->queryConfigurationFile("core",
                                                            "InputManager",
                                                            attr.c_str());
            if (!!keyStr)
              {
                if (getInputDeviceType(keyStr) == INPUTDEVICE_KEYBOARD)
                  *j = stringToKeyboard(keyStr);
                else
                  *j = stringToJoystick(keyStr);
              } else
                *j = Key();
            ++key;
          }
        ++pl;
      }
  }

  InputManager::InputManager(const InputManager&) :
    isExiting_ (false),
    playerKeys_ (),
    joysticks_ (),
    inversePlayer_ (-1),
    inverseTimer_ (0)
  {
    assert(0);
  }

  InputManager::~InputManager()
  {
  }

  InputManager& InputManager::operator=(const InputManager&)
  {
    assert(0);
    return *this;
  }

  void
  InputManager::handle()
  {
    SDL_Event event;

    clearBuffer();

    while (SDL_PollEvent(&event))
      {
        switch (event.type)
          {
          case SDL_QUIT:
            ::exit(EXIT_SUCCESS);
          break;

          case SDL_KEYDOWN:
            OnKeyDown(event.key.keysym.sym);
            break;

          case SDL_KEYUP:
            OnKeyUp(event.key.keysym.sym);
            break;

          case SDL_JOYBUTTONDOWN:
            OnJoystickButtonDown(event.jbutton.which, event.jbutton.button);
            break;

          case SDL_JOYBUTTONUP:
            OnJoystickButtonUp(event.jbutton.which, event.jbutton.button);
            break;

          case SDL_JOYAXISMOTION:
            OnJoystickAxisMove(event.jaxis.which,
                               event.jaxis.axis, event.jaxis.value);
            break;
          }
      }

    if (inverseTimer_.is_time(true))
      {
        inversePlayer_ = -1;
        inverseTimer_.reset(0);
      }

    SDL_JoystickUpdate();
  }

  bool
  InputManager::isKeyDown(Key& key)
  {
    if (key.device == INPUTDEVICE_JOYSTICK)
      {
        if (key.joystickIsButton)
          return joystickButtonsBuffer_[key.joystickIndex][key.joystickButton]
            == DOWN;
        else if (key.joystickAxisValue < 0)
          return joystickAxesBuffer_[key.joystickIndex][key.joystickAxis]
            < key.joystickAxisValue;
        else
          return joystickAxesBuffer_[key.joystickIndex][key.joystickAxis]
            > key.joystickAxisValue;
      }
    else
      return keyBuffer_[key.keyboardkey] == DOWN;
  }

  bool
  InputManager::isKeyRelease(Key& key)
  {
    if (key.device == INPUTDEVICE_JOYSTICK)
      {
        if (key.joystickIsButton)
          return joystickButtonsBuffer_[key.joystickIndex][key.joystickButton]
            == RELEASE;
        else if (key.joystickAxisValue < 0)
          return joystickAxesBuffer_[key.joystickIndex][key.joystickAxis]
            >= key.joystickAxisValue;
        else
          return joystickAxesBuffer_[key.joystickIndex][key.joystickAxis]
            <= key.joystickAxisValue;
      }
    else
      return keyBuffer_[key.keyboardkey] == RELEASE;
  }

  bool
  InputManager::isLeftPushed(unsigned player)
  {
    if (isInversed(player))
      return isKeyDown(playerKeys_[player][3]);
    return isKeyDown(playerKeys_[player][2]);
  }

  bool
  InputManager::isRightPushed(unsigned player)
  {
    if (isInversed(player))
      return isKeyDown(playerKeys_[player][2]);
    return isKeyDown(playerKeys_[player][3]);
  }

  bool
  InputManager::isUpPushed(unsigned player)
  {
    if (isInversed(player))
      return isKeyDown(playerKeys_[player][1]);
    return isKeyDown(playerKeys_[player][0]);
  }

  bool
  InputManager::isDownPushed(unsigned player)
  {
    if (isInversed(player))
      return isKeyDown(playerKeys_[player][0]);
    return isKeyDown(playerKeys_[player][1]);
  }

  bool
  InputManager::isActionKeyPushed(unsigned player)
  {
    return isKeyDown(playerKeys_[player][4]);
  }

  bool
  InputManager::isActionKeyReleased(unsigned player)
  {
    return isKeyRelease(playerKeys_[player][4]);
  }

  bool
  InputManager::isPausePushed()
  {
    Key k = KeyboardToKey(SDLK_p);
    return isKeyDown(k);
  }

  void
  InputManager::OnKeyDown(SDLKey& key)
  {
    keyBuffer_[key] = DOWN;
  }

  void
  InputManager::OnKeyUp(SDLKey& key)
  {
    keyBuffer_[key] = RELEASE;
  }

  void
  InputManager::OnJoystickButtonDown(joystickindex_t id,
                                     joystickbutton_t button)
  {
    joystickButtonsBuffer_[id][button] = DOWN;
  }

  void
  InputManager::OnJoystickButtonUp(joystickindex_t id, joystickbutton_t button)
  {
    joystickButtonsBuffer_[id][button] = RELEASE;
  }

  void
  InputManager::OnJoystickAxisMove(joystickindex_t id,
                                   joystickaxis_t axis,
                                   joystickaxisvalue_t value)
  {
    joystickAxesBuffer_[id][axis] = value;
  }

  void
  InputManager::setMousePosition(int x, int y)
  {
    SDL_WarpMouse(x, y);
  }

  InputManager::joystick_t*
  InputManager::getJoystick(joystickindex_t id)
  {
    if (id >= SDL_NumJoysticks())
      {
        ERROR() << _("Try to access to invalid joystick")
                << std::endl;
        return 0;
      }
    if (joysticks_[id] == 0)
      {
        joysticks_[id] = SDL_JoystickOpen(id);
        if (joysticks_[id] == 0)
          WARNING() << _("Failed to open joystick.")
                    << std::endl;
        else
          {
            joystickButtonsBuffer_[id].resize(
              SDL_JoystickNumButtons(joysticks_[id]));
            joystickAxesBuffer_[id].resize(
              SDL_JoystickNumAxes(joysticks_[id]));
          }
      }
    return joysticks_[id];
  }

  void InputManager::exit()
  {
    isExiting_ = true;
  }

  bool
  InputManager::isExiting() const
  {
    return isExiting_;
  }

  void
  InputManager::inverseInput(unsigned player, unsigned delay)
  {
    inversePlayer_ = player;
    inverseTimer_.reset(delay);
  }

  bool
  InputManager::isInversed(int player)
  {
    return inversePlayer_ == player;
  }

  InputManager::InputDevice
  InputManager::getInputDeviceType(const char *key) const
  {
    if (std::string(key).compare(0, 5, "SDLK_") == 0)
      return INPUTDEVICE_KEYBOARD;
    return INPUTDEVICE_JOYSTICK;
  }

  InputManager::Key
  InputManager::stringToJoystick(const char* key)
  {
    std::string k(key);
    std::string tmp;

    joystickindex_t index = 0;
    joystickbutton_t button = 0;
    joystickaxis_t axis = 0;
    joystickaxisvalue_t axisv = 0;
    bool isbutton = true;

    std::istringstream iss(key);
    iss >> tmp;
    if (tmp == "SDLJB")
      {
        iss >> index;
        iss >> button;
        isbutton = true;
      }
    else if (tmp == "SDLJA")
      {
        iss >> index;
        iss >> axis;
        iss >> axisv;
        isbutton = false;
      } else
        WARNING() << _("Invalid key value.") << std::endl;

    getJoystick(index);

    return Key(INPUTDEVICE_JOYSTICK, 0, index, isbutton, button, axis, axisv);
  }

  InputManager::Key
  InputManager::stringToKeyboard(const char* key) const
  {
    std::string k(key);

    STRINGTOKEYBOARD_CASE(SDLK_BACKSPACE);
    STRINGTOKEYBOARD_CASE(SDLK_TAB);
    STRINGTOKEYBOARD_CASE(SDLK_CLEAR);
    STRINGTOKEYBOARD_CASE(SDLK_RETURN);
    STRINGTOKEYBOARD_CASE(SDLK_PAUSE);
    STRINGTOKEYBOARD_CASE(SDLK_ESCAPE);
    STRINGTOKEYBOARD_CASE(SDLK_SPACE);
    STRINGTOKEYBOARD_CASE(SDLK_EXCLAIM);
    STRINGTOKEYBOARD_CASE(SDLK_QUOTEDBL);
    STRINGTOKEYBOARD_CASE(SDLK_HASH);
    STRINGTOKEYBOARD_CASE(SDLK_DOLLAR);
    STRINGTOKEYBOARD_CASE(SDLK_AMPERSAND);
    STRINGTOKEYBOARD_CASE(SDLK_QUOTE);
    STRINGTOKEYBOARD_CASE(SDLK_LEFTPAREN);
    STRINGTOKEYBOARD_CASE(SDLK_RIGHTPAREN);
    STRINGTOKEYBOARD_CASE(SDLK_ASTERISK);
    STRINGTOKEYBOARD_CASE(SDLK_PLUS);
    STRINGTOKEYBOARD_CASE(SDLK_COMMA);
    STRINGTOKEYBOARD_CASE(SDLK_MINUS);
    STRINGTOKEYBOARD_CASE(SDLK_PERIOD);
    STRINGTOKEYBOARD_CASE(SDLK_SLASH);
    STRINGTOKEYBOARD_CASE(SDLK_0);
    STRINGTOKEYBOARD_CASE(SDLK_1);
    STRINGTOKEYBOARD_CASE(SDLK_2);
    STRINGTOKEYBOARD_CASE(SDLK_3);
    STRINGTOKEYBOARD_CASE(SDLK_4);
    STRINGTOKEYBOARD_CASE(SDLK_5);
    STRINGTOKEYBOARD_CASE(SDLK_6);
    STRINGTOKEYBOARD_CASE(SDLK_7);
    STRINGTOKEYBOARD_CASE(SDLK_8);
    STRINGTOKEYBOARD_CASE(SDLK_9);
    STRINGTOKEYBOARD_CASE(SDLK_COLON);
    STRINGTOKEYBOARD_CASE(SDLK_SEMICOLON);
    STRINGTOKEYBOARD_CASE(SDLK_LESS);
    STRINGTOKEYBOARD_CASE(SDLK_EQUALS);
    STRINGTOKEYBOARD_CASE(SDLK_GREATER);
    STRINGTOKEYBOARD_CASE(SDLK_QUESTION);
    STRINGTOKEYBOARD_CASE(SDLK_AT);
    /*
      Skip uppercase letters
    */
    STRINGTOKEYBOARD_CASE(SDLK_LEFTBRACKET);
    STRINGTOKEYBOARD_CASE(SDLK_BACKSLASH);
    STRINGTOKEYBOARD_CASE(SDLK_RIGHTBRACKET);
    STRINGTOKEYBOARD_CASE(SDLK_CARET);
    STRINGTOKEYBOARD_CASE(SDLK_UNDERSCORE);
    STRINGTOKEYBOARD_CASE(SDLK_BACKQUOTE);
    STRINGTOKEYBOARD_CASE(SDLK_a);
    STRINGTOKEYBOARD_CASE(SDLK_b);
    STRINGTOKEYBOARD_CASE(SDLK_c);
    STRINGTOKEYBOARD_CASE(SDLK_d);
    STRINGTOKEYBOARD_CASE(SDLK_e);
    STRINGTOKEYBOARD_CASE(SDLK_f);
    STRINGTOKEYBOARD_CASE(SDLK_g);
    STRINGTOKEYBOARD_CASE(SDLK_h);
    STRINGTOKEYBOARD_CASE(SDLK_i);
    STRINGTOKEYBOARD_CASE(SDLK_j);
    STRINGTOKEYBOARD_CASE(SDLK_k);
    STRINGTOKEYBOARD_CASE(SDLK_l);
    STRINGTOKEYBOARD_CASE(SDLK_m);
    STRINGTOKEYBOARD_CASE(SDLK_n);
    STRINGTOKEYBOARD_CASE(SDLK_o);
    STRINGTOKEYBOARD_CASE(SDLK_p);
    STRINGTOKEYBOARD_CASE(SDLK_q);
    STRINGTOKEYBOARD_CASE(SDLK_r);
    STRINGTOKEYBOARD_CASE(SDLK_s);
    STRINGTOKEYBOARD_CASE(SDLK_t);
    STRINGTOKEYBOARD_CASE(SDLK_u);
    STRINGTOKEYBOARD_CASE(SDLK_v);
    STRINGTOKEYBOARD_CASE(SDLK_w);
    STRINGTOKEYBOARD_CASE(SDLK_x);
    STRINGTOKEYBOARD_CASE(SDLK_y);
    STRINGTOKEYBOARD_CASE(SDLK_z);
    STRINGTOKEYBOARD_CASE(SDLK_DELETE);

    /* Numeric keypad */
    STRINGTOKEYBOARD_CASE(SDLK_KP0);
    STRINGTOKEYBOARD_CASE(SDLK_KP1);
    STRINGTOKEYBOARD_CASE(SDLK_KP2);
    STRINGTOKEYBOARD_CASE(SDLK_KP3);
    STRINGTOKEYBOARD_CASE(SDLK_KP4);
    STRINGTOKEYBOARD_CASE(SDLK_KP5);
    STRINGTOKEYBOARD_CASE(SDLK_KP6);
    STRINGTOKEYBOARD_CASE(SDLK_KP7);
    STRINGTOKEYBOARD_CASE(SDLK_KP8);
    STRINGTOKEYBOARD_CASE(SDLK_KP9);
    STRINGTOKEYBOARD_CASE(SDLK_KP_PERIOD);
    STRINGTOKEYBOARD_CASE(SDLK_KP_DIVIDE);
    STRINGTOKEYBOARD_CASE(SDLK_KP_MULTIPLY);
    STRINGTOKEYBOARD_CASE(SDLK_KP_MINUS);
    STRINGTOKEYBOARD_CASE(SDLK_KP_PLUS);
    STRINGTOKEYBOARD_CASE(SDLK_KP_ENTER);
    STRINGTOKEYBOARD_CASE(SDLK_KP_EQUALS);

    /* Arrows + Home/End pad */
    STRINGTOKEYBOARD_CASE(SDLK_UP);
    STRINGTOKEYBOARD_CASE(SDLK_DOWN);
    STRINGTOKEYBOARD_CASE(SDLK_RIGHT);
    STRINGTOKEYBOARD_CASE(SDLK_LEFT);
    STRINGTOKEYBOARD_CASE(SDLK_INSERT);
    STRINGTOKEYBOARD_CASE(SDLK_HOME);
    STRINGTOKEYBOARD_CASE(SDLK_END);
    STRINGTOKEYBOARD_CASE(SDLK_PAGEUP);
    STRINGTOKEYBOARD_CASE(SDLK_PAGEDOWN);

    /* Function keys */
    STRINGTOKEYBOARD_CASE(SDLK_F1);
    STRINGTOKEYBOARD_CASE(SDLK_F2);
    STRINGTOKEYBOARD_CASE(SDLK_F3);
    STRINGTOKEYBOARD_CASE(SDLK_F4);
    STRINGTOKEYBOARD_CASE(SDLK_F5);
    STRINGTOKEYBOARD_CASE(SDLK_F6);
    STRINGTOKEYBOARD_CASE(SDLK_F7);
    STRINGTOKEYBOARD_CASE(SDLK_F8);
    STRINGTOKEYBOARD_CASE(SDLK_F9);
    STRINGTOKEYBOARD_CASE(SDLK_F10);
    STRINGTOKEYBOARD_CASE(SDLK_F11);
    STRINGTOKEYBOARD_CASE(SDLK_F12);
    STRINGTOKEYBOARD_CASE(SDLK_F13);
    STRINGTOKEYBOARD_CASE(SDLK_F14);
    STRINGTOKEYBOARD_CASE(SDLK_F15);

    /* Key state modifier keys */
    STRINGTOKEYBOARD_CASE(SDLK_NUMLOCK);
    STRINGTOKEYBOARD_CASE(SDLK_CAPSLOCK);
    STRINGTOKEYBOARD_CASE(SDLK_SCROLLOCK);
    STRINGTOKEYBOARD_CASE(SDLK_RSHIFT);
    STRINGTOKEYBOARD_CASE(SDLK_LSHIFT);
    STRINGTOKEYBOARD_CASE(SDLK_RCTRL);
    STRINGTOKEYBOARD_CASE(SDLK_LCTRL);
    STRINGTOKEYBOARD_CASE(SDLK_RALT);
    STRINGTOKEYBOARD_CASE(SDLK_LALT);
    STRINGTOKEYBOARD_CASE(SDLK_RMETA);
    STRINGTOKEYBOARD_CASE(SDLK_LMETA);
    STRINGTOKEYBOARD_CASE(SDLK_LSUPER);
    STRINGTOKEYBOARD_CASE(SDLK_RSUPER);
    STRINGTOKEYBOARD_CASE(SDLK_MODE);
    STRINGTOKEYBOARD_CASE(SDLK_COMPOSE);

    /* Miscellaneous function keys */
    STRINGTOKEYBOARD_CASE(SDLK_HELP);
    STRINGTOKEYBOARD_CASE(SDLK_PRINT);
    STRINGTOKEYBOARD_CASE(SDLK_SYSREQ);
    STRINGTOKEYBOARD_CASE(SDLK_BREAK);
    STRINGTOKEYBOARD_CASE(SDLK_MENU);
    STRINGTOKEYBOARD_CASE(SDLK_POWER);
    STRINGTOKEYBOARD_CASE(SDLK_EURO);
    STRINGTOKEYBOARD_CASE(SDLK_UNDO);
    return Key();
  }
};
