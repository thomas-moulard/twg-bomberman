/*!
  *  \file  game/speedpowerup
  *
  *  @brief Déclaration de \c game::SpeedPowerUp .
  */

 /*!
  *  \class   SpeedPowerUp
  *
  *  @brief   Classe SpeedPowerUp non encore documentée.
  *  @author  Thomas Moulard <thomas.moulard@gmail.com>
  *  @author  Aurélien Vallée <vallee.aurelien@gmail.com>
  *  @version 1.0
  *  @date    07-29-2006
  *  @bug     none
  *  @warning none
  */

#ifndef GAME_SPEEDPOWERUP_HH_
# define GAME_SPEEDPOWERUP_HH_
# include "game/fwd.hh"
# include "game/powerup.hh"
# include "utils/pathmanager.hh"

# define SPEED_POWERUP_DATA_IMG \
        utils::PathManager::getDataFilename("/img/speedpowerup.png").c_str()


namespace game
{
  class SpeedPowerUp : public PowerUp
  {
  public:
    /*!
     *  \fn         SpeedPowerUp()
     *
     *  @brief      Constructeur par défaut de la classe.
     */
    SpeedPowerUp();

    /*!
     *  \fn         SpeedPowerUp(const SpeedPowerUp&)
     *
     *  @brief      Constructeur par copie de la classe.
     */
    SpeedPowerUp(const SpeedPowerUp&);

    /*!
     *  \fn         ~SpeedPowerUp()
     *
     *  @brief      Destructeur par défaut de la classe.
     */
    ~SpeedPowerUp();

    /*!
     *  \fn         SpeedPowerUp& operator=(const SpeedPowerUp&)
     *
     *  @brief      Surcharge de l'opérateur = (assignation).
     *              Cet opérateur est équivalent au constructeur
     *              par copie de la classe.
     */
    SpeedPowerUp& operator=(const SpeedPowerUp&);

    virtual void render();
    virtual bool take(Player& player);

    static SpeedPowerUp* loadFromXml(TiXmlElement*, Map*);
  private:
  };
};


#endif /* !GAME_SPEEDPOWERUP_HH_ */
