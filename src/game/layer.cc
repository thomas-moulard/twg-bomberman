#include <cstring>

#include "game/layer.hh"
#include "game/powerup.hh"

#include "game/backgroundlayer.hh"
#include "game/uplayer.hh"
#include "game/downlayer.hh"
#include "utils/debug.hh"
#include "utils/portable.hh"

namespace game
{
  Layer::Layer(const Rect& renderingZone) :
    renderingZone_ (renderingZone)
  {
  }

  Layer::~Layer()
  {
  }

  Layer* Layer::loadFromXml(TiXmlElement* node, Map* map)
  {
    assert(!!node);

    if (strcasecmp(node->Value(), "layer"))
      {
	W() << "Erreur lors du chargement des layer"
	    << std::endl;
	assert(0);
	return 0;
      }
    int id;
    node->QueryIntAttribute ("id", &id);

    Layer* l;
    switch (id)
      {
      case 0:
	l = BackgroundLayer::loadFromXml(node, map);
	break;
      case 1:
	l = DownLayer::loadFromXml(node, map);
	break;
      case 2:
	l = UpLayer::loadFromXml(node, map);
	break;
      default:
	ERROR() << _("Error while loading the map.")
                << std::endl;
	assert(0);
	break;
      }
    return l;
  }
};
