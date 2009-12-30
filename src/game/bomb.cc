#include "game/bomb.hh"
#include <cassert>
#include <cstring>

#include "game/battlescene.hh"
#include "game/block.hh"
#include "game/classicbomb.hh"
#include "game/followbomb.hh"
#include "game/map.hh"
#include "game/minebomb.hh"
#include "utils/debug.hh"
#include "utils/pathmanager.hh"
#include "utils/portable.hh"

namespace game
{
  Bomb::Bomb(game::Player* owner, const char* filename) :
    GameElement(filename, 32, 32),
    state_ (BOMB_IDLE),
    timer_ (0),
    owner_ (owner),
    fire_ (game::Player::MIN_FIRE),
    forceExplosion_ (false)
  {
    if (owner)
      fire_ = owner->getFire();

    timer_.reset(getExplodeDelay());
  }

  Bomb::Bomb(const Bomb& b) :
    GameElement(),
    state_ (BOMB_IDLE),
    timer_ (0),
    owner_ (b.owner_)
  {
    assert(false);
  }

  Bomb::~Bomb()
  {
  }

  Bomb& Bomb::operator=(const Bomb&)
  {
    assert(false);
    return *this;
  }

  void
  Bomb::makeExplode()
  {
    forceExplosion_ = true;
  }

  void
  Bomb::handleStates(game::BattleScene& bs)
  {
    switch (state_)
      {
      case BOMB_IDLE:
        handleStateIdle(bs);
        break;

      case BOMB_EXPLODE:
        handleStateExplode(bs);
        break;

      case BOMB_HAS_EXPLODED:
        handleStateHasExploded(bs);
        break;

      default:
        W() << _("No handle function for this state.")
            << std::endl;
      }
  }

  void
  Bomb::handleStateIdle(game::BattleScene& bs)
  {
    if (!forceExplosion_ && !timer_.is_time(false))
      return;
    if (owner_)
      owner_->decreaseBombCounter();

    state_ = BOMB_EXPLODE;
    timer_.reset(getExplosionLength());
    addExplosions(bs);
  }

  void
  Bomb::handleStateExplode(game::BattleScene&)
  {
    if (!timer_.is_time(false))
      return;
    state_ = BOMB_HAS_EXPLODED;
    timer_.reset(0);

    for (explosions_t::iterator it = explosion_.begin();
         it != explosion_.end(); ++it)
      delete (*it);
    explosion_.clear();
  }

  void
  Bomb::handleStateHasExploded(game::BattleScene&)
  {
  }

  void Bomb::render()
  {
    sprite_.draw();
    for (explosions_t::iterator it = explosion_.begin();
         it < explosion_.end(); ++it)
      (*it)->draw();
  }

  bool
  Bomb::isTouched(int x, int y, int w, int h)
  {
    switch (state_)
      {
      case BOMB_IDLE:
        return collide(x, y, w, h);
        break;

      case BOMB_EXPLODE:
        if (collide(x, y, w, h))
          return true;
        for (explosions_t::const_iterator i = explosion_.begin();
             i < explosion_.end(); ++i)
          if (collide(x,
                      y,
                      w,
                      h,
                      (*i)->getX(),
                      (*i)->getY(),
                      (*i)->getWidth(),
                      (*i)->getHeight()))
            return true;
        return false;
        break;

      case BOMB_HAS_EXPLODED:
        return false;
        break;
      }
    return false;
  }


  bool
  Bomb::isWalkable(int x, int y, int w, int h) const
  {
    switch (state_)
      {
      case BOMB_IDLE:
        return !collide(x, y, w, h);
        break;

      case BOMB_EXPLODE:
        return !collide(x, y, w, h);
        break;

      case BOMB_HAS_EXPLODED:
        return true;
        break;
      }
    W() << _("Unexpected error.") << std::endl;
    return true;
  }

  bool
  Bomb::isDestructible(int, int, int, int) const
  {
    return true;
  }

  void
  Bomb::onTouch(game::BattleScene&, game::Player& pl)
  {
    if (state_ == BOMB_EXPLODE && pl.isAlive())
      {
        pl.die();
        if (owner_ && owner_ != &pl)
          owner_->increaseScore();
      }
  }

  unsigned
  Bomb::getExplodeDelay()
  {
    return 2000;
  }

  unsigned
  Bomb::getExplosionLength()
  {
    return 500;
  }

  game::Bomb*
  Bomb::collideWithBomb(game::BattleScene& bs, int x, int y, int w, int h)
    const
  {
    return dynamic_cast<Bomb*>(bs.getCurrentMap()->pickElement(2, x, y, w, h));
  }

  void
  Bomb::triggerBomb(game::BattleScene& bs, int x, int y, int w, int h)
  {
    game::Bomb* b = collideWithBomb(bs, x, y, w, h);
    if (!b || b->state_ != BOMB_IDLE)
      return;
    b->makeExplode();
  }

  bool
  Bomb::collideWithBlock(game::BattleScene& bs, int x, int y, int w, int h)
    const
  {
    return !bs.getCurrentMap()->isWalkable(x, y, w, h);
  }

  void
  Bomb::addExplosions(int dx, int dy, game::BattleScene& bs)
  {
    unsigned w = 32;
    unsigned h = 32;

    const unsigned ca =
      (dx != 0) ?
      BOMB_ANIMATION_HORIZONTAL
      : BOMB_ANIMATION_VERTICAL;

    unsigned ca_end = 0;
    if (dx < 0 && dy == 0)
      ca_end = BOMB_ANIMATION_LEFT;
    else if (dx > 0 && dy == 0)
      ca_end = BOMB_ANIMATION_RIGHT;
    else if (dx == 0 && dy < 0)
      ca_end = BOMB_ANIMATION_TOP;
    else if (dx == 0 && dy > 0)
      ca_end = BOMB_ANIMATION_BOTTOM;
    else
      W() << _("No available valid animation.") << std::endl;

    bool collision = false;
    for (unsigned i = 1; (i <= fire_) && !collision; ++i)
      {
        unsigned x = getX()+i*dx*w;
        unsigned y = getY()+i*dy*h;

        collision =
          !bs.getCurrentMap()->isDestructible(x, y, w, h);

        if (!collision)
          {
            if (!owner_->getSuperBomb() &&
                collideWithBlock(bs, x, y, w, h))
              collision = true;

            addExplosion(x, y, (i < fire_ && !collision) ? ca : ca_end);
            bs.getCurrentMap()->removeBlocks(x, y);
          }
        triggerBomb(bs, x, y, w, h);
      }
  }

  void
  Bomb::addExplosions(game::BattleScene& bs)
  {
    sprite_.hide();
    addExplosion(getX(), getY(), 0);

    addExplosions(1,  0, bs);
    addExplosions(-1, 0, bs);
    addExplosions(0,  1, bs);
    addExplosions(0, -1, bs);

    for (explosions_t::iterator it = explosion_.begin();
         it != explosion_.end(); ++it)
      {
        (*it)->animation_rewind();
        (*it)->animation_play();
      }
  }

  void
  Bomb::addExplosion(unsigned x, unsigned y, unsigned ca)
  {
    explosion_.push_back(new graphic::ImageElement(
                                                   utils::PathManager::getDataFilename("/img/explosion.png").c_str(),
                                                   32,
                                                   32));
    explosion_.back()->animation_set(ca);
    explosion_.back()->setPosition(x, y);

    unsigned l = getExplosionLength()/explosion_.back()->getMaxFrame();
    explosion_.back()->setFrameLength(l);
  }

  Bomb* Bomb::loadFromXml(TiXmlElement* node, Map* map)
  {
    const char* attr = node->Attribute("type");
    if (!strcasecmp(attr,"ClassicBomb"))
      return ClassicBomb::loadFromXml(node, map);
    if (!strcasecmp(attr,"FollowBomb"))
      return FollowBomb::loadFromXml(node, map);
    if (!strcasecmp(attr,"MineBomb"))
      return MineBomb::loadFromXml(node, map);
    return 0;
  }
};
