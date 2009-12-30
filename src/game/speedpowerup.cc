/*!
 * \file  game/speedpowerup.cc
 *
 * @brief Implémentation de \c game::SpeedPowerUp .
 */

#include <cassert>

#include "game/map.hh"
#include "game/speedpowerup.hh"

namespace game
{
  SpeedPowerUp::SpeedPowerUp() :
		PowerUp(SPEED_POWERUP_DATA_IMG)
  {
  }

  SpeedPowerUp::SpeedPowerUp(const SpeedPowerUp&) :
		PowerUp(SPEED_POWERUP_DATA_IMG)
  {
  }

  SpeedPowerUp::~SpeedPowerUp()
  {
  }

  SpeedPowerUp& SpeedPowerUp::operator=(const SpeedPowerUp&)
  {
  	return *this; //FIXME
  }

  void SpeedPowerUp::render()
  {
	sprite_.draw();
  }

  bool SpeedPowerUp::take(Player& player)
  {
	taken_ = true;
	sprite_.hide();
	player.setSpeed(player.getSpeed()+1);
	return true;
  }

  SpeedPowerUp* SpeedPowerUp::loadFromXml(TiXmlElement* node, Map* map)
  {
	SpeedPowerUp* res = new SpeedPowerUp();

	int x ,y;
	node->QueryIntAttribute("x", &x);
	node->QueryIntAttribute("y", &y);

	if (x < 0 || y < 0)
	{
          ERROR()
            << _("The following speedpowerup has an invalid position")
            << " (" << x << ";" << y << ")" << std::endl;
	  assert(0);
	}
	res->sprite_.setPosition(map->getRenderingZone().x + x,
                                 map->getRenderingZone().y + y);
	return res;
  }
};
