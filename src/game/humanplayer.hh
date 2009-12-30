/*!
 * \file  game/humanplayer.hh
 *
 * @brief D�claration de \c game::HumanPlayer .
 */

 /*!
 *  \class   HumanPlayer
 *
 *  @brief   Classe repr�sentant un joueur humain.
 *           Cette classe est charg�e de g�rer les entr�es du joueur
 *           et de faire le liens avec la sc�ne courante.
 *  @author  Thomas Moulard <thomas.moulard@gmail.com>
 *  @author  Aur�lien Vall�e <vallee.aurelien@gmail.com>
 *  @version 1.0
 *  @date    07-24-2006
 *  @bug     none
 *  @warning none
 */

#ifndef GAME_HUMANPLAYER_HH_
# define GAME_HUMANPLAYER_HH_
# include "game/player.hh"
# include "core/inputmanager.hh"
# include "graphic/visualelement.hh"
# include "utils/pathmanager.hh"

# define HUMAN_PLAYER_DATA_IMG \
        utils::PathManager::getDataFilename("/img/kat.png").c_str()
# define SPRITE_SIZE_X 32
# define SPRITE_SIZE_Y 32

namespace game
{

  class HumanPlayer : public Player
  {
  public:
    /*!
     *  \fn         HumanPlayer()
     *
     *  @brief      Constructeur par d�faut de la classe.
     */
    HumanPlayer(unsigned, unsigned, unsigned);

    /*!
     *  \fn         AHumanPlayer(const HumanPlayer&)
     *
     *  @brief      Constructeur par copie de la classe.
     */
    HumanPlayer(const HumanPlayer&);

    /*!
     *  \fn         virtual ~HumanPlayer()
     *
     *  @brief      Destructeur par d�faut sp�cialis� de la classe.
     */
    virtual ~HumanPlayer();

    /*!
     *  \fn         HumanPlayer& operator=(const HumanPlayer&)
     *
     *  @brief      Surcharge de l'op�rateur = (assignation).
     *              Cet op�rateur est �quivalent au constructeur
     *              par copie de la classe.
     */
    HumanPlayer& operator=(const HumanPlayer&);

   /*!
     *  \fn         virtual void play(BattleScene& bs)
     *
     *  @brief      Cette fonction est charg�e de g�rer
	   *              l'affichage du joueur.
	   *  @param[in]  battleScene
	   *              C'est une r�f�rence vers la sc�ne courante o� se situe
	   *              le joueur.
	   *
     */
    virtual void play(BattleScene&);

  private:
  };
};


#endif
