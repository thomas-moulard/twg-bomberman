/*!
 * \file  core/application.hh
 *
 * @brief Déclaration de \c core::Application .
 */

 /*!
 *  \class   Application
 *
 *  @brief   Point d'entrée du jeu.
 *           Elle sert à lancer le programme, gérer le fenêtrage, et
 *           de manière plus générale, elle fait office de conteneur à
 *           toute l'application.
 *  @author  Thomas Moulard <thomas.moulard@gmail.com>
 *  @author  Aurélien Vallée <vallee.aurelien@gmail.com>
 *  @version 1.0
 *  @date    07-24-2006
 *  @bug     none
 *  @warning none
 */

#ifndef CORE_APPLICATION_HH_
# define CORE_APPLICATION_HH_
# include <vector>

namespace game
{
  class Scene;
  class Player;
};

namespace core
{
  // Ceci est un hack pour faire fonctionner gettext...
  char* mygettext(const char* s);

  class Application
  {
  public:
    typedef std::vector<game::Player*> players_t;

    /*!
     *  \fn         Application()
     *
     *  @brief      Constructeur par défaut de la classe.
     */
    Application();

    /*!
     *  \fn         Application(const Application&)
     *
     *  @brief      Constructeur par copie de la classe.
     */
    Application(const Application&);

    /*!
     *  \fn         ~Application()
     *
     *  @brief      Destructeur par défaut de la classe.
     */
    ~Application();

    /*!
     *  \fn         Application& operator=(const Application&)
     *
     *  @brief      Surcharge de l'opérateur = (assignation).
     *              Cet opérateur est équivalent au constructeur
     *              par copie de la classe.
     */
    Application& operator=(const Application&);

    /*!
     *  \fn         unsigned char run(int argc, const char** argv)
     *
     *  @brief      Cette fonction est chargée de lancer l'application,
     *              d'initialiser tous les composants...
     *  @param[in]  argc
     *              Comprendre ARGument Count, contient un entier
     *              symbolisant le nombre d'arguments passés au
     *              programme. Les valeurs de ces arguments sont
     *              contenus dans \a argv .
     *  @param[in]  argv
     *              Comprendre ARGument Values, contient les arguments
     *              passés au programme, qui sont au nombre de \a argc .
     *  @return     Renvoie un \c unsigned \c char . Soit EXIT_SUCCESS(0),
     *              soit EXIT_FAILURE(1).
     */
    unsigned char run(int argc, const char** argv);

    void intro();
    void menu();

    void normal();
    void battle();
    void options();
    void credits();

    int replaceScene(game::Scene*);
    int useOnceScene(game::Scene*);
    int stackScene(game::Scene*);

    void exit(int);

    void removePlayers();
  private:
    /*!
     *  \property   game::Scene* currentScene_
     *
     *  @brief      Cet attribut contient un pointeur vers la
     *              scène courante (celle qui est en train d'être
     *              jouée par l'application).
     *  @sa         game::Scene
     */
    game::Scene* currentScene_;

    players_t players_;

    bool skipIntro_;
  };
};

#endif /* !CORE_APPLICATION_HH_ */







