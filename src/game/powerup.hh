#ifndef GAME_POWERUP_HH_
# define GAME_POWERUP_HH_

# include "game/fwd.hh"
# include "game/gameelement.hh"
# include "game/player.hh"

namespace game
{
  class Player;

  class PowerUp : public GameElement
  {
  public:
    PowerUp(const char* filename);
    PowerUp(const PowerUp&);

    ~PowerUp();

    PowerUp& operator=(const PowerUp&);

    virtual void render() = 0;
    virtual bool take(Player& player) = 0;

    virtual bool isWalkable(int, int, int = 0, int = 0) const
    {
      return true;
    }

    virtual bool isDestructible(int, int, int = 0, int = 0) const
    {
      return true;
    }

    virtual void onTouch(game::BattleScene&, game::Player& pl)
    {
      if (!taken_)
        take(pl);
    }

    static PowerUp* loadFromXml(TiXmlElement*, Map*);
  protected:
    bool taken_;

  private:
  };
};


#endif
