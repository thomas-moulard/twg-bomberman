#ifndef GAME_BLOCK_HH_
# define GAME_BLOCK_HH_

# include <tinyxml.h>

# include "game/fwd.hh"
# include "game/gameelement.hh"
# include "utils/pathmanager.hh"

# define BLOCK_DATA_IMG \
        utils::PathManager::getDataFilename("/img/crate0.png").c_str()

namespace game
{
  class Block : public GameElement
  {
  public:
    Block();
    Block(const Block&);

    ~Block();

    Block& operator=(const Block&);

    virtual void render();

    static Block* loadFromXml(TiXmlElement*, Map*);

    virtual bool isWalkable(int x, int y, int w = 0, int h = 0) const
    {
      return !collide(x, y, w, h);
    }

    virtual bool isDestructible(int, int, int = 0, int = 0) const
    {
      return true;
    }

    virtual void onTouch(game::BattleScene&, game::Player&)
    {
    }
  private:
  };
};


#endif /* !GAME_BLOCK_HH_ */
