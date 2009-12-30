#include "game/block.hh"

#include <cassert>

#include "game/map.hh"
#include "utils/debug.hh"
#include "utils/gettext.hh"

namespace game
{
  Block::Block() :
    GameElement(BLOCK_DATA_IMG, 0, 0)
  {
  }

  Block::Block(const Block&) :
    GameElement(BLOCK_DATA_IMG, 0, 0)
  {
  }

  Block::~Block()
  {
  }

  Block& Block::operator=(const Block&)
  {
    return *this;
  }

  void Block::render()
  {
    sprite_.draw();
  }

  Block* Block::loadFromXml(TiXmlElement* node, Map* map)
  {
    Block* res = new Block();
    int x ,y;
    node->QueryIntAttribute("x", &x);
    node->QueryIntAttribute("y", &y);

    if (x < 0 || y < 0)
      {
        ERROR()
          << _("The following block has an invalid position")
          << " (" << x << ";" << y << ")" << std::endl;
        assert(0);
      }
    res->sprite_.setPosition(map->getRenderingZone().x + x,
                             map->getRenderingZone().y + y);
    return res;
  }
};
