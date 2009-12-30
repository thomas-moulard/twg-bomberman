#include <iostream>
#include <cstring>

#include "core/configmanager.hh"
#include "game/bomb.hh"
#include "game/bombpowerup.hh"
#include "game/devilpowerup.hh"
#include "game/firepowerup.hh"
#include "game/map.hh"
#include "game/minepowerup.hh"
#include "game/speedpowerup.hh"
#include "game/updownlayer.hh"
#include "graphic/imageelement.hh"
#include "utils/debug.hh"
#include "utils/pathmanager.hh"
#include "utils/portable.hh"

namespace game
{
  Map::Map() :
    layers_ (),
    width_ (),
    height_ (),
    renderingZone_ (),
    bg_ (0)
  {
    core::ConfigManager* cm = core::ConfigManager::get_instance();
    graphic::GraphicManager* gm = graphic::GraphicManager::get_instance();

    renderingZone_.x = cm->getIntFromConfigurationFile(
                       "game", "Map", "renderingZone_.x");
    renderingZone_.y = cm->getIntFromConfigurationFile(
                       "game", "Map", "renderingZone_.y");
    renderingZone_.w = cm->getIntFromConfigurationFile(
                       "game", "Map", "renderingZone_.w");
    renderingZone_.h = cm->getIntFromConfigurationFile(
                       "game", "Map", "renderingZone_.h");

    if (!renderingZone_.w)
      renderingZone_.w = gm->getScreenWidth() - renderingZone_.x;
    if (!renderingZone_.h)
      renderingZone_.h = gm->getScreenHeight() - renderingZone_.y;
  }

  Map::Map(const Map& new_map)
  {
    for(unsigned int i = 0; i < new_map.layers_.size(); i++)
      layers_[i] = new_map.layers_[i];
  }

  Map& Map::operator= (const Map& new_map)
  {
    for(unsigned int i = 0; i < new_map.layers_.size(); i++)
      layers_[i] = new_map.layers_[i];
    return *this;
  }

  void Map::render()
  {
    if (bg_)
      bg_->draw();
    for(unsigned int i = 0; i < layers_.size(); i++)
      layers_[i]->render();
  }

  bool
  Map::isWalkable(int x, int y, int w, int h) const
  {
    return (isValidPosition(x, y, w, h) &&
            layers_[0]->isWalkable(x, y, w, h) &&
            layers_[1]->isWalkable(x, y, w, h) &&
            layers_[2]->isWalkable(x, y, w, h));
  }

  bool
  Map::isDestructible(int x, int y, int w, int h) const
  {
    return (isValidPosition(x, y, w, h) &&
            layers_[0]->isDestructible(x, y, w, h) &&
            layers_[1]->isDestructible(x, y, w, h) &&
            layers_[2]->isDestructible(x, y, w, h));
  }

  void
  Map::handleEvents(game::BattleScene& bs)
  {
    for (layer_t::const_iterator it = layers_.begin();
         it < layers_.end(); ++it)
      (*it)->handleEvents(bs);
  }

  void
  Map::removeBlocks(unsigned x, unsigned y)
  {
    for (layer_t::iterator it = layers_.begin();
         it < layers_.end(); ++it)
      (*it)->removeBlocks(x, y);
  }

  game::GameElement*
  Map::pickElement(unsigned l, int x, int y, int w, int h) const
  {
    if (l >= layers_.size() || !isValidPosition(x, y, w, h))
      return 0;

    game::UpDownLayer* udl = dynamic_cast<game::UpDownLayer*>(layers_[l]);

    for (game::UpDownLayer::GameElementVec::iterator it =
           udl->getElements().begin();
         it != udl->getElements().end(); ++it)
      if ((*it)->collide(x, y, w, h))
        return *it;
    return 0;
  }

  bool
  Map::isValidPosition(int x, int y, int w, int h) const
  {
    return (isValidPosition(x, y) &&
            isValidPosition(x+w, y) &&
            isValidPosition(x, y+h) &&
            isValidPosition(x+w, y+h));
  }

  bool
  Map::isValidPosition(int x, int y) const
  {
    const int wm = width_*SIZE_TILE_X;
    const int hm = height_*SIZE_TILE_Y;

    return (x >= 0 &&
            y >= 0 &&
            x >= renderingZone_.x &&
            y >= renderingZone_.y &&
            x <= renderingZone_.x+renderingZone_.w &&
            y <= renderingZone_.y+renderingZone_.h &&
            x <= renderingZone_.x+wm &&
            y <= renderingZone_.y+hm);
  }

  bool Map::isEscapingFromCollision(unsigned x, unsigned y,
                            unsigned w, unsigned h) const
  {
    if (isWalkable(x, y, w, h))
      return true;

    if (!isWalkable(x, y, 0, 0)
        && (!dynamic_cast<game::Bomb*>(pickElement(2, x, y, 0, 0))))
      return false;
    if (!isWalkable(x+w-1, y, 0, 0)
        && (!dynamic_cast<game::Bomb*>(pickElement(2, x+w-1, y, 0, 0))))
      return false;
    if (!isWalkable(x, y+h-1, 0, 0)
        && (!dynamic_cast<game::Bomb*>(pickElement(2, x, y+h-1, 0, 0))))
      return false;
    if (!isWalkable(x+w-1, y+h-1, 0, 0)
        && (!dynamic_cast<game::Bomb*>(pickElement(2, x+w-1, y+h-1, 0, 0))))
      return false;
    return true;
  }

  bool
  Map::isSameTile(unsigned x, unsigned y,
                  unsigned prevx, unsigned prevy,
                  unsigned w, unsigned h) const
  {
    const unsigned rx = x/SIZE_TILE_X;
    const unsigned ry = y/SIZE_TILE_Y;
    const unsigned rprevx = prevx/SIZE_TILE_X;
    const unsigned rprevy = prevy/SIZE_TILE_Y;

    const unsigned rx2 = (x+w)/SIZE_TILE_X;
    const unsigned ry2 = (y+h)/SIZE_TILE_Y;
    const unsigned rprevx2 = (prevx+w)/SIZE_TILE_X;
    const unsigned rprevy2 = (prevy+h)/SIZE_TILE_Y;

    return ((rx == rprevx)
            && (rx2 == rprevx2)
            && (ry == rprevy)
            && (ry2 == rprevy2));
  }

  void
  Map::printCollisionMap() const
  {
    const int w = SIZE_TILE_X;
    const int h = SIZE_TILE_Y;

    for (int i = 0; i < 79; ++i)
      DEBUG() << "-";
    DEBUG() << std::endl;

    for (int y = 0; y < getHeight()*h; y += h)
      {
        for (int x = 0; x < getWidth()*w; x += w)
          {
            int res = 1*(!layers_[0]->isWalkable(x, y, w, h))
              + 2*(!layers_[1]->isWalkable(x, y, w, h))
              + 4*(!layers_[2]->isWalkable(x, y, w, h));

            if (res == 0)
              DEBUG() << " ";
            else
              DEBUG() << res;
          }
        DEBUG() << std::endl;
      }
    for (int i = 0; i < 79; ++i)
      DEBUG() << "-";
    DEBUG() << std::endl;
  }

  const Map::Rect&
  Map::getRenderingZone() const
  {
    return renderingZone_;
  }

  unsigned
  Map::getPlayerInitialPositionX(unsigned id) const
  {
    const unsigned xmax = (getWidth()-1)*SIZE_TILE_X;

    switch (id)
      {
      case 0:
      case 2:
        return getRenderingZone().x;
        break;

      case 1:
      case 3:
        return getRenderingZone().x+xmax-1;
        break;
      };

    WARNING() << _("Unexpected player id.") << std::endl;
    return 0;
  }


  unsigned
  Map::getPlayerInitialPositionY(unsigned id) const
  {
    const unsigned ymax = (getHeight()-1)*SIZE_TILE_Y;

    switch (id)
      {
      case 0:
      case 1:
        return getRenderingZone().y;
        break;

      case 2:
      case 3:
        return getRenderingZone().y+ymax-1;
        break;
      };

    WARNING() << _("Unexpected player id.") << std::endl;
    return 0;
  }

  Map*
  Map::loadFromXml(const char* filename)
  {
    Map* map = new Map();

    TiXmlDocument* doc = new TiXmlDocument;
    if (!doc->LoadFile(filename))
      {
        ERROR() << "Impossible de charger la carte ``"
                << filename
                << "''"
                << std::endl;
        return 0;
      }

    TiXmlElement* node = doc->RootElement();

    if (strcasecmp(node->Value(), "map"))
      {
	ERROR() << _("Invalid root in XML file. ``")
		<< node->Value() << "''"
		<< std::endl;
	return map;
      }

    node->QueryIntAttribute ("width", &map->width_);
    node->QueryIntAttribute ("height", &map->height_);

    const char* bg = node->Attribute ("background");
    if (!bg)
      bg = "/img/bg-fixme.png";
    map->bg_ = new graphic::ImageElement(
                 utils::PathManager::getDataFilename(bg).c_str());
    map->bg_->setPosition(0, 0);

    node = node->FirstChildElement();

    map->layers_.resize(3);

    while(node)
      {
	if (!strcasecmp(node->Value(), "layer"))
	  {
	    int id;
	    node->QueryIntAttribute ("id", &id);
	    if (id < 0 || id > 2)
	      {
		E() << _("Error while loading the map.")
		    << std::endl;
		assert(0);
	      }
	    Layer* l = Layer::loadFromXml(node, map);
	    map->layers_[id] = l;
	  }
	node = node->NextSiblingElement();
      }

    TiXmlHandle mapHandle(doc);
    TiXmlElement* settings =
      mapHandle.FirstChild("Map").FirstChild("Settings").Element();
    loadSettingsFromXml(settings, map);
    return map;
  }

  void
  Map::loadSettingsFromXml(TiXmlElement* node, Map* map)
  {
    if (!node)
      return;
    node = node->FirstChildElement();

    while(node)
      {
	if (!strcasecmp(node->Value(), "randomseed"))
	  {
	    int seed;
	    node->QueryIntAttribute ("value", &seed);
            srand(seed);
	  }
        else if (!strcasecmp(node->Value(), "itemprobability"))
          {
            int value;
	    node->QueryIntAttribute ("value", &value);
            const char* type = node->Attribute("type");
            if (map->layers_.size() > 1)
              {
                game::UpDownLayer* udl =
                  dynamic_cast<game::UpDownLayer*>(map->layers_[1]);
                for (int x = 0; x < map->width_*SIZE_TILE_X; x += SIZE_TILE_X)
                  for (int y = 0; y < map->height_*SIZE_TILE_Y;
                       y += SIZE_TILE_Y)
                    if (map->isDestructible(map->getRenderingZone().x+x,
                                            map->getRenderingZone().y+y,
                                            SIZE_TILE_X,
                                            SIZE_TILE_Y) &&
                        dynamic_cast<PowerUp*>(map->pickElement(1,
                                         map->getRenderingZone().x+x,
                                         map->getRenderingZone().y+y,
                                         SIZE_TILE_X,
                                         SIZE_TILE_Y)) == 0 &&
                        dynamic_cast<PowerUp*>(map->pickElement(2,
                                         map->getRenderingZone().x+x,
                                         map->getRenderingZone().y+y,
                                         SIZE_TILE_X,
                                         SIZE_TILE_Y)) == 0 &&
                        rand()%100 <= value)
                      {
                        if (!strcasecmp(type, "firepowerup"))
                          udl->pushGameElement(new game::FirePowerUp());
                        else if (!strcasecmp(type, "speedpowerup"))
                          udl->pushGameElement(new game::SpeedPowerUp());
                        else if (!strcasecmp(type, "devilpowerup"))
                          udl->pushGameElement(new game::DevilPowerUp());
                        else if (!strcasecmp(type, "bombpowerup"))
                          udl->pushGameElement(new game::BombPowerUp());
                        else if (!strcasecmp(type, "minepowerup"))
                          udl->pushGameElement(new game::MinePowerUp());

                        udl->getElements().back()->getSprite().
                          setPosition(
                                      map->getRenderingZone().x+x,
                                      map->getRenderingZone().y+y);
                      }
              }
          }
	node = node->NextSiblingElement();
      }
  }

  Map::~Map()
  {

  }
}
