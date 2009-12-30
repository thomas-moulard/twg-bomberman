/*!
 * \file  game/devilpowerup.cc
 *
 * @brief Implémentation de \c game::DevilPowerUp .
 */

#include <cassert>

#include "core/inputmanager.hh"
#include "game/devilpowerup.hh"
#include "game/map.hh"

namespace game
{
  DevilPowerUp::DevilPowerUp() :
    PowerUp(DEVIL_POWERUP_DATA_IMG)
  {
  }

  DevilPowerUp::DevilPowerUp(const DevilPowerUp&) :
    PowerUp(DEVIL_POWERUP_DATA_IMG)
  {
  }

  DevilPowerUp::~DevilPowerUp()
  {
  }

  DevilPowerUp& DevilPowerUp::operator=(const DevilPowerUp&)
  {
    return *this; //FIXME
  }

  void DevilPowerUp::render()
  {
    sprite_.draw();
  }

  bool DevilPowerUp::take(Player& player)
  {
    taken_ = true;
    sprite_.hide();

    unsigned delay = rand() % 20000;

    core::InputManager *im = im->get_instance();
    im->inverseInput(player.getId(),delay);
    return true;
  }

  DevilPowerUp* DevilPowerUp::loadFromXml(TiXmlElement* node, Map* map)
  {
    DevilPowerUp* res = new DevilPowerUp();

    int x ,y;
    node->QueryIntAttribute("x", &x);
    node->QueryIntAttribute("y", &y);

    if (x < 0 || y < 0)
      {
        ERROR()
          << _("The following DevilPowerUp has an invalid position")
          << " (" << x << ";" << y << ")" << std::endl;
        assert(0);
      }
    res->sprite_.setPosition(map->getRenderingZone().x + x,
                             map->getRenderingZone().y + y);
    return res;
  }
};
