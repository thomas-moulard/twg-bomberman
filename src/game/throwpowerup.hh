/*!
  *  \file  game/throwpowerup
  *
  *  @brief Déclaration de \c game::ThrowPowerUp .
  */

 /*!
  *  \class   ThrowPowerUp
  *
  *  @brief   Classe ThrowPowerUp non encore documentée.
  *  @author  Thomas Moulard <thomas.moulard@gmail.com>
  *  @author  Aurélien Vallée <vallee.aurelien@gmail.com>
  *  @version 1.0
  *  @date    07-29-2006
  *  @bug     none
  *  @warning none
  */

#ifndef GAME_THROWPOWERUP_HH_
# define GAME_THROWPOWERUP_HH_
# include "game/fwd.hh"
# include "game/powerup.hh"
# include "utils/pathmanager.hh"

# define THROW_POWERUP_DATA_IMG \
        utils::PathManager::getDataFilename("/img/fixme.png").c_str()

namespace game
{
  class ThrowPowerUp : public PowerUp
  {
  public:
    /*!
     *  \fn         ThrowPowerUp()
     *
     *  @brief      Constructeur par défaut de la classe.
     */
    ThrowPowerUp();

    /*!
     *  \fn         ThrowPowerUp(const ThrowPowerUp&)
     *
     *  @brief      Constructeur par copie de la classe.
     */
    ThrowPowerUp(const ThrowPowerUp&);

    /*!
     *  \fn         ~ThrowPowerUp()
     *
     *  @brief      Destructeur par défaut de la classe.
     */
    ~ThrowPowerUp();

    /*!
     *  \fn         ThrowPowerUp& operator=(const ThrowPowerUp&)
     *
     *  @brief      Surcharge de l'opérateur = (assignation).
     *              Cet opérateur est équivalent au constructeur
     *              par copie de la classe.
     */
    ThrowPowerUp& operator=(const ThrowPowerUp&);

    virtual void render();
    virtual bool take(Player& player);

    static ThrowPowerUp* loadFromXml(TiXmlElement*, Map*);
  private:
  };
};


#endif /* !GAME_THROWPOWERUP_HH_ */
