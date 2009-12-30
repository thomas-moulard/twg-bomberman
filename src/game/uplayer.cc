/*!
 * \file  game/uplayer.cc
 *
 * @brief Impl√©mentation de \c game::UpLayer .
 */

#include <cstring>

#include "game/uplayer.hh"

#include "game/block.hh"
#include "game/bomb.hh"
#include "game/map.hh"
#include "game/powerup.hh"
#include "utils/debug.hh"
#include "utils/portable.hh"

namespace game
{
  UpLayer::UpLayer (const Rect& renderingZone) :
    UpDownLayer (renderingZone)
  {
  }

  UpLayer::UpLayer (const UpLayer& ul) :
    UpDownLayer (ul.renderingZone_)
  {
  }

  UpLayer::~UpLayer ()
  {
  }

  UpLayer& UpLayer::operator=(const UpLayer&)
  {
  	return *this; //FIXME
  }

  void UpLayer::render()
  {
    for (GameElementVec::const_iterator i = elements_.begin();
	 i != elements_.end(); ++i)
      (*i)->render();
  }

  UpLayer* UpLayer::loadFromXml(TiXmlElement* node, Map* map)
  {
    UpLayer* l = new UpLayer(map->getRenderingZone());

    if (strcasecmp(node->Value(), "layer"))
      {
	ERROR() << "Erreur lors du chargement du layer haut. ``"
		<< node->Value() << "''"
		<< std::endl;
	return l;
      }
    node = node->FirstChildElement();

    while(node)
      {
	if (!strcasecmp(node->Value(), "gameelement"))
	  {
	    const char * t = node->Attribute ("type");
	    if (!t)
	      {
		ERROR () << "Erreur lors du chargement d'un ÈlÈment de jeu"
			 << std::endl;
		assert(0);
	      }

	    if (!strcasecmp(t, "block"))
	      l->elements_.push_back(Block::loadFromXml(node, map));
	    else if (strlen(t) > strlen("powerup") && !strcasecmp(t + strlen(t) - strlen("powerup"), "powerup"))
	      l->elements_.push_back(PowerUp::loadFromXml(node, map));
	    else if (strlen(t) > strlen("bomb") && !strcasecmp(t + strlen(t) - strlen("bomb"), "bomb"))
	      l->elements_.push_back(Bomb::loadFromXml(node, map));
	    else
	      {
		N() << "Element de jeu invalide d√©tect√©. ``"
		    << t << "''"
		    << std::endl;
		assert(0);
	      }
	  }
	node = node->NextSiblingElement();
      }
    return l;
  }
};
