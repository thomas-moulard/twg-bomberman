#ifndef GAME_UPDOWNLAYER_HH_
# define GAME_UPDOWNLAYER_HH_
# include <list>
# include <tinyxml.h>

# include "game/layer.hh"
# include "game/gameelement.hh"
# include "game/player.hh"

namespace game
{
  /*!
   * Classe abstraite intermédiaire permettant
   * de factoriser du code en commun.
   */
  class UpDownLayer : public Layer
  {
  public:
    typedef std::list<GameElement*> GameElementVec;

    virtual bool isWalkable(int x, int y, int w = 0, int h = 0);
    virtual bool isDestructible(int x, int y, int w = 0, int h = 0);

    virtual void handleEvents(game::BattleScene& bs);

    virtual void pushGameElement(game::GameElement* e)
    {
      elements_.push_back(e);
    }

    virtual void removeBlocks(unsigned x, unsigned y);
    virtual void cleanup();

    virtual GameElementVec& getElements()
    {
      return elements_;
    }

  protected:
    UpDownLayer(Rect);
    UpDownLayer(const Layer&);

    virtual ~UpDownLayer();

    UpDownLayer& operator=(const UpDownLayer&);

    /*!
     *  \property   std::vector<GameElement*> elements_
     *
     *  @brief      Cet attribut regroupe tous les éléments interactifs
	 *              de ce layer.
     *  @sa         game::GameElement
     */
    GameElementVec elements_;
  };
};


#endif
