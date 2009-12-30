#ifndef GAME_IAPLAYER_HH_
# define GAME_IAPLAYER_HH_
# include "game/battlescene.hh"
# include "game/player.hh"
# include "utils/pathmanager.hh"

# define IA_PLAYER_DATA_IMG \
        utils::PathManager::getDataFilename("/img/kat.png").c_str()
# define SPRITE_SIZE_X 32
# define SPRITE_SIZE_Y 32

namespace game
{
  namespace ia
  {
    class Behavior;
  }; // End of namespace ia

  class IAPlayer : public Player
  {
  public:
    enum Direction
      {
        DIRECTION_UP = 0,
        DIRECTION_RIGHT,
        DIRECTION_DOWN,
        DIRECTION_LEFT,
        DIRECTION_MAX
      };

    IAPlayer(unsigned, unsigned, unsigned);
    IAPlayer(const IAPlayer&);

    virtual ~IAPlayer();

    IAPlayer& operator=(const IAPlayer&);

    virtual void play(BattleScene& bs);

    Direction getDir() const;

    void randomizeDirection();
    void UTurn();
  private:

    Direction dir_;
    ia::Behavior* behavior_;
  };
};


#endif
