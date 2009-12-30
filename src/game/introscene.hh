#ifndef GAME_INTROSCENE_HH_
# define GAME_INTROSCENE_HH_
# include "game/scene.hh"
# include "graphic/imageelement.hh"
# include "graphic/textelement.hh"

namespace game
{
  class IntroScene : public Scene
  {
   public:
     IntroScene();
     IntroScene(const IntroScene&);

     ~IntroScene();

     IntroScene& operator=(const IntroScene&);

     virtual int play();
   private:
  };
};

#endif
