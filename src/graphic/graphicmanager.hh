/**
 * \file graphic/graphicmanager.hh
 * \brief Déclaration de Graphic::GraphicManager.
 */
#ifndef GRAPHIC_GRAPHICMANAGER_HH_
# define GRAPHIC_GRAPHICMANAGER_HH_
# include <SDL/SDL.h>
# include <SDL/SDL_ttf.h>

# include "utils/gettext.hh"
# include "utils/timemanager.hh"

# define WM_TITLE \
   "TWG : Bomberman Classic - Games Creators Network"
# define WM_ICON \
   "bomberman"

# define SDL_SURFACE_DEFAULT_FLAGS \
   SDL_HWSURFACE | SDL_SRCALPHA


namespace graphic
{
  class GraphicManager
  {
  public:
    typedef SDL_Surface Surface;
    typedef SDL_Rect Rect;
    typedef SDL_Color Color;

    static GraphicManager* get_instance()
    {
      if (!instance_)
        instance_ = new GraphicManager();
      return instance_;
    }

    static void kill()
    {
      if (instance_)
      delete instance_;
    }


    void flip();

    void blit(Surface& src, Rect& srcrect,
	      Surface& dst, Rect& dstrect)
    {
      if (SDL_BlitSurface(&src, &srcrect, &dst, &dstrect) < 0)
        ERROR() << _("Blit failed.") << std::endl;
    }

    void blit(Surface& src, Rect& srcrect, Surface& dst)
    {
      if (SDL_BlitSurface(&src, &srcrect, &dst, NULL) < 0)
        ERROR() << _("Blit failed.") << std::endl;
    }

    void blitToScreen(Surface& src, Rect& dstrect)
    {
      if (SDL_BlitSurface(&src, NULL, screen_, &dstrect) < 0)
        ERROR() << _("Blit failed.") << std::endl;
    }

    void blitToScreen(Surface& src, Rect& srcrect, Rect& dstrect)
    {
      if (SDL_BlitSurface(&src, &srcrect, screen_, &dstrect) < 0)
        ERROR() << _("Blit failed.") << std::endl;
    }

    void fill(Surface& dst, Uint32 color)
    {
      SDL_FillRect(&dst, NULL, color);
    }

    void fill(Surface& dst, Rect& dstrect, Uint32 color)
    {
      SDL_FillRect(&dst, &dstrect, color);
    }

    void fillScreen(Uint32 color)
    {
      SDL_FillRect(screen_, NULL, color);
    }

    void fillScreen(Rect& dstrect, Uint32 color)
    {
      SDL_FillRect(screen_, &dstrect, color);
    }

    void setTransparentColor(Surface& src, Uint32 flag, Uint32 key)
    {
      SDL_SetColorKey(&src, flag, key);
    }

    Uint32 mapColorRGB(Surface& src, Uint32 r, Uint32 g, Uint32 b)
    {
      return SDL_MapRGB(src.format,r,g,b);
    }

    void mapColorRGBA(Surface& src, Uint32 r, Uint32 g, Uint32 b, Uint32 a)
    {
      SDL_MapRGBA(src.format,r,g,b,a);
    }

    int getScreenWidth()
    {
      return screen_->w;
    }

    int getScreenHeight()
    {
      return screen_->h;
    }

    void onFps()
    {
      isFps_ = true;
    }

    void offFps()
    {
      isFps_ = false;
    }

    Surface* load(const char *filename);

    Surface* print(const char* text, Color& col);

  private:
    GraphicManager();
    GraphicManager(const GraphicManager&);
    ~GraphicManager();
    GraphicManager& operator=(const GraphicManager&);
    void drawFps();
    static GraphicManager* instance_;
    utils::TimeManager* timemanager_;

    Surface* screen_;
    TTF_Font* font_;
    bool isFps_;
  };
};


#endif /* !GRAPHIC_GRAPHICMANAGER_HH_ */
