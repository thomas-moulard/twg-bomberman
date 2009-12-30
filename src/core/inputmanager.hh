/*!
 * \file  core/inputmanager.hh
 *
 * @brief Déclaration de \c core::InputManager.
 */

 /*!
 *  \class   InputManager
 *
 *  @brief   La classe \c InputManager classe gère les entrées
 *           (touches clavier) du programme.
 *  @author  Thomas Moulard <thomas.moulard@gmail.com>
 *  @author  Aurélien Vallée <vallee.aurelien@gmail.com>
 *  @version 1.0
 *  @date    07-24-2006
 *  @bug     none
 *  @warning none
 */

#ifndef CORE_INPUTMANAGER_HH_
# define CORE_INPUTMANAGER_HH_
# include <string>
# include <vector>
# include "SDL/SDL.h"
# include "utils/timemanager.hh"

namespace core
{
  class InputManager
  {
  public:
    typedef unsigned keyboardkey_t;
    typedef unsigned joystickindex_t;
    typedef unsigned joystickbutton_t;
    typedef unsigned joystickaxis_t;
    typedef int joystickaxisvalue_t;

    typedef SDL_Joystick joystick_t;

    enum InputDevice
    {
        INPUTDEVICE_KEYBOARD,
        INPUTDEVICE_JOYSTICK
    };

    enum InputState
    {
        UP,
        DOWN,
        RELEASE
    };

    struct Key
    {
      explicit Key() :
        device (INPUTDEVICE_KEYBOARD),
        keyboardkey (0),
        joystickIndex (0),
        joystickIsButton (true),
        joystickButton (0),
        joystickAxis (0),
        joystickAxisValue (0)
      {
      }

      Key(InputDevice dev,
          keyboardkey_t kkey,
          joystickindex_t jindex,
          bool isbutton,
          joystickbutton_t jbutton,
          joystickaxis_t jaxis,
          joystickaxisvalue_t javalue) :
        device (dev),
        keyboardkey (kkey),
        joystickIndex (jindex),
        joystickIsButton (isbutton),
        joystickButton (jbutton),
        joystickAxis (jaxis),
        joystickAxisValue (javalue)
      {
      }

      InputDevice device;
      keyboardkey_t keyboardkey;
      joystickindex_t joystickIndex;
      bool joystickIsButton;
      joystickbutton_t joystickButton;
      joystickaxis_t joystickAxis;
      joystickaxisvalue_t joystickAxisValue;
    };

    static InputManager* get_instance()
    {
      if (!instance_)
    instance_ = new InputManager();
      return instance_;
    }
    static void kill()
    {
      if (instance_)
      delete instance_;
    }

    /*!
     *  \fn         bool handle ()
     *
     *  @brief      Cette fonction doit être appelée régulièrement afin
     *          que l'InputManager puisse fonctionner.
     */
    void handle ();

    /*!
     *  \fn         bool isLeftPushed (unsigned player)
     *
     *  @brief      Cette fonction permet de connaitre le statut de
     *              la touche gauche du joueur passé en paramètre.
     *  @param[in]  player
     *              Représente le numéro (game::BattleScene::MAX_PLAYERS)
     *              du joueur dont on veut connaitre l'état de la touche.
     *  @return     Renvoie un \c bool qui est \c true si la touche est
     *              pressée, \c false sinon.
     */
    bool isLeftPushed (unsigned player);

    /*!
     *  \fn         bool isRightPushed (unsigned player)
     *
     *  @brief      Cette fonction permet de connaitre le statut de
     *              la touche droite du joueur passé en paramètre.
     *  @param[in]  player
     *              Représente le numéro (game::BattleScene::MAX_PLAYERS)
     *              du joueur dont on veut connaitre l'état de la touche.
     *  @return     Renvoie un \c bool qui est \c true si la touche est
     *              pressée, \c false sinon.
     */
    bool isRightPushed(unsigned player);

    /*!
     *  \fn         bool isUpPushed (unsigned player)
     *
     *  @brief      Cette fonction permet de connaitre le statut de
     *              la touche haut du joueur passé en paramètre.
     *  @param[in]  player
     *              Représente le numéro (game::BattleScene::MAX_PLAYERS)
     *              du joueur dont on veut connaitre l'état de la touche.
     *  @return     Renvoie un \c bool qui est \c true si la touche est
     *              pressée, \c false sinon.
     */
    bool isUpPushed   (unsigned player);

    /*!
     *  \fn         bool isDownPushed (unsigned player)
     *
     *  @brief      Cette fonction permet de connaitre le statut de
     *              la touche bas du joueur passé en paramètre.
     *  @param[in]  player
     *              Représente le numéro (game::BattleScene::MAX_PLAYERS)
     *              du joueur dont on veut connaitre l'état de la touche.
     *  @return     Renvoie un \c bool qui est \c true si la touche est
     *              pressée, \c false sinon.
     */
    bool isDownPushed (unsigned player);

    /*!
     *  \fn         bool isActionKeyPushed (unsigned player)
     *
     *  @brief      Cette fonction permet de connaitre le statut de
     *              la touche action du jeu.
     *  @param[in]  player
     *  @return     Renvoie un \c bool qui est \c true si la touche est
     *              pressée, \c false sinon.
     */
    bool isActionKeyPushed(unsigned player);

    bool isActionKeyReleased(unsigned);

    /*!
     *  \fn         bool isPausePushed (void)
     *
     *  @brief      Cette fonction permet de connaitre le statut de
     *              la touche pause du jeu.
     *  @return     Renvoie un \c bool qui est \c true si la touche est
     *              pressée, \c false sinon.
     */
    bool isPausePushed();

    bool isKeyDown(Key&);
    bool isKeyRelease(Key&);
    void setMousePosition(int x, int y);

    joystick_t* getJoystick(joystickindex_t);

    void exit();
    bool isExiting() const;

    void inverseInput(unsigned player, unsigned delay);
    void clearBuffer()
    {
      for (unsigned int i = 0; i < max_keys; ++i)
        if (keyBuffer_[i] == RELEASE)
          keyBuffer_[i] = UP;
      for (joystickButtonsBuffer_t::iterator j = joystickButtonsBuffer_.begin();
           j != joystickButtonsBuffer_.end(); ++j)
        for (joystickButtonsBuffer_t::value_type::iterator b = j->begin();
             b != j->end(); ++b)
          if (*b == RELEASE)
            *b = UP;

      for (joystickAxesBuffer_t::iterator j = joystickAxesBuffer_.begin();
           j != joystickAxesBuffer_.end(); ++j)
        for (joystickAxesBuffer_t::value_type::iterator b = j->begin();
             b != j->end(); ++b)
          if (*b == RELEASE)
            *b = UP;
    }

    bool isInversed(int player);

    InputDevice getInputDeviceType(const char *) const;
    Key stringToJoystick(const char *);
    Key stringToKeyboard(const char *) const;

    Key KeyboardToKey(keyboardkey_t key) const
    {
      return Key(INPUTDEVICE_KEYBOARD, key, 0, false, 0, 0, 0);
    }

    static const unsigned USED_KEYS = 5;
  private:
    /*!
     * Le type de tableau utilise pour stocker les
     * touches de chaque joueur.
     */
    typedef std::vector<std::vector<Key> > playerkeys_t;

    typedef std::vector<joystick_t*> joysticks_t;
    typedef std::vector<std::vector<InputState> > joystickButtonsBuffer_t;
    typedef std::vector<std::vector<joystickaxisvalue_t> > joystickAxesBuffer_t;

    /*!
     *  \fn         InputManager()
     *
     *  @brief      Constructeur par défaut de la classe.
     */
    InputManager();

    /*!
     *  \fn         InputManager(const InputManager&)
     *
     *  @brief      Constructeur par copie de la classe.
     */
    InputManager(const InputManager&);

    /*!
     *  \fn         ~InputManager()
     *
     *  @brief      Destructeur par défaut de la classe.
     */
    ~InputManager();

    /*!
     *  \fn         InputManager& operator=(const InputManager&)
     *
     *  @brief      Surcharge de l'opérateur = (assignation).
     *              Cet opérateur est équivalent au constructeur
     *              par copie de la classe.
     */
    InputManager& operator=(const InputManager&);

    void OnKeyDown(SDLKey&);
    void OnKeyUp(SDLKey&);

    void OnJoystickButtonDown(joystickindex_t, joystickbutton_t);
    void OnJoystickButtonUp(joystickindex_t, joystickbutton_t);
    void OnJoystickAxisMove(joystickindex_t, joystickaxis_t,
                            joystickaxisvalue_t);

    static InputManager* instance_;

    static const unsigned max_keys = SDLK_LAST;
    InputState keyBuffer_[max_keys];
    bool isExiting_;

    playerkeys_t playerKeys_;
    joysticks_t joysticks_;
    joystickButtonsBuffer_t joystickButtonsBuffer_;
    joystickAxesBuffer_t joystickAxesBuffer_;

    int inversePlayer_;
    utils::TimeManager inverseTimer_;
  };
};

#endif
