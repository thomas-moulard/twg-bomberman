/*!
  *  \file  game/minebomb
  *
  *  @brief Déclaration de \c game::MineBomb .
  */

 /*!
  *  \class   MineBomb
  *
  *  @brief   Classe MineBomb non encore documentée.
  *  @author  Thomas Moulard <thomas.moulard@gmail.com>
  *  @author  Aurélien Vallée <vallee.aurelien@gmail.com>
  *  @version 1.0
  *  @date    07-29-2006
  *  @bug     none
  *  @warning none
  */

#ifndef GAME_MINEBOMB_HH_
# define GAME_MINEBOMB_HH_
# include "game/bomb.hh"
# include "game/fwd.hh"
# include "utils/pathmanager.hh"

# define MINE_BOMB_DATA_IMG \
        utils::PathManager::getDataFilename("/img/minebomb.png").c_str()

namespace game
{
  class MineBomb : public Bomb
  {
  public:
    typedef Bomb parent;

    enum MineBombExtraStates
      {
        MINEBOMB_NOTACTIVATED
      };

    /*!
     *  \fn         MineBomb()
     *
     *  @brief      Constructeur par défaut de la classe.
     */
    MineBomb(game::Player* owner);

    /*!
     *  \fn         MineBomb(const MineBomb&)
     *
     *  @brief      Constructeur par copie de la classe.
     */
    MineBomb(const MineBomb&);

    /*!
     *  \fn         ~MineBomb()
     *
     *  @brief      Destructeur par défaut de la classe.
     */
    ~MineBomb();

    /*!
     *  \fn         MineBomb& operator=(const MineBomb&)
     *
     *  @brief      Surcharge de l'opérateur = (assignation).
     *              Cet opérateur est équivalent au constructeur
     *              par copie de la classe.
     */
    MineBomb& operator=(const MineBomb&);

    virtual void onTouch(game::BattleScene&, game::Player&);
    virtual bool isWalkable(int, int, int, int) const;

    unsigned getActivationDelay() const;

    static MineBomb* loadFromXml(TiXmlElement*, Map*);
  private:
    utils::TimeManager activationTimer_;
    bool touched_;
  };
};


#endif /* !GAME_MINEBOMB_HH_ */
