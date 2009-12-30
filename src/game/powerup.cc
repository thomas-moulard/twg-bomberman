#include <cassert>
#include <cstring>

#include "game/bombpowerup.hh"
#include "game/devilpowerup.hh"
#include "game/firepowerup.hh"
#include "game/minepowerup.hh"
#include "game/powerup.hh"
#include "game/shootpowerup.hh"
#include "game/speedpowerup.hh"
#include "game/throwpowerup.hh"

#include "utils/portable.hh"

namespace game
{
  PowerUp::PowerUp(const char* filename) :
	GameElement(filename, 0, 0),
	taken_(false)
  {
  }

  PowerUp::PowerUp(const PowerUp&) :
	GameElement()
  {
	assert(false);
  }

  PowerUp::~PowerUp()
  {
  }

  PowerUp& PowerUp::operator=(const PowerUp&)
  {
	assert(false);
	return *this;
  }

  PowerUp* PowerUp::loadFromXml(TiXmlElement* node, Map* map)
  {
	const char* attr = node->Attribute("type");

	if (!strcasecmp(attr,"BombPowerUp"))
	  return BombPowerUp::loadFromXml(node, map);
	if (!strcasecmp(attr,"DevilPowerUp"))
	  return DevilPowerUp::loadFromXml(node, map);
	if (!strcasecmp(attr,"FirePowerUp"))
	  return FirePowerUp::loadFromXml(node, map);
	if (!strcasecmp(attr,"MinePowerUp"))
	  return MinePowerUp::loadFromXml(node, map);
	if (!strcasecmp(attr,"ShootPowerUp"))
	  return ShootPowerUp::loadFromXml(node, map);
	if (!strcasecmp(attr,"SpeedPowerUp"))
	  return SpeedPowerUp::loadFromXml(node, map);
	if (!strcasecmp(attr,"ThrowPowerUp"))
	  return ThrowPowerUp::loadFromXml(node, map);
	else
	  return 0;
  }
};
