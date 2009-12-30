#include <cassert>

#include "game/classicbomb.hh"
#include "game/map.hh"

namespace game
{
  ClassicBomb::ClassicBomb(game::Player* owner) :
	Bomb(owner, CLASSIC_BOMB_DATA_IMG)
  {
    sprite_.setFrameLength(500);
    sprite_.animation_play();
  }

  ClassicBomb::ClassicBomb(const ClassicBomb& cb) :
	Bomb(cb.owner_, CLASSIC_BOMB_DATA_IMG)
  {
  }

  ClassicBomb::~ClassicBomb()
  {
  }

  ClassicBomb& ClassicBomb::operator=(const ClassicBomb&)
  {
	return *this;
  }

  ClassicBomb* ClassicBomb::loadFromXml(TiXmlElement* node, Map* map)
  {
	ClassicBomb* res = new ClassicBomb(0);

	int x ,y;
	node->QueryIntAttribute("x",&x);
	node->QueryIntAttribute("y",&y);

	if (x < 0 || y < 0)
	{
          ERROR()
            << _("The following ClassicBomb has an invalid position")
            << " (" << x << ";" << y << ")" << std::endl;
	  assert(0);
	}
	res->sprite_.setPosition(map->getRenderingZone().x + x,
                                 map->getRenderingZone().y + y);
	return res;
  }
}
