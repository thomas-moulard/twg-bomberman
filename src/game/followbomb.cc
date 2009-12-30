/*!
 * \file  game/followbomb.cc
 *
 * @brief Implémentation de \c game::FollowBomb .
 */

#include <cassert>

#include "game/followbomb.hh"
#include "game/map.hh"

namespace game
{
  FollowBomb::FollowBomb(game::Player* owner) :
    Bomb(owner, FOLLOW_BOMB_DATA_IMG)
  {
  }

  FollowBomb::FollowBomb(const FollowBomb& fb) :
    Bomb(fb.owner_, FOLLOW_BOMB_DATA_IMG)
  {
  }

  FollowBomb::~FollowBomb()
  {
  }

  FollowBomb& FollowBomb::operator=(const FollowBomb&)
  {
    return *this;
  }

  void FollowBomb::render()
  {
    sprite_.draw();
  }

  FollowBomb* FollowBomb::loadFromXml(TiXmlElement* node, Map* map)
  {
    FollowBomb* res = new FollowBomb(0);

    int x ,y;
    node->QueryIntAttribute("x", &x);
    node->QueryIntAttribute("y", &y);

    if (x < 0 || y < 0)
      {
        ERROR()
          << _("The following FollowBomb has an invalid position")
          << " (" << x << ";" << y << ")" << std::endl;
        assert(0);
      }
    res->sprite_.setPosition(map->getRenderingZone().x + x,
                             map->getRenderingZone().y + y);
    return res;
  }
};
