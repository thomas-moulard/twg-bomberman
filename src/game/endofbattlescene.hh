/*!
 * \file  game/endofbattlescene.hh
 *
 * @brief D�claration de \c game::EndOfBattleScene .
 */

 /*!
 *  \class   EndOfBattleScene
 *
 *  @brief   Cette classe est une descendante de game::Scene.
 *           Elle est charg�e d'afficher le tableau de fin de partie,
 *           d'afficher les score, et de revenir au menu.
 *  @author  Thomas Moulard <thomas.moulard@gmail.com>
 *  @author  Aur�lien Vall�e <vallee.aurelien@gmail.com>
 *  @version 1.0
 *  @date    07-24-2006
 *  @bug     none
 *  @warning none
 */

#ifndef GAME_ENDOFBATTLESCENE_HH_
# define GAME_ENDOFBATTLESCENE_HH_
# include <vector>

# include "core/application.hh"
# include "game/scene.hh"
# include "graphic/visualelement.hh"

namespace game
{
  class Player;

  class EndOfBattleScene : public Scene
  {
  public:
    typedef core::Application::players_t players_t;
    typedef std::vector<graphic::VisualElement*> velements_t;

    /*!
     *  \fn         EndOfBattleScene()
     *
     *  @brief      Constructeur par d�faut de la classe.
     */
     EndOfBattleScene(players_t&);

    /*!
     *  \fn         EndOfBattleScene(const EndOfBattleScene&)
     *
     *  @brief      Constructeur par copie de la classe.
     */
    EndOfBattleScene(const EndOfBattleScene&);

    /*!
     *  \fn         ~EndOfBattleScene()
     *
     *  @brief      Destructeur par d�faut de la classe.
     */
    ~EndOfBattleScene();

    /*!
     *  \fn         EndOfBattleScene& operator=(const EndOfBattleScene&)
     *
     *  @brief      Surcharge de l'op�rateur = (assignation).
     *              Cet op�rateur est �quivalent au constructeur
     *              par copie de la classe.
     */
    EndOfBattleScene& operator=(const EndOfBattleScene&);

    virtual int play();

   private:
    players_t& players_;
    velements_t velements_;
    game::Player* winner_;
    bool skip_;
   };
};


#endif /* !GAME_ENDOFBATTLESCENE_HH_ */
