/*!
 * \file  game/firepowerup.cc
 *
 * @brief Implémentation de \c game::FirePowerUp .
 */

#include <cassert>

#include "game/firepowerup.hh"
#include "game/map.hh"

namespace game
{
  FirePowerUp::FirePowerUp() :
		PowerUp(FIRE_POWERUP_DATA_IMG)
  {
  }

  FirePowerUp::FirePowerUp(const FirePowerUp&) :
		PowerUp(FIRE_POWERUP_DATA_IMG)
  {
  }

  FirePowerUp::~FirePowerUp()
  {
  }

  FirePowerUp& FirePowerUp::operator=(const FirePowerUp&)
  {
    return *this; //FIXME
  }

  void FirePowerUp::render()
  {
    sprite_.draw();
  }

  bool FirePowerUp::take(Player& player)
  {
    taken_ = true;
    sprite_.hide();
    player.setFire(player.getFire()+1);
    return true;
  }

  FirePowerUp* FirePowerUp::loadFromXml(TiXmlElement* node, Map* map)
  {
    FirePowerUp* res = new FirePowerUp();

    int x ,y;
    node->QueryIntAttribute("x", &x);
    node->QueryIntAttribute("y", &y);

    if (x < 0 || y < 0)
      {
        ERROR()
          << _("The following FirePowerUp has an invalid position")
          << " (" << x << ";" << y << ")" << std::endl;
        assert(0);
      }
    res->sprite_.setPosition(map->getRenderingZone().x + x,
                             map->getRenderingZone().y + y);
    return res;
  }
};
