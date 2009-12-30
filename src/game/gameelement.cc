/*!
 * \file  game/gameelement.hh
 *
 * @brief Déclaration de \c game::GameElement .
 */
#include "game/gameelement.hh"
#include <cstring>

//Attention à l'ordre des inclusions
//il s'agit d'inclusions réciproques!
#include "game/block.hh"
#include "game/bomb.hh"
#include "game/powerup.hh"

namespace game
{
  GameElement::GameElement() :
	sprite_ (0, 0, 0)
  {
  }

  GameElement::GameElement(const char* filename, unsigned frameSizeX, unsigned frameSizeY) :
	sprite_ (filename, frameSizeX, frameSizeY)
  {
  }

  GameElement::GameElement(const GameElement& clone) :
	sprite_ (clone.sprite_)
  {
  }

  GameElement::~GameElement()
  {
  }

  GameElement& GameElement::operator=(const GameElement& clone)
  {
  	sprite_ = clone.sprite_;
	return *this;
  }

  GameElement* GameElement::loadFromXml(TiXmlElement* node, Map* map)
  {
    const char* attr;
    attr = node->Attribute("type");
    if (strcmp("Block", attr))
      return Block::loadFromXml(node, map);

    if (strlen(attr) > strlen("PowerUp") && !strcmp(attr + strlen(attr) -
                                         strlen("PowerUp"), "PowerUp"))
      return PowerUp::loadFromXml(node, map);

    if (strlen(attr) > strlen("Bomb") && !strcmp(attr + strlen(attr) -
                                            strlen("Bomb"), "Bomb"))
      return Bomb::loadFromXml(node, map);
    return 0;
  }
};
