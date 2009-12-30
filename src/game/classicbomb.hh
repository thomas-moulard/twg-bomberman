/**
 * \file game/classicbomb.hh
 * \brief Déclaration de Game::ClassicBomb.
 */
#ifndef GAME_CLASSICBOMB_HH_
# define GAME_CLASSICBOMB_HH_
# include "game/bomb.hh"
# include "game/fwd.hh"
# include "utils/pathmanager.hh"

#define CLASSIC_BOMB_DATA_IMG \
        utils::PathManager::getDataFilename("/img/classicbomb.png").c_str()

namespace game
{
  class ClassicBomb : public Bomb
  {
  public:
    ClassicBomb(game::Player* owner);
    ClassicBomb(const ClassicBomb&);

    ~ClassicBomb();

    ClassicBomb& operator=(const ClassicBomb&);

    static ClassicBomb* loadFromXml(TiXmlElement*, Map*);
  private:
  };
};


#endif /* !GAME_CLASSICBOMB_HH_ */
