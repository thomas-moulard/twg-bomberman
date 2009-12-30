/*!
 * \file  game/iaplayer.cc
 *
 * @brief Implémentation de \c game::IaPlayer.
 */

#include <cassert>
#include "game/ia/behavior.hh"
#include "game/ia/randombehavior.hh"
#include "game/iaplayer.hh"
#include "game/battlescene.hh"
#include "utils/gettext.hh"


namespace game
{
  IAPlayer::IAPlayer(unsigned id, unsigned x, unsigned y) :
    Player(id, IA_PLAYER_DATA_IMG, x, y, SPRITE_SIZE_X, SPRITE_SIZE_Y),
    dir_ (static_cast<Direction>(rand() % DIRECTION_MAX)),
    behavior_ (0)
  {
    behavior_ = new game::ia::RandomBehavior(*this);
    sprite_.setMaxFrame(0, 1);
    sprite_.setMaxFrame(1, 6);
    sprite_.setMaxFrame(2, 5);
    sprite_.setMaxFrame(3, 6);
    sprite_.setMaxFrame(4, 5);
    sprite_.setMaxFrame(5, 6);
    sprite_.setMaxFrame(6, 5);
    sprite_.setMaxFrame(7, 6);
    sprite_.setMaxFrame(8, 5);
    sprite_.setMaxFrame(9, 12);
    sprite_.setMaxFrame(10, 7);
    sprite_.setMaxFrame(11, 1);
  }

  IAPlayer::IAPlayer(const IAPlayer& hp) :
    Player(hp.id_,
           IA_PLAYER_DATA_IMG,
           hp.sprite_.getX(),
           hp.sprite_.getY(),
           SPRITE_SIZE_X,
           SPRITE_SIZE_Y),
    dir_ (static_cast<Direction>(rand() % DIRECTION_MAX))
  {
  }

  IAPlayer::~IAPlayer()
  {
    delete behavior_;
  }

  IAPlayer& IAPlayer::operator=(const IAPlayer&)
  {
    return *this;
  }

  void IAPlayer::play(BattleScene& bs)
  {
    assert(behavior_);

    if (sprite_.animation_get() == ANIMATION_DIE &&
        sprite_.getCurrentFrame() == sprite_.getMaxFrame(ANIMATION_DIE) - 2)
      alive_ = false;

    behavior_->play(bs);
  }

  void IAPlayer::randomizeDirection()
  {
    dir_ = static_cast<Direction>(rand() % DIRECTION_MAX);
  }

  void IAPlayer::UTurn()
  {
    switch (dir_)
      {
      case DIRECTION_UP:
        dir_ = DIRECTION_DOWN;
        break;
      case DIRECTION_RIGHT:
        dir_ = DIRECTION_LEFT;
        break;
      case DIRECTION_DOWN:
        dir_ = DIRECTION_UP;
        break;
      case DIRECTION_LEFT:
        dir_ = DIRECTION_RIGHT;
        break;
      default:
        W() << "Mouvement invalide détecté." << std::endl;
      }
  }

  IAPlayer::Direction
  IAPlayer::getDir() const
  {
    return dir_;
  }
};
