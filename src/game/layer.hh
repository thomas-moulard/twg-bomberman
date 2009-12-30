#ifndef GAME_LAYER_HH_
# define GAME_LAYER_HH_
# include <vector>
# include <tinyxml.h>

# include "game/fwd.hh"
# include "game/gameelement.hh"
# include "game/player.hh"
# include "graphic/graphicmanager.hh"

namespace game
{
  class Layer
  {
  public:
    typedef graphic::GraphicManager::Rect Rect;

    explicit Layer(const Rect& renderingZone);
    explicit Layer(const Layer&);

    virtual ~Layer();

    Layer& operator=(const Layer&);

    virtual void render() = 0;
    virtual bool isWalkable(int x, int y, int w = 0, int h = 0) = 0;
    virtual bool isDestructible(int x, int y, int w = 0, int h = 0) = 0;

    virtual void handleEvents(game::BattleScene& bs) = 0;

    virtual void removeBlocks(unsigned x, unsigned y) = 0;

    static Layer* loadFromXml(TiXmlElement*, Map*);
  protected:
    Rect renderingZone_;
  };
};


#endif
