/**
 * \file graphic/imageelement.hh
 * \brief Déclaration de Graphic::ImageElement.
 */
#ifndef GRAPHIC_IMAGEELEMENT_HH_
# define GRAPHIC_IMAGEELEMENT_HH_
# include <vector>
# include "graphic/graphicmanager.hh"
# include "graphic/visualelement.hh"
# include "utils/resourcemanager.hh"
# include "utils/smartpointer.hh"
# include "utils/timemanager.hh"

# define DEFAULT_FRAME_SIZE_X 32
# define DEFAULT_FRAME_SIZE_Y 32
# define DEFAULT_FRAME_LENGTH 10

namespace graphic
{
  class ImageElement : public VisualElement
  {
  public:
    typedef GraphicManager::Rect Rect;

    static const unsigned NONE_ANIMATION = 0;

    ImageElement();
    ImageElement(const char* filename, unsigned frameSizeX = NONE_ANIMATION,
		 unsigned frameSizeY = NONE_ANIMATION);
    ImageElement(const ImageElement&);

    ~ImageElement();

    ImageElement& operator=(const ImageElement&);

    virtual void draw();

    void animation_play();
    void animation_stop();
    void animation_pause();
    void animation_rewind();
    void animation_set(unsigned ca);
    unsigned animation_get() const;

    int getWidth() const
    {
      return frameSizeX_;
    }

    int getHeight() const
    {
      return frameSizeY_;
    }

    unsigned getMaxAnimation() const;
    unsigned getMaxFrame() const;
    unsigned getMaxFrame(unsigned) const;
    void setMaxFrame(unsigned, unsigned);

    void setAlpha(Uint8 alpha)
    {
      SDL_SetAlpha(&**surf_, SDL_SRCALPHA, alpha);
    }

    const Rect& getOffsets() const
    {
      return offsets_;
    }

    void setOffsets(Rect& r)
    {
      offsets_ = r;
    }

    void setFrameLength(unsigned frameLength)
    {
      frameLength_ = frameLength;
    }

    unsigned getCurrentFrame() const
    {
      return currentFrame_;
    }

  private:
    unsigned frameSizeX_;
    unsigned frameSizeY_;

    unsigned currentAnimation_;
    unsigned currentFrame_;

    unsigned frameLength_; // Combien de temps dure une frame.

    bool isPlaying_;

    std::vector<unsigned> maxAnimationFrame_;

    // Les marges utilisées lors du calcul des collisions.
    Rect offsets_;


    utils::TimeManager frameTimer_;
    utils::ResourceManager::SpSurface_t* surf_;
  };
};


#endif /* !GRAPHIC_IMAGEELEMENT_HH_ */
