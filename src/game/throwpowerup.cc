/*!
 * \file  game/throwpowerup.cc
 *
 * @brief Implémentation de \c game::ThrowPowerUp .
 */

#include <cassert>

#include "game/throwpowerup.hh"
#include "game/map.hh"

namespace game
{
  ThrowPowerUp::ThrowPowerUp() :
    PowerUp(THROW_POWERUP_DATA_IMG)
  {
  }

  ThrowPowerUp::ThrowPowerUp(const ThrowPowerUp&) :
    PowerUp(THROW_POWERUP_DATA_IMG)
  {
  }

  ThrowPowerUp::~ThrowPowerUp()
  {
  }
  
  ThrowPowerUp& ThrowPowerUp::operator=(const ThrowPowerUp&)
  {
  	return *this; //FIXME
  }

  void ThrowPowerUp::render()
  {
	sprite_.draw();
  }

  bool ThrowPowerUp::take(Player& player)
  {
	taken_ = true;
	sprite_.hide();
	player.setThrow(true);
	return true;
  }
	
  ThrowPowerUp* ThrowPowerUp::loadFromXml(TiXmlElement* node, Map* map)
  {
	ThrowPowerUp* res = new ThrowPowerUp();

	int x ,y;
	node->QueryIntAttribute("x", &x);
	node->QueryIntAttribute("y", &y);

	if (x < 0 || y < 0)
	{
          ERROR()
            << _("The following throwpowerup has an invalid position")
            << " (" << x << ";" << y << ")" << std::endl;
	  assert(0);
	}
	res->sprite_.setPosition(map->getRenderingZone().x + x,
                                 map->getRenderingZone().y + y);
	return res;
  }
};
