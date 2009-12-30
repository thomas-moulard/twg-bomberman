/*!
 * \file  game/shootpowerup.cc
 *
 * @brief Implémentation de \c game::ShootPowerUp .
 */

#include <cassert>

#include "game/map.hh"
#include "game/shootpowerup.hh"

namespace game
{
  ShootPowerUp::ShootPowerUp() :
		PowerUp(SHOOT_POWERUP_DATA_IMG)
  {
  }

  ShootPowerUp::ShootPowerUp(const ShootPowerUp&) :
		PowerUp(SHOOT_POWERUP_DATA_IMG)
  {
  }

  ShootPowerUp::~ShootPowerUp()
  {
  }

  ShootPowerUp& ShootPowerUp::operator=(const ShootPowerUp&)
  {
  	return *this; //FIXME
  }

  void ShootPowerUp::render()
  {
	sprite_.draw();
  }

  bool ShootPowerUp::take(Player& player)
  {
	taken_ = true;
	sprite_.hide();
	player.setShoot(true);
	return true;
  }

  ShootPowerUp* ShootPowerUp::loadFromXml(TiXmlElement* node, Map* map)
  {
	ShootPowerUp* res = new ShootPowerUp();

	int x ,y;
	node->QueryIntAttribute("x", &x);
	node->QueryIntAttribute("y", &y);

	if (x < 0 || y < 0)
	{
          ERROR()
            << _("The following ShootPowerUp has an invalid position")
            << " (" << x << ";" << y << ")" << std::endl;
	  assert(0);
	}
	res->sprite_.setPosition(map->getRenderingZone().x + x,
                                 map->getRenderingZone().y + y);
	return res;
  }
};
