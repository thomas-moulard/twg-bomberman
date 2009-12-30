/*!
  *  \file  game/shootpowerup
  *
  *  @brief D�claration de \c game::ShootPowerUp .
  */

 /*!
  *  \class   ShootPowerUp
  *
  *  @brief   Classe ShootPowerUp non encore document�e.
  *  @author  Thomas Moulard <thomas.moulard@gmail.com>
  *  @author  Aur�lien Vall�e <vallee.aurelien@gmail.com>
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
     *  @brief      Constructeur par d�faut de la classe.
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
     *  @brief      Destructeur par d�faut de la classe.
     */
    ~ShootPowerUp();

    /*!
     *  \fn         ShootPowerUp& operator=(const ShootPowerUp&)
     *
     *  @brief      Surcharge de l'op�rateur = (assignation).
     *              Cet op�rateur est �quivalent au constructeur
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
