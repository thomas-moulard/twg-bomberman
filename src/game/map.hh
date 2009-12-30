#ifndef GAME_MAP_HH_
# define GAME_MAP_HH_
# include <vector>
# include "game/fwd.hh"
# include "game/layer.hh"
# include "game/player.hh"
# include "graphic/fwd.hh"
# include "graphic/graphicmanager.hh"

namespace game
{
  class Bomb;
  class GameElement;
  class Layer;

  class Map
  {
  public:
    typedef graphic::GraphicManager::Rect Rect;
    typedef std::vector<Layer*> layer_t;

    explicit Map();
    explicit Map(const Map&);

    ~Map();

    Map& operator=(const Map&);

    void render();
    bool isWalkable(int x, int y, int w, int h) const;
    bool isDestructible(int x, int y, int w, int h) const;
    void handleEvents(game::BattleScene& bs);

    void removeBlocks(unsigned x, unsigned y);

    layer_t& getLayers()
    {
      return layers_;
    }

    int getWidth() const
    {
      return width_;
    }

    int getHeight() const
    {
      return height_;
    }

    game::GameElement* pickElement(unsigned l,
                                   int x, int y,
                                   int w, int h) const;

    bool isValidPosition(int x, int y) const;
    bool isValidPosition(int x, int y, int w, int h) const;
    bool isEscapingFromCollision(unsigned x, unsigned y,
                         unsigned w, unsigned h) const;

    bool isSameTile(unsigned, unsigned,
                    unsigned, unsigned,
                    unsigned, unsigned) const;

    void printCollisionMap() const;

    const Rect& getRenderingZone() const;

    unsigned getPlayerInitialPositionX(unsigned) const;
    unsigned getPlayerInitialPositionY(unsigned) const;

    static Map* loadFromXml(const char* filename);
    static void loadSettingsFromXml(TiXmlElement*, Map*);

    static const unsigned SIZE_TILE_X = 32;
    static const unsigned SIZE_TILE_Y = 32;
  private:
    layer_t layers_;

    int width_;
    int height_;

    Rect renderingZone_;

    graphic::ImageElement* bg_;
  };
};


#endif
