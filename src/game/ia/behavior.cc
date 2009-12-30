/*!
 * \file  game/ia/behavior.cc
 *
 * @brief Implémentation de \c game::ia::Behavior.
 */
#include "game/ia/behavior.hh"

namespace game
{
  namespace ia
  {
    Behavior::Behavior(game::IAPlayer& player) :
      player_ (player)
    {
    }

    Behavior::Behavior(const Behavior& b) :
      player_ (b.player_)
    {
    }

    Behavior::~Behavior()
    {
    }

    Behavior&
    Behavior::operator=(const Behavior&)
    {
      return *this;
    }
  }; // End of namespace ia
}; // End of namespace game

