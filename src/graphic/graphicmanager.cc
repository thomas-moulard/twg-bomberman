#include <cassert>
#include <sstream>
#include <SDL/SDL_image.h>
#include "core/configmanager.hh"
#include "graphic/graphicmanager.hh"
#include "graphic/textelement.hh"
#include "utils/debug.hh"
#include "utils/pathmanager.hh"

namespace graphic
{
  GraphicManager* GraphicManager::instance_ = 0;

  GraphicManager::GraphicManager() :
    screen_ (0),
    font_ (0)
  {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0)
      {
	ERROR() << _("Failed to initialize SDL.") << std::endl;
	exit(1);
      }

    if (TTF_Init() < 0)
      {
	ERROR() << _("Failed to initialize SDL_ttf.") << std::endl;
	exit(1);
      }

    core::ConfigManager* cm = core::ConfigManager::get_instance();
    unsigned width = cm->getIntFromConfigurationFile(
                     "graphic", "GraphicManager", "screenWidth");
    unsigned height = cm->getIntFromConfigurationFile(
                     "graphic", "GraphicManager", "screenHeight");

    if (!width || !height)
      {
        ERROR() << _("Invalid resolution.") << std::endl;
        exit(1);
      }

    screen_ = SDL_SetVideoMode(width, height, 32,
			       SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_SRCALPHA);
    assert(!!screen_);

    SDL_WM_SetCaption(WM_TITLE, WM_ICON);

    font_ = TTF_OpenFont(
                     utils::PathManager::getDataFilename("/fixme.ttf").c_str(),
                     14);

    if (!font_)
      {
	ERROR() << _("Failed to load the font.") << std::endl;
	exit(42);
      }

    timemanager_ = new utils::TimeManager(41);
  }

  GraphicManager::GraphicManager(const GraphicManager&)
  {
    assert(0);
  }

  GraphicManager::~GraphicManager()
  {
    TTF_CloseFont(font_);
    TTF_Quit();
    SDL_Quit();
  }

  GraphicManager&
  GraphicManager::operator=(const GraphicManager&)
  {
    assert(0);
    return *this;
  }

  GraphicManager::Surface*
  GraphicManager::load(const char *filename)
  {
    return IMG_Load(filename);
  }

  GraphicManager::Surface*
  GraphicManager::print(const char* text, Color& col)
  {
    return TTF_RenderUTF8_Blended(font_, text, col);
  }

  void
  GraphicManager::flip()
  {
    if (isFps_)
    {
      std::ostringstream oss;

      int fps = 0;
      int timeElapsed = timemanager_->TimeElapsed();
      if (timeElapsed != 0)
        fps = 1000 / timeElapsed;
      oss << "FPS: " << fps;

      Color col;
      col.r = 128, col.g = 128, col.b = 128;
      TextElement text(oss.str().c_str(), col);
      text.setPosition(5, 5);
      text.draw();
    }

    timemanager_->DelayUtilEnd(true);
    SDL_Flip(screen_);
    fillScreen(0);
  }
};
