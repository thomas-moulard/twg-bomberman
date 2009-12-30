/*!
  *  \file  game/followbomb
  *
  *  @brief Déclaration de \c game::FollowBomb .
  */

 /*!
  *  \class   FollowBomb
  *
  *  @brief   Classe FollowBomb non encore documentée.
  *  @author  Thomas Moulard <thomas.moulard@gmail.com>
  *  @author  Aurélien Vallée <vallee.aurelien@gmail.com>
  *  @version 1.0
  *  @date    07-29-2006
  *  @bug     none
  *  @warning none
  */

#ifndef GAME_FOLLOWBOMB_HH_
# define GAME_FOLLOWBOMB_HH_
# include "game/bomb.hh"
# include "game/fwd.hh"
# include "utils/pathmanager.hh"

# define FOLLOW_BOMB_DATA_IMG \
        utils::PathManager::getDataFilename("/img/fixme.png").c_str()

namespace game
{
  class FollowBomb : public Bomb
  {
  public:
    /*!
     *  \fn         FollowBomb()
     *
     *  @brief      Constructeur par défaut de la classe.
     */
    FollowBomb(game::Player* owner);

    /*!
     *  \fn         FollowBomb(const FollowBomb&)
     *
     *  @brief      Constructeur par copie de la classe.
     */
    FollowBomb(const FollowBomb&);

    /*!
     *  \fn         ~FollowBomb()
     *
     *  @brief      Destructeur par défaut de la classe.
     */
    ~FollowBomb();

    /*!
     *  \fn         FollowBomb& operator=(const FollowBomb&)
     *
     *  @brief      Surcharge de l'opérateur = (assignation).
     *              Cet opérateur est équivalent au constructeur
     *              par copie de la classe.
     */
    FollowBomb& operator=(const FollowBomb&);

    virtual void render();
    static FollowBomb* loadFromXml(TiXmlElement*, Map*);
  private:
  };
};


#endif /* !GAME_FOLLOWBOMB_HH_ */
