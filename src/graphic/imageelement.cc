#include <math.h>

#include "graphic/imageelement.hh"
#include "utils/gettext.hh"

namespace graphic
{
  ImageElement::ImageElement() :
    VisualElement(),
    frameSizeX_(DEFAULT_FRAME_SIZE_X),
    frameSizeY_(DEFAULT_FRAME_SIZE_Y),
    currentAnimation_ (0),
    currentFrame_ (0),
    frameLength_(DEFAULT_FRAME_LENGTH),
    isPlaying_ (false),
    maxAnimationFrame_ (),
    offsets_ (),
    frameTimer_(frameLength_),
    surf_ (0)
  {
    offsets_.x = 0;
    offsets_.y = 0;
    offsets_.w = DEFAULT_FRAME_SIZE_X;
    offsets_.h = DEFAULT_FRAME_SIZE_Y;
  }

  ImageElement::ImageElement(const char* filename, unsigned frameSizeX,
			     unsigned frameSizeY) :
    VisualElement(),
    frameSizeX_ (frameSizeX),
    frameSizeY_ (frameSizeY),
    currentAnimation_ (0),
    currentFrame_ (0),
    frameLength_(DEFAULT_FRAME_LENGTH),
    isPlaying_ (false),
    maxAnimationFrame_ (),
    offsets_ (),
    frameTimer_(frameLength_),
    surf_ (0)
  {
    utils::ResourceManager* rm = utils::ResourceManager::get_instance();
    surf_ = &rm->querySurface(filename, utils::DP_ALWAYS);

    graphic::GraphicManager* gm = graphic::GraphicManager::get_instance();
    Uint32 test = gm->mapColorRGB(**surf_, 255,0,255);
    gm->setTransparentColor(**surf_, SDL_SRCCOLORKEY, test);

    if (frameSizeX == NONE_ANIMATION || frameSizeY == NONE_ANIMATION)
      frameSizeX_ = (*surf_)->w, frameSizeY_ = (*surf_)->h;

    for (unsigned i = 0; i < getMaxAnimation(); ++i)
      maxAnimationFrame_.push_back(getMaxFrame());
  }

  ImageElement::ImageElement(const ImageElement& im) :
    VisualElement(),
    frameSizeX_ (im.frameSizeX_),
    frameSizeY_ (im.frameSizeY_),
    currentAnimation_ (im.currentAnimation_),
    currentFrame_ (im.currentFrame_),
    frameLength_(im.frameLength_),
    frameTimer_(frameLength_),
    surf_ (im.surf_)
  {
  }

  ImageElement::~ImageElement()
  {
    delete surf_;
  }

  ImageElement& ImageElement::operator=(const ImageElement& im)
  {
    frameSizeX_ = im.frameSizeX_;
    frameSizeY_ = im.frameSizeY_;
    currentAnimation_ = im.currentAnimation_;
    currentFrame_ = im.currentFrame_;
    frameLength_ = im.frameLength_;
    frameTimer_ = frameLength_;
    surf_ = im.surf_;
    return *this;
  }

  void ImageElement::draw()
  {
    if (isVisible_)
      {
        GraphicManager* gm = GraphicManager::get_instance();

        Rect dst;
        Rect src;

        if(frameTimer_.is_time(true) && isPlaying_)
        {
          ++currentFrame_;
          if (currentFrame_ >= getMaxFrame(currentAnimation_))
            currentFrame_ = 0;
        }

        dst.x = x_, dst.y = y_;
        dst.w = frameSizeX_, dst.h = frameSizeY_;

        src.x = frameSizeX_ * currentFrame_;
        src.y = frameSizeY_ * currentAnimation_;
        src.w = frameSizeX_, src.h = frameSizeY_;
        gm->blitToScreen(**surf_, src, dst);
      }
  }

  void ImageElement::animation_play()
  {
    if(isPlaying_)
      return;
    isPlaying_ = true;
    frameTimer_.resume();
  }

  void ImageElement::animation_pause()
  {
    if(!isPlaying_)
      return;
    isPlaying_ = false;
    frameTimer_.pause();
  }

  void ImageElement::animation_rewind()
  {
    currentFrame_ = 0;
    frameTimer_.reset(frameLength_);
  }

  void ImageElement::animation_stop()
  {
    isPlaying_ = false;
    animation_rewind();
  }

  void ImageElement::animation_set(unsigned ca)
  {
    if (ca >= getMaxAnimation())
      {
        W() << _("Invalid animation.") << std::endl;
        return;
      }
    currentAnimation_ = ca;
    animation_rewind();
  }

  unsigned ImageElement::getMaxAnimation() const
  {
    return (*surf_)->h / frameSizeY_;
  }

  unsigned ImageElement::getMaxFrame() const
  {
    return (*surf_)->w / frameSizeX_;
  }

  unsigned ImageElement::getMaxFrame(unsigned ca) const
  {
    return (maxAnimationFrame_[ca] < getMaxFrame()) ?
      maxAnimationFrame_[ca] : getMaxFrame();
  }

  void ImageElement::setMaxFrame(unsigned ca, unsigned n)
  {
    if (ca >= getMaxAnimation())
      {
        W() << _("Invalid animation.") << std::endl;
        return;
      }
    if (ca >= maxAnimationFrame_.size())
      {
        W() << _("Unexpected error.") << std::endl;
        return;
      }
    maxAnimationFrame_[ca] = n;
  }

  unsigned ImageElement::animation_get() const
  {
    return currentAnimation_;
  }
};
