/*!
 * \file  game/ia/randombehavior.cc
 *
 * @brief Implémentation de \c game::ia::RandomBehavior.
 */
#include "game/ia/randombehavior.hh"
#include "game/iaplayer.hh"
#include "game/player.hh"
#include "utils/debug.hh"
#include "utils/gettext.hh"

namespace game
{
  namespace ia
  {
    RandomBehavior::RandomBehavior(game::IAPlayer& player) :
      Behavior(player)
    {
    }

    RandomBehavior::RandomBehavior(const RandomBehavior& rb) :
      Behavior(rb.player_)
    {
    }

    RandomBehavior::~RandomBehavior()
    {
    }

    RandomBehavior&
    RandomBehavior::operator=(const RandomBehavior&)
    {
      return *this;
    }

    void
    RandomBehavior::play(game::BattleScene& bs)
    {
      unsigned x = player_.getSprite().getX();
      unsigned y = player_.getSprite().getY();

      if (player_.getSprite().animation_get() != game::Player::ANIMATION_DIE)
        {
          switch (player_.getDir())
            {
            case game::IAPlayer::DIRECTION_UP:
              player_.move(game::Player::ANIMATION_UP, bs);
              break;
            case game::IAPlayer::DIRECTION_RIGHT:
              player_.move(game::Player::ANIMATION_RIGHT, bs);
              break;
            case game::IAPlayer::DIRECTION_DOWN:
              player_.move(game::Player::ANIMATION_DOWN, bs);
              break;
            case game::IAPlayer::DIRECTION_LEFT:
              player_.move(game::Player::ANIMATION_LEFT, bs);
              break;
            default:
              W() << _("Invalid movement.") << std::endl;
            }
          if (x == player_.getSprite().getX() && y == player_.getSprite().getY())
            player_.UTurn();
          else if (rand() % 100 == 0)
            player_.randomizeDirection();
          else if (rand() % 50 == 0)
            player_.putBomb(bs);
        }
    }

  }; // End of namespace ia
}; // End of namespace game

