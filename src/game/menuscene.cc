#include <math.h>
#include "game/menuscene.hh"
#include "core/inputmanager.hh"
#include "graphic/graphicmanager.hh"
#include "utils/gettext.hh"
#include "utils/pathmanager.hh"

namespace game
{
  MenuScene::MenuScene() :
    Scene()
  {
  }

  MenuScene::MenuScene(const MenuScene&) :
    Scene()
  {
  }

  MenuScene::~MenuScene()
  {
  }

  MenuScene&
  MenuScene::operator=(const MenuScene&)
  {
    return *this; //FIXME
  }

  int
  MenuScene::play()
  {
    unsigned selectedMenu = 0;

    graphic::GraphicManager* gm = graphic::GraphicManager::get_instance();
    core::InputManager* im = core::InputManager::get_instance();
    core::InputManager::Key keyDown = im->KeyboardToKey(SDLK_DOWN);
    core::InputManager::Key keyUp = im->KeyboardToKey(SDLK_UP);
    core::InputManager::Key keyReturn = im->KeyboardToKey(SDLK_RETURN);

    gm->onFps();

    graphic::GraphicManager::Color col;
    col.r = 128, col.g = 128, col.b = 128;
    graphic::TextElement text("MenuScene", col);
    text.setPosition(5, 20);

    graphic::ImageElement bm5(
       utils::PathManager::getDataFilename("/img/logo_bm5.png").c_str());
    bm5.setPosition((gm->getScreenWidth()/2) - (bm5.getWidth()/2), 10);

    graphic::ImageElement gcn(
       utils::PathManager::getDataFilename("/img/logo_gcn.png").c_str());
    gcn.setPosition(5, (gm->getScreenHeight() - gcn.getHeight() - 5));

    menuoption_t menu;
    menu.push_back(_("Normal game"));
    menu.push_back(_("Battle game"));
    menu.push_back(_("Options"));
    menu.push_back(_("Credits"));
    menu.push_back(_("Quit"));

    graphic::GraphicManager::Color colOn;
    colOn.r = 255, colOn.g = 20, colOn.b = 20;

    graphic::GraphicManager::Color colOff;
    colOff.r = 255, colOff.g = 255, colOff.b = 255;

    bool isdone = false;
    while (!isdone)
    {
      im->clearBuffer();
      im->handle();

      if (im->isKeyRelease(keyReturn))
          return selectedMenu;
      else if (im->isKeyRelease(keyDown))
      {
        ++selectedMenu;
        if (selectedMenu >= menu.size())
          selectedMenu = 0;
      }
      else if (im->isKeyRelease(keyUp))
      {
        if (selectedMenu > 0)
          --selectedMenu;
        else
          selectedMenu = menu.size()-1;
      }

      gm->fillScreen(0);
      text.draw();
      bm5.draw();
      gcn.draw();

      for (unsigned i = 0; i < menu.size(); ++i)
      {
        graphic::TextElement menuText(menu[i].c_str(),
                                      ((i == selectedMenu) ? colOn : colOff));
        menuText.setPosition((gm->getScreenWidth()/2) - (menuText.getWidth()/2),
                             (350 + 30*i));
        menuText.draw();
      }

      gm->flip();
      if (im->isExiting())
	return 0;
    }

    return 0;
  }
};
