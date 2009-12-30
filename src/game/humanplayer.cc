/*!
 * \file  game/humanplayer.cc
 *
 * @brief Implémentation de \c game::HumanPlayer .
 */

#include "game/humanplayer.hh"
#include "game/battlescene.hh"


namespace game
{
  HumanPlayer::HumanPlayer(unsigned id, unsigned x, unsigned y) :
    Player(id, HUMAN_PLAYER_DATA_IMG, x, y, SPRITE_SIZE_X, SPRITE_SIZE_Y)
  {
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

  HumanPlayer::HumanPlayer(const HumanPlayer& hp) :
    Player(hp.id_,
           HUMAN_PLAYER_DATA_IMG,
           hp.sprite_.getX(),
           hp.sprite_.getY(),
           SPRITE_SIZE_X,
           SPRITE_SIZE_Y)
  {
  }

  HumanPlayer::~HumanPlayer()
  {
  }

  HumanPlayer& HumanPlayer::operator=(const HumanPlayer&)
  {
    return *this; //FIXME
  }

  void HumanPlayer::play(BattleScene& bs)
  {
    core::InputManager *im = im->get_instance();

    if (sprite_.animation_get() == ANIMATION_DIE &&
        sprite_.getCurrentFrame() >= sprite_.getMaxFrame(ANIMATION_DIE) - 2)
      alive_ = false;

    if (sprite_.animation_get() != ANIMATION_DIE)
      {
        setMove(false);
        if (im->isUpPushed(id_))
          move(ANIMATION_UP, bs);

        if (im->isDownPushed(id_))
          move(ANIMATION_DOWN, bs);

        if(im->isRightPushed(id_))
          move(ANIMATION_RIGHT, bs);

        if(im->isLeftPushed(id_))
          move(ANIMATION_LEFT, bs);

        if(im->isActionKeyReleased(id_))
          putBomb(bs);

        if (!isMoving())
          {
            if (idleTimer_.is_time(false))
              move(ANIMATION_IDLE, bs);
            else
              move(ANIMATION_STAND, bs);
          }
      }
  }
};
