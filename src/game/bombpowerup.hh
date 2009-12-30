/*!
  *  \file  game/bombpowerup
  *
  *  @brief Déclaration de \c game::BombPowerUp .
  */

 /*!
  *  \class   BombPowerUp
  *
  *  @brief   Classe BombPowerUp non encore documentée.
  *  @author  Thomas Moulard <thomas.moulard@gmail.com>
  *  @author  Aurélien Vallée <vallee.aurelien@gmail.com>
  *  @version 1.0
  *  @date    07-29-2006
  *  @bug     none
  *  @warning none
  */

#ifndef GAME_BOMBPOWERUP_HH_
# define GAME_BOMBPOWERUP_HH_
# include "game/fwd.hh"
# include "game/powerup.hh"
# include "utils/pathmanager.hh"

# define BOMB_POWERUP_DATA_IMG \
        utils::PathManager::getDataFilename("/img/bombpowerup.png").c_str()

namespace game
{
  class BombPowerUp : public PowerUp
  {
  public:
    /*!
     *  \fn         BombPowerUp()
     *
     *  @brief      Constructeur par défaut de la classe.
     */
    BombPowerUp();

    /*!
     *  \fn         BombPowerUp(const BombPowerUp&)
     *
     *  @brief      Constructeur par copie de la classe.
     */
    BombPowerUp(const BombPowerUp&);

    /*!
     *  \fn         ~BombPowerUp()
     *
     *  @brief      Destructeur par défaut de la classe.
     */
    ~BombPowerUp();

    /*!
     *  \fn         BombPowerUp& operator=(const BombPowerUp&)
     *
     *  @brief      Surcharge de l'opérateur = (assignation).
     *              Cet opérateur est équivalent au constructeur
     *              par copie de la classe.
     */
    BombPowerUp& operator=(const BombPowerUp&);
    
    virtual void render();
    virtual bool take(Player& player);
    
    static BombPowerUp* loadFromXml(TiXmlElement*, Map* map);
  private:
  };
};


#endif /* !GAME_BOMBPOWERUP_HH_ */
