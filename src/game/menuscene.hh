#ifndef GAME_MENUSCENE_HH_
# define GAME_MENUSCENE_HH_
# include <string>
# include <vector>

# include "game/scene.hh"
# include "graphic/imageelement.hh"
# include "graphic/textelement.hh"

namespace game
{
  class MenuScene : public Scene
  {
  public:
    typedef std::vector<std::string> menuoption_t;

    MenuScene();
    MenuScene(const MenuScene&);

    ~MenuScene();

    MenuScene& operator=(const MenuScene&);

    int play();
  private:
  };
};


#endif
