#include <math.h>

#include "core/inputmanager.hh"
#include "game/introscene.hh"
#include "graphic/graphicmanager.hh"
#include "utils/pathmanager.hh"

namespace game
{
  IntroScene::IntroScene() :
    Scene()
  {
  }

  IntroScene::IntroScene(const IntroScene&) :
    Scene()
  {
  }

  IntroScene::~IntroScene()
  {
  }

  IntroScene&
  IntroScene::operator=(const IntroScene&)
  {
    return *this; //FIXME
  }


  int IntroScene::play()
  {
    graphic::GraphicManager* gm = graphic::GraphicManager::get_instance();
    core::InputManager* im = core::InputManager::get_instance();
    core::InputManager::Key keyEscape = im->KeyboardToKey(SDLK_ESCAPE);

    gm->onFps();

    graphic::GraphicManager::Color col;
    col.r = 128, col.g = 128, col.b = 128;
    graphic::TextElement text("IntroScene", col);
    text.setPosition(5, 20);


    // Partie numéro 1, logo gcn
    int f = 0;
    graphic::ImageElement gcn(
       utils::PathManager::getDataFilename("/img/logo_gcn.png").c_str());
    gcn.setPosition(gm->getScreenWidth()/2 - gcn.getWidth()/2,
                    gm->getScreenHeight()/2 - gcn.getHeight()/2);

    while (++f <= 72)
    {
      im->handle();

      if (im->isKeyRelease(keyEscape))
      {
          break;
      }

      gm->fillScreen(0);
      text.draw();

      if (f <= 24)
      {
          gcn.setAlpha(f * 255 / 24);
      }
      else if (f > 48)
      {
          gcn.setAlpha((72 - f) * 255 / 24);
      }

      gcn.draw();
      gm->flip();
    }


    // Partie numéro 2, logo TWG
    f = 0;
    graphic::ImageElement twg(
       utils::PathManager::getDataFilename("/img/logo_twg.png").c_str());
    twg.setPosition(gm->getScreenWidth()/2 -
		    twg.getWidth()/2,
                    gm->getScreenHeight()/2 -
		    twg.getHeight()/2);

    while (++f <= 72)
    {
      im->handle();

      if (im->isKeyRelease(keyEscape))
      {
          break;
      }

      gm->fillScreen(0xffffff);
      text.draw();

      if (f <= 24)
      {
          twg.setAlpha(f * 255 / 24);
      }
      else if (f > 48)
      {
          twg.setAlpha((72 - f) * 255 / 24);
      }

      twg.draw();
      gm->flip();
    }

    if (im->isExiting()) return 0;
    return 0;
  }
};
