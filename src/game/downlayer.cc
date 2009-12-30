/*!
 * \file  game/downlayer.cc
 *
 * @brief Implémentation de \c game::DownLayer .
 */

#include <cstring>

#include "game/downlayer.hh"
#include "game/map.hh"

#include "game/block.hh"
#include "game/bomb.hh"
#include "game/powerup.hh"
#include "utils/debug.hh"
#include "utils/portable.hh"


namespace game
{
  DownLayer::DownLayer (const Rect& renderingZone) :
    UpDownLayer (renderingZone)
  {
  }

  DownLayer::DownLayer (const DownLayer& dl) :
    UpDownLayer (dl.renderingZone_)
  {
  }

  DownLayer::~DownLayer()
  {
  }

  DownLayer& DownLayer::operator=(const DownLayer&)
  {
    return *this;
  }

  void DownLayer::render()
  {
    for (GameElementVec::const_iterator i = elements_.begin();
	 i != elements_.end(); ++i)
      (*i)->render();
  }

  DownLayer* DownLayer::loadFromXml(TiXmlElement* node, Map* map)
  {
    DownLayer* l = new DownLayer(map->getRenderingZone());

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
		ERROR () << "Erreur lors du chargement d'un élément de jeu"
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
		N() << "Element de jeu invalide détecté. ``"
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
