/*!
 * \file  game/minebomb.cc
 *
 * @brief Implémentation de \c game::MineBomb .
 */

#include <cassert>

#include "game/map.hh"
#include "game/minebomb.hh"

namespace game
{
  MineBomb::MineBomb(game::Player* owner) :
    Bomb(owner, MINE_BOMB_DATA_IMG),
    activationTimer_ (getActivationDelay()),
    touched_ (false)
  {
    timer_.reset(0);
    sprite_.hide();
  }

  MineBomb::MineBomb(const MineBomb& mb) :
    Bomb(mb.owner_, MINE_BOMB_DATA_IMG),
    activationTimer_ (getActivationDelay()),
    touched_ (false)
  {
  }

  MineBomb::~MineBomb()
  {
  }

  MineBomb& MineBomb::operator=(const MineBomb&)
  {
  	return *this;
  }

  void
  MineBomb::onTouch(game::BattleScene& bs, game::Player& pl)
  {
    parent::onTouch(bs, pl);

    if (!touched_ && activationTimer_.is_time(false))
      {
        touched_ = true;
        timer_.reset(getExplodeDelay());
        sprite_.show();
        sprite_.animation_play();
      }
  }

  bool
  MineBomb::isWalkable(int x, int y, int w, int h) const
  {
    if (state_ == BOMB_IDLE)
      return true;
    return parent::isWalkable(x, y, w, h);
  }

  unsigned
  MineBomb::getActivationDelay() const
  {
    return 3000;
  }

  MineBomb* MineBomb::loadFromXml(TiXmlElement* node, Map* map)
  {
    MineBomb* res = new MineBomb(0);

    int x ,y;
    node->QueryIntAttribute("x",&x);
    node->QueryIntAttribute("y",&y);

    if (x < 0 || y < 0)
      {
        ERROR()
          << _("The following MineBomb has an invalid position")
          << " (" << x << ";" << y << ")" << std::endl;
        assert(0);
      }
    res->sprite_.setPosition(map->getRenderingZone().x + x,
                             map->getRenderingZone().y + y);
    return res;
  }
};
