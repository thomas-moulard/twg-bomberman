/*!
  *  \file  game/minepowerup
  *
  *  @brief Déclaration de \c game::MinePowerUp .
  */

 /*!
  *  \class   MinePowerUp
  *
  *  @brief   Classe MinePowerUp non encore documentée.
  *  @author  Thomas Moulard <thomas.moulard@gmail.com>
  *  @author  Aurélien Vallée <vallee.aurelien@gmail.com>
  *  @version 1.0
  *  @date    07-29-2006
  *  @bug     none
  *  @warning none
  */

#ifndef GAME_MINEPOWERUP_HH_
# define GAME_MINEPOWERUP_HH_
# include "game/fwd.hh"
# include "game/powerup.hh"

# define MINE_POWERUP_DATA_IMG \
        utils::PathManager::getDataFilename("/img/fixme.png").c_str()

namespace game
{
  class MinePowerUp : public PowerUp
  {
  public:
    /*!
     *  \fn         MinePowerUp()
     *
     *  @brief      Constructeur par défaut de la classe.
     */
    MinePowerUp();

    /*!
     *  \fn         MinePowerUp(const MinePowerUp&)
     *
     *  @brief      Constructeur par copie de la classe.
     */
    MinePowerUp(const MinePowerUp&);

    /*!
     *  \fn         ~MinePowerUp()
     *
     *  @brief      Destructeur par défaut de la classe.
     */
    ~MinePowerUp();

    /*!
     *  \fn         MinePowerUp& operator=(const MinePowerUp&)
     *
     *  @brief      Surcharge de l'opérateur = (assignation).
     *              Cet opérateur est équivalent au constructeur
     *              par copie de la classe.
     */
    MinePowerUp& operator=(const MinePowerUp&);

	virtual void render();
    virtual bool take(Player& player);

	static MinePowerUp* loadFromXml(TiXmlElement*, Map*);
  private:
  };
};


#endif /* !GAME_MINEPOWERUP_HH_ */
