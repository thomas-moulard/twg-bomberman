/*!
  *  \file  game/firepowerup
  *
  *  @brief D�claration de \c game::FirePowerUp .
  */

 /*!
  *  \class   FirePowerUp
  *
  *  @brief   Classe FirePowerUp non encore document�e.
  *  @author  Thomas Moulard <thomas.moulard@gmail.com>
  *  @author  Aur�lien Vall�e <vallee.aurelien@gmail.com>
  *  @version 1.0
  *  @date    07-29-2006
  *  @bug     none
  *  @warning none
  */

#ifndef GAME_FIREPOWERUP_HH_
# define GAME_FIREPOWERUP_HH_
# include "game/fwd.hh"
# include "game/powerup.hh"
# include "utils/pathmanager.hh"

# define FIRE_POWERUP_DATA_IMG \
        utils::PathManager::getDataFilename("/img/firepowerup.png").c_str()

namespace game
{
  class FirePowerUp : public PowerUp
  {
  public:
    /*!
     *  \fn         FirePowerUp()
     *
     *  @brief      Constructeur par d�faut de la classe.
     */
    FirePowerUp();

    /*!
     *  \fn         FirePowerUp(const FirePowerUp&)
     *
     *  @brief      Constructeur par copie de la classe.
     */
    FirePowerUp(const FirePowerUp&);

    /*!
     *  \fn         ~FirePowerUp()
     *
     *  @brief      Destructeur par d�faut de la classe.
     */
    ~FirePowerUp();

    /*!
     *  \fn         FirePowerUp& operator=(const FirePowerUp&)
     *
     *  @brief      Surcharge de l'op�rateur = (assignation).
     *              Cet op�rateur est �quivalent au constructeur
     *              par copie de la classe.
     */
    FirePowerUp& operator=(const FirePowerUp&);

    virtual void render();
    virtual bool take(Player& player);

    static FirePowerUp* loadFromXml(TiXmlElement*, Map*);
  private:
  };
};


#endif /* !GAME_FIREPOWERUP_HH_ */
