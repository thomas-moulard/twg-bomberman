#include <sstream>
#include "core/configmanager.hh"
#include "game/battlescene.hh"
#include "game/classicbomb.hh"
#include "game/player.hh"
#include "game/uplayer.hh"

namespace game
{
  Player::Player(unsigned id,
                 const char* filename,
                 unsigned x,
                 unsigned y,
                 unsigned frameSizeX,
                 unsigned frameSizeY) :
    id_ (id),
    name_ (""),
    bombCtor_ (&game::Bomb::create<ClassicBomb>),
    speed_ (MIN_SPEED),
    fire_ (MIN_FIRE),
    bomb_ (MIN_BOMB),
    shoot_ (false),
    throw_ (false),
    superbomb_ (false),
    alive_ (true),
    moving_(false),
    score_ (0),
    bombCounter_ (0),
    sprite_ (filename, frameSizeX, frameSizeY),
    idleTimer_ (IDLE_DELAY)
  {
    core::ConfigManager* cm = core::ConfigManager::get_instance();
    std::string attr = cm->buildArray("name", id);
    const char* name =
      cm->queryConfigurationFile("game", "Player", attr.c_str());

    if (!!name)
      name_ = name;
    else
      {
        std::stringstream stream;
        stream << id;
        stream >> name_;
        name_ = "No name " + name_;
      }

    sprite_.animation_rewind();
    sprite_.animation_stop();

    graphic::GraphicManager::Rect r = getOffsets();
    sprite_.setOffsets(r);
    sprite_.setPosition(x, y);
  }

  Player::~Player()
  {
  }

  void Player::move(Animation anim, BattleScene& bs)
  {

    unsigned prevx = sprite_.getX();
    unsigned prevy = sprite_.getY();
    bool collision = false;
    bool oldcollision = false;
    unsigned nextx = 0;
    unsigned nexty = 0;

    if (anim == ANIMATION_STAND)
      sprite_.animation_pause();
    else if (sprite_.animation_get() != anim)
      {
        sprite_.animation_set(anim);
        sprite_.animation_play();
      }

    setMove(false);
    switch (anim)
      {
      case ANIMATION_UP:
      case ANIMATION_DOWN:
      case ANIMATION_LEFT:
      case ANIMATION_RIGHT:
        setMove(true);
        break;

      default:
        break;
      }

    computeNextPosition(anim, nextx, nexty);

    collision = !bs.getCurrentMap()->isWalkable(nextx+sprite_.getOffsets().x,
                                                nexty+sprite_.getOffsets().y,
                                                sprite_.getOffsets().w,
                                                sprite_.getOffsets().h);

    oldcollision = !bs.getCurrentMap()->isWalkable(
                                                prevx+sprite_.getOffsets().x,
                                                prevy+sprite_.getOffsets().y,
                                                sprite_.getOffsets().w,
                                                sprite_.getOffsets().h);

    while (collision && (nextx != prevx || nexty != prevy))
      {
        if (prevx < nextx)
          nextx--;
        else if (prevx > nextx)
          nextx++;

        if (prevy < nexty)
          nexty--;
        else if (prevy > nexty)
          nexty++;

        collision = (!oldcollision) ?
          !bs.getCurrentMap()->isWalkable(nextx+sprite_.getOffsets().x,
                                          nexty+sprite_.getOffsets().y,
                                          sprite_.getOffsets().w,
                                          sprite_.getOffsets().h)
          :
          !bs.getCurrentMap()->isEscapingFromCollision(
                                               nextx+sprite_.getOffsets().x,
                                               nexty+sprite_.getOffsets().y,
                                               sprite_.getOffsets().w,
                                               sprite_.getOffsets().h);

      }

    if (prevx != nextx || prevy != nexty)
      idleTimer_.reset(idleTimer_.getDelay());
    sprite_.setPosition(nextx, nexty);

    if (!oldcollision)
      moveHandleShootBomb(anim, bs);
  }

  void
  Player::computeNextPosition(Animation anim, unsigned& nextx, unsigned& nexty)
  {
    const unsigned prevx = sprite_.getX();
      const unsigned prevy = sprite_.getY();

    nextx = prevx;
    nexty = prevy;

    switch(anim)
      {
      case ANIMATION_UP:
        nexty = (prevy > speed_) ? prevy-speed_ : 0;
        break;

      case ANIMATION_DOWN:
        nexty = prevy+speed_;
        break;

      case ANIMATION_RIGHT:
        nextx = prevx+speed_;
        break;

      case ANIMATION_LEFT:
        nextx = (prevx > speed_) ? prevx-speed_ : 0;
        break;

      default:
        break;
      }
  }

  void
  Player::moveHandleShootBomb(Animation anim, BattleScene& bs)
  {
    unsigned nextx, nexty;

    if (!getShoot())
      return;

    if (!isMoving()
        || anim == ANIMATION_IDLE
        || anim == ANIMATION_STAND
        || anim == ANIMATION_DIE)
      return;

    computeNextPosition(anim, nextx, nexty);

    game::Bomb* b =
      dynamic_cast<game::Bomb*>
      (bs.getCurrentMap()->pickElement(2, nextx, nexty,
                                       game::Map::SIZE_TILE_X,
                                       game::Map::SIZE_TILE_Y));

    if (!b)
      return;


    unsigned x = b->getSprite().getX();
    unsigned y = b->getSprite().getY();
    switch (anim)
      {
      case ANIMATION_UP:
        y = (y > speed_) ? y-speed_ : 0;
        break;

      case ANIMATION_DOWN:
        y = y+speed_;
        break;

      case ANIMATION_RIGHT:
        x = x+speed_;
        break;

      case ANIMATION_LEFT:
        x = (x > speed_) ? x-speed_ : 0;
        break;

      default:
        break;
      }

    b->getSprite().setPosition(x, y);
  }

  void
  Player::putBomb(game::BattleScene& bs)
  {
    if (bombCounter_ >= bomb_)
      return;

    Bomb* b = bombCtor_(this);

    unsigned w = b->getSprite().getWidth();
    unsigned h = b->getSprite().getHeight();
    int x = ((this->getXPosition()+sprite_.getOffsets().x
              +(sprite_.getOffsets().w/2))/w)*w;
    int y = ((this->getYPosition()+sprite_.getOffsets().y
             +(sprite_.getOffsets().h/2))/h)*h;

    if (x >= 0 && y >= 0 && bs.getCurrentMap()->isWalkable(x, y, w, h))
      {
        b->getSprite().setPosition(x, y);
        UpLayer* l;

        l = dynamic_cast<UpLayer*>(bs.getCurrentMap()->getLayers()[2]);
        if (!l)
          {
            E() << "UpLayer not found while putting a bomb." << std::endl;
            return;
          }
        l->pushGameElement(b);
        bombCounter_++;
      }
    else
      delete b;
  }

  void Player::reset(unsigned x, unsigned y)
  {
    bombCtor_ = &game::Bomb::create<ClassicBomb>;
    speed_ = MIN_SPEED;
    fire_ = MIN_FIRE;
    bomb_ = MIN_BOMB;
    shoot_ = false;
    throw_ = false;
    superbomb_ = false;
    alive_ = true;
    moving_ = false;
    //score_
    bombCounter_ = 0;

    sprite_.setPosition(x, y);
    sprite_.animation_set(ANIMATION_STAND);
  }

  graphic::GraphicManager::Rect Player::getOffsets()
  {
    core::ConfigManager* cm = core::ConfigManager::get_instance();
    graphic::GraphicManager::Rect r;
    r.x = cm->getIntFromConfigurationFile("game", "Player", "sprite_offset_x");
    r.y = cm->getIntFromConfigurationFile("game", "Player", "sprite_offset_y");
    r.w = cm->getIntFromConfigurationFile("game", "Player", "sprite_offset_w");
    r.h = cm->getIntFromConfigurationFile("game", "Player", "sprite_offset_h");
    return r;
  }

  std::string& Player::getName()
  {
    return name_;
  }

  void Player::setName(const char* name)
  {
    name_= name;
  }

  void Player::setBombType(bombctor_t bc)
  {
    bombCtor_ = bc;
  }

  unsigned Player::getSpeed() const
  {
    return speed_;
  }

  void Player::setSpeed(unsigned speed)
  {
    if (speed <= MAX_SPEED && speed >= MIN_SPEED)
      speed_ = speed;
  }

  unsigned Player::getFire() const
  {
    return fire_;
  }

  void Player::setFire(unsigned fire)
  {
    if (fire <= MAX_FIRE && fire >= MIN_FIRE)
      fire_ = fire;
  }

  unsigned Player::getBomb() const
  {
    return bomb_;
  }

  void Player::setBomb(unsigned bomb)
  {
    if (bomb <= MAX_BOMB && bomb >= MIN_BOMB)
      bomb_ = bomb;
  }

  bool Player::getShoot() const
  {
    return shoot_;
  }

  void Player::setShoot(bool shoot)
  {
    shoot_ = shoot;
  }

  bool Player::getThrow() const
  {
    return throw_;
  }

  void Player::setThrow(bool bthrow)
  {
    throw_ = bthrow;
  }

  bool Player::getSuperBomb() const
  {
    return superbomb_;
  }

  void Player::setSuperBomb(bool sb)
  {
    throw_ = sb;
  }

  bool Player::isAlive() const
  {
    return alive_;
  }

  unsigned Player::getXPosition()
  {
    return sprite_.getX();
  }

  unsigned Player::getYPosition()
  {
    return sprite_.getY();
  }

  void Player::decreaseBombCounter()
  {
    if (bombCounter_)
      bombCounter_--;
  }

  bool Player::isMoving() const
  {
    return moving_;
  }

  void Player::setMove(bool move)
  {
    moving_ = move;
  }

};
