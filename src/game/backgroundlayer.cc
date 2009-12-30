/*!
 * \file  game/backgroundlayer.cc
 *
 * @brief Implémentation de \c game::BackgroundLayer .
 */

#include <cmath>
#include <cstring>

#include "game/backgroundlayer.hh"
#include "game/map.hh"

#include "graphic/imageelement.hh"
#include "utils/debug.hh"
#include "utils/pathmanager.hh"
#include "utils/portable.hh"

namespace game
{
  BackgroundLayer::BackgroundLayer(const Rect& renderingZone) :
    Layer(renderingZone)
  {
  }

  BackgroundLayer::BackgroundLayer(const BackgroundLayer& bl) :
    Layer(bl.renderingZone_)
  {
  }

  BackgroundLayer::~BackgroundLayer()
  {
  }

  BackgroundLayer& BackgroundLayer::operator=(const BackgroundLayer&)
  {
  	return *this; //FIXME
  }

  void BackgroundLayer::render()
  {
    for (TileVec::const_iterator i = tiles_.begin(); i != tiles_.end(); ++i)
      (*i)->draw();
  }

  bool
  BackgroundLayer::isWalkable(int x, int y, int w, int h)
  {
    int ntilex_tl = (x - renderingZone_.x) / Map::SIZE_TILE_X;
    int ntiley_tl = (y - renderingZone_.y) / Map::SIZE_TILE_Y;
    if (ntiley_tl % 2 == 1 && ntilex_tl % 2 == 1)
      return false;

    int ntilex_tr = (x - renderingZone_.x + w - 1) / Map::SIZE_TILE_X;
    int ntiley_tr = (y - renderingZone_.y) / Map::SIZE_TILE_Y;
    if (ntiley_tr % 2 == 1 && ntilex_tr % 2 == 1)
      return false;

    int ntilex_bl = (x - renderingZone_.x) / Map::SIZE_TILE_X;
    int ntiley_bl = (y - renderingZone_.y + h - 1) / Map::SIZE_TILE_Y;
    if (ntiley_bl % 2 == 1 && ntilex_bl % 2 == 1)
      return false;

    int ntilex_br = (x - renderingZone_.x + w - 1) / Map::SIZE_TILE_X;
    int ntiley_br = (y - renderingZone_.y + h - 1) / Map::SIZE_TILE_Y;
    if (ntiley_br % 2 == 1 && ntilex_br % 2 == 1)
      return false;
    return true;
  }

  bool
  BackgroundLayer::isDestructible(int x, int y, int w, int h)
  {
    return isWalkable(x, y, w, h);
  }

  BackgroundLayer* BackgroundLayer::loadFromXml(TiXmlElement* node, Map* map)
  {
    BackgroundLayer* res = new BackgroundLayer(map->getRenderingZone());

    if (strcasecmp(node->Value(), "layer"))
      {
	ERROR() << "Erreur lors du chargement du layer de fond. ``"
		<< node->Value() << "''"
		<< std::endl;
	return res;
      }
    node = node->FirstChildElement();

    while(node)
      {
	if (!strcasecmp(node->Value(), "imageelement"))
	  {
	    int x, y;
	    const char* src = node->Attribute ("src");
	    node->QueryIntAttribute("x", &x);
	    node->QueryIntAttribute("y", &y);
	    if (x < 0 || y < 0)
	      {
		E() << "Un élément de fond a une position incorrecte. ("
		    << x << ";" << y << ")" << std::endl;
		assert(0);
	      }
	    graphic::ImageElement* ie = new graphic::ImageElement(
                            utils::PathManager::getDataFilename(src).c_str());
	    ie->setPosition(map->getRenderingZone().x + x * ie->getWidth(),
                            map->getRenderingZone().y + y * ie->getHeight());
	    res->tiles_.push_back(ie);
	  }
	else
	  {
	    N() << "Element inconnu rencontré dans le layer de fond. ``"
		<< node->Value() << "''" << std::endl;
	  }
	node = node->NextSiblingElement();
      }

    return res;
  }

  void
  BackgroundLayer::handleEvents(game::BattleScene&)
  {
  }
};
