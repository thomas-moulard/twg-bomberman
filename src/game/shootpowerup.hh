/*!
  *  \file  game/shootpowerup
  *
  *  @brief Déclaration de \c game::ShootPowerUp .
  */

 /*!
  *  \class   ShootPowerUp
  *
  *  @brief   Classe ShootPowerUp non encore documentée.
  *  @author  Thomas Moulard <thomas.moulard@gmail.com>
  *  @author  Aurélien Vallée <vallee.aurelien@gmail.com>
  *  @version 1.0
  *  @date    07-29-2006
  *  @bug     none
  *  @warning none
  */

#ifndef GAME_SHOOTPOWERUP_HH_
# define GAME_SHOOTPOWERUP_HH_
# include "game/fwd.hh"
# include "game/powerup.hh"
# include "utils/pathmanager.hh"

# define SHOOT_POWERUP_DATA_IMG \
        utils::PathManager::getDataFilename("/img/fixme.png").c_str()


namespace game
{
  class ShootPowerUp : public PowerUp
  {
  public:
    /*!
     *  \fn         ShootPowerUp()
     *
     *  @brief      Constructeur par défaut de la classe.
     */
    ShootPowerUp();

    /*!
     *  \fn         ShootPowerUp(const ShootPowerUp&)
     *
     *  @brief      Constructeur par copie de la classe.
     */
    ShootPowerUp(const ShootPowerUp&);

    /*!
     *  \fn         ~ShootPowerUp()
     *
     *  @brief      Destructeur par défaut de la classe.
     */
    ~ShootPowerUp();

    /*!
     *  \fn         ShootPowerUp& operator=(const ShootPowerUp&)
     *
     *  @brief      Surcharge de l'opérateur = (assignation).
     *              Cet opérateur est équivalent au constructeur
     *              par copie de la classe.
     */
    ShootPowerUp& operator=(const ShootPowerUp&);

	virtual void render();
    virtual bool take(Player& player);

    static ShootPowerUp* loadFromXml(TiXmlElement*, Map*);
  private:
  };
};


#endif /* !GAME_SHOOTPOWERUP_HH_ */
