#include "graphic/textelement.hh"

namespace graphic
{
  TextElement::TextElement(const char* text,
			   Color& col) :
    VisualElement(),
    text_ (text),
    color_ (col),
    surf_ (0)
  {
    refreshSurface();
  }

  TextElement::TextElement(const TextElement& te) :
    VisualElement(),
    text_ (te.text_),
    color_ (te.color_),
    surf_ (0)
  {
  }

  TextElement::~TextElement()
  {
    delete surf_;
  }

  TextElement&
  TextElement::operator=(const TextElement& te)
  {
    text_ = te.text_;
    color_ = te.color_;
    delete surf_;
    surf_ = 0;
    return *this;
  }

  void
  TextElement::draw()
  {
    if (isVisible_)
      {
	GraphicManager* gm = GraphicManager::get_instance();
	if (!surf_)
          refreshSurface();
	Rect dst;
	dst.x = x_, dst.y = y_, dst.w = (*surf_)->w, dst.h = (*surf_)->h;
	gm->blitToScreen(**surf_, dst);
      }
  }

  void
  TextElement::setColor(Color& col)
  {
    color_ = col;
    refreshSurface();
  }

  void
  TextElement::refreshSurface()
  {
    delete surf_;
    surf_ = 0;
    utils::ResourceManager* rm = utils::ResourceManager::get_instance();
    surf_ = &rm->queryText(text_.c_str(), color_, utils::DP_ALWAYS);
  }
};
