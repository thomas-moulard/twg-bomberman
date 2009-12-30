/*!
 * \file  game/humanplayer.hh
 *
 * @brief Déclaration de \c game::HumanPlayer .
 */

 /*!
 *  \class   HumanPlayer
 *
 *  @brief   Classe représentant un joueur humain.
 *           Cette classe est chargée de gérer les entrées du joueur
 *           et de faire le liens avec la scène courante.
 *  @author  Thomas Moulard <thomas.moulard@gmail.com>
 *  @author  Aurélien Vallée <vallee.aurelien@gmail.com>
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
     *  @brief      Constructeur par défaut de la classe.
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
     *  @brief      Destructeur par défaut spécialisé de la classe.
     */
    virtual ~HumanPlayer();

    /*!
     *  \fn         HumanPlayer& operator=(const HumanPlayer&)
     *
     *  @brief      Surcharge de l'opérateur = (assignation).
     *              Cet opérateur est équivalent au constructeur
     *              par copie de la classe.
     */
    HumanPlayer& operator=(const HumanPlayer&);

   /*!
     *  \fn         virtual void play(BattleScene& bs)
     *
     *  @brief      Cette fonction est chargée de gérer
	   *              l'affichage du joueur.
	   *  @param[in]  battleScene
	   *              C'est une référence vers la scène courante où se situe
	   *              le joueur.
	   *
     */
    virtual void play(BattleScene&);

  private:
  };
};


#endif
