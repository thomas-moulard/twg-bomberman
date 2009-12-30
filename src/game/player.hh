#ifndef GAME_PLAYER_HH_
#define GAME_PLAYER_HH_
# include <string>
# include "graphic/graphicmanager.hh"
# include "graphic/imageelement.hh"
# include "utils/timemanager.hh"

namespace game
{
  class Bomb;
  class BattleScene;

  class Player
  {
  public:

    enum Animation
      {
        ANIMATION_STAND = 0,
        ANIMATION_UP,
        ANIMATION_UPRIGHT,
        ANIMATION_RIGHT,
        ANIMATION_DOWNRIGHT,
        ANIMATION_DOWN,
        ANIMATION_DOWNLEFT,
        ANIMATION_LEFT,
        ANIMATION_UPLEFT,
        ANIMATION_DIE,
        ANIMATION_IDLE,
        ANIMATION_VICTORY
      };

    typedef game::Bomb* (*bombctor_t)(game::Player*);

    Player(unsigned id,
           const char* filename,
           unsigned x,
           unsigned y,
           unsigned frameSizeX,
           unsigned frameSizeY);
    Player(const Player&);

    virtual ~Player();

    Player& operator=(const Player&);

    virtual void play(BattleScene& bs) = 0;

    void move(Animation anim, BattleScene& bs);

    virtual void putBomb(game::BattleScene& bs);

    unsigned getId() const
    {
      return id_;
    }

    std::string& getName();
    void setName(const char* name);

    void setBombType(bombctor_t);

    unsigned getSpeed() const;
    void setSpeed(unsigned speed);

    unsigned getFire() const;
    void setFire(unsigned fire);

    unsigned getBomb() const;
    void setBomb(unsigned bomb);

    bool getShoot() const;
    void setShoot(bool shoot);

    bool getThrow() const;
    void setThrow(bool bthrow);

    bool getSuperBomb() const;
    void setSuperBomb(bool);

    bool isAlive() const;

    bool isMoving() const;
    void setMove(bool move);

    unsigned getXPosition();
    unsigned getYPosition();

    unsigned getScore() const
    {
      return score_;
    }

    void increaseScore()
    {
      ++score_;
    }

    void decreaseScore()
    {
      --score_;
    }

    void decreaseBombCounter();

    const graphic::ImageElement& getSprite() const
    {
      return sprite_;
    }

    void render()
    {
      if (alive_)
        sprite_.draw();
    }

    virtual void die()
    {
      sprite_.animation_set(ANIMATION_DIE);
      sprite_.animation_play();
    }

    virtual void reset(unsigned, unsigned);

    virtual graphic::GraphicManager::Rect getOffsets();

    static const unsigned MIN_SPEED = 8;
    static const unsigned MAX_SPEED = 32;

    static const unsigned MIN_FIRE = 1;
    static const unsigned MAX_FIRE = 10;

    static const unsigned MIN_BOMB = 1;
    static const unsigned MAX_BOMB = 5;

    static const unsigned IDLE_DELAY = 10000;
  protected:
    void computeNextPosition(Animation anim, unsigned& nextx, unsigned& nexty);
    void moveHandleShootBomb(Animation anim, BattleScene& bs);

    unsigned id_;
    std::string name_;

    bombctor_t bombCtor_;

    unsigned speed_;
    unsigned fire_;
    unsigned bomb_;

    bool shoot_;
    bool throw_;
    /*!
     * La super-bombe a la caractéristique de ne pas s'arrêter
     * après avoir détruit un bloc.
     */
    bool superbomb_;

    bool alive_;
    bool moving_;

    unsigned char score_;
    unsigned bombCounter_;

    graphic::ImageElement sprite_;

    utils::TimeManager idleTimer_;
  };
};


#endif
