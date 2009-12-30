/*!
  *  \file  game/devilpowerup
  *
  *  @brief Déclaration de \c game::DevilPowerUp .
  */

 /*!
  *  \class   DevilPowerUp
  *
  *  @brief   Classe DevilPowerUp non encore documentée.
  *  @author  Thomas Moulard <thomas.moulard@gmail.com>
  *  @author  Aurélien Vallée <vallee.aurelien@gmail.com>
  *  @version 1.0
  *  @date    07-29-2006
  *  @bug     none
  *  @warning none
  */

#ifndef GAME_DEVILPOWERUP_HH_
# define GAME_DEVILPOWERUP_HH_
# include "game/fwd.hh"
# include "game/powerup.hh"
# include "utils/pathmanager.hh"

# define DEVIL_POWERUP_DATA_IMG \
        utils::PathManager::getDataFilename("/img/reversepowerup.png").c_str()

namespace game
{
  class DevilPowerUp : public PowerUp
  {
  public:
    /*!
     *  \fn         DevilPowerUp()
     *
     *  @brief      Constructeur par défaut de la classe.
     */
    DevilPowerUp();

    /*!
     *  \fn         DevilPowerUp(const DevilPowerUp&)
     *
     *  @brief      Constructeur par copie de la classe.
     */
    DevilPowerUp(const DevilPowerUp&);

    /*!
     *  \fn         ~DevilPowerUp()
     *
     *  @brief      Destructeur par défaut de la classe.
     */
    ~DevilPowerUp();

    /*!
     *  \fn         DevilPowerUp& operator=(const DevilPowerUp&)
     *
     *  @brief      Surcharge de l'opérateur = (assignation).
     *              Cet opérateur est équivalent au constructeur
     *              par copie de la classe.
     */
    DevilPowerUp& operator=(const DevilPowerUp&);

    virtual void render();
    virtual bool take(Player& player);

    static DevilPowerUp* loadFromXml(TiXmlElement*, Map*);
  private:
  };
};


#endif /* !GAME_DEVILPOWERUP_HH_ */
