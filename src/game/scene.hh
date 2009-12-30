#ifndef GAME_SCENE_HH_
# define GAME_SCENE_HH_

namespace game
{
  class Scene
  {
  public:
    Scene();
    Scene(const Scene&);

    virtual ~Scene();

    Scene& operator=(const Scene&);

    virtual int play() = 0;

  private:
  };
};

#endif








