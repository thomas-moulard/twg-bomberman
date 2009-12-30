#include <cstring>

#include "game/battlescene.hh"
#include "game/block.hh"
#include "game/bomb.hh"
#include "game/updownlayer.hh"
#include "utils/debug.hh"
#include "utils/portable.hh"

namespace game
{
  UpDownLayer::UpDownLayer (Rect renderingZone) :
    Layer (renderingZone)
  {
  }

  UpDownLayer::~UpDownLayer ()
  {
  }

  bool
  UpDownLayer::isWalkable(int x, int y, int w, int h)
  {
    for (GameElementVec::const_iterator i = elements_.begin();
         i != elements_.end(); ++i)
      if (!(*i)->isWalkable(x, y, w, h))
        return false;
    return true;
  }

  bool
  UpDownLayer::isDestructible(int x, int y, int w, int h)
  {
    for (GameElementVec::const_iterator i = elements_.begin();
         i != elements_.end(); ++i)
      if (!(*i)->isDestructible(x, y, w, h))
        return false;
    return true;
  }

  void
  UpDownLayer::handleEvents(game::BattleScene& bs)
  {
    for (game::BattleScene::players_t::iterator it =
           bs.get_players().begin();
         it < bs.get_players().end(); ++it)
      {
        unsigned x = (*it)->getXPosition()+(*it)->getSprite().getOffsets().x;
        unsigned y = (*it)->getYPosition()+(*it)->getSprite().getOffsets().y;
        unsigned w = (*it)->getSprite().getOffsets().w;
        unsigned h = (*it)->getSprite().getOffsets().h;

        for (GameElementVec::const_iterator e = elements_.begin();
             e != elements_.end(); ++e)
          {
            if ((*e)->isTouched(x, y, w, h))
              (*e)->onTouch(bs, *(*it));

            game::Bomb* b = dynamic_cast<game::Bomb*>(*e);
            if (b)
              b->handleStates(bs);
          }
      }
    cleanup();
  }

  void UpDownLayer::removeBlocks(unsigned x, unsigned y)
  {
    for (GameElementVec::iterator e = elements_.begin();
         e != elements_.end(); ++e)
        if ((*e)->getX() == static_cast<int>(x) &&
            (*e)->getY() == static_cast<int>(y) &&
            !!dynamic_cast<Block*>(*e))
          {
            GameElement* elt = *e;
            elements_.remove(*e);
            delete elt;
            e = elements_.begin();
          }
  }

  void
  UpDownLayer::cleanup()
  {
    for (GameElementVec::const_iterator e = elements_.begin();
         e != elements_.end(); ++e)
      {
        game::Bomb* b = dynamic_cast<game::Bomb*>(*e);
        if (!!b && b->getState() == Bomb::BOMB_HAS_EXPLODED)
          {
            delete *e;
            elements_.remove(*e);
            e = elements_.begin();
          }
      }
  }
};
