/*!
 * \file  game/bombpowerup.cc
 *
 * @brief Implémentation de \c game::BombPowerUp .
 */

#include <cassert>

#include "game/bombpowerup.hh"
#include "game/map.hh"

namespace game
{
  BombPowerUp::BombPowerUp() :
    PowerUp(BOMB_POWERUP_DATA_IMG)
  {
  }

  BombPowerUp::BombPowerUp(const BombPowerUp&) :
    PowerUp(BOMB_POWERUP_DATA_IMG)
  {
  }

  BombPowerUp::~BombPowerUp()
  {
  }

  BombPowerUp& BombPowerUp::operator=(const BombPowerUp&)
  {
    return *this;
  }

  void BombPowerUp::render()
  {
    sprite_.draw();
  }

  bool BombPowerUp::take(Player& player)
  {
    taken_ = true;
    sprite_.hide();
    player.setBomb(player.getBomb()+1);
    return true;
  }

  BombPowerUp* BombPowerUp::loadFromXml(TiXmlElement* node, Map* map)
  {
    BombPowerUp* res = new BombPowerUp();

    int x ,y;
    node->QueryIntAttribute("x", &x);
    node->QueryIntAttribute("y", &y);

    if (x < 0 || y < 0)
      {
        ERROR()
          << _("The following BombPowerUp has an invalid position")
          << " (" << x << ";" << y << ")" << std::endl;
	assert(0);
      }
    res->sprite_.setPosition(map->getRenderingZone().x + x,
                             map->getRenderingZone().y + y);
    return res;
  }
};
