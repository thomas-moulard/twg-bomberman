/*!
 * \file  game/minepowerup.cc
 *
 * @brief Implémentation de \c game::MinePowerUp .
 */

#include <cassert>

#include "game/map.hh"
#include "game/minepowerup.hh"
#include "game/minebomb.hh"

namespace game
{
  MinePowerUp::MinePowerUp() :
    PowerUp(MINE_POWERUP_DATA_IMG)
  {
  }

  MinePowerUp::MinePowerUp(const MinePowerUp&) :
    PowerUp(MINE_POWERUP_DATA_IMG)
  {
  }

  MinePowerUp::~MinePowerUp()
  {
  }

  MinePowerUp& MinePowerUp::operator=(const MinePowerUp&)
  {
    return *this; //FIXME
  }

  void MinePowerUp::render()
  {
    sprite_.draw();
  }

  bool MinePowerUp::take(Player& player)
  {
    taken_ = true;
    sprite_.hide();
    player.setBombType(&game::Bomb::create<MineBomb>);
    return true;
  }

  MinePowerUp* MinePowerUp::loadFromXml(TiXmlElement* node, Map* map)
  {
    MinePowerUp* res = new MinePowerUp();

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
