/**
 * \file graphic/textelement.hh
 * \brief Déclaration de Graphic::TextElement.
 */
#ifndef GRAPHIC_TEXTELEMENT_HH_
# define GRAPHIC_TEXTELEMENT_HH_
# include <string>

# include "graphic/graphicmanager.hh"
# include "graphic/visualelement.hh"
# include "utils/resourcemanager.hh"

namespace graphic
{
  class TextElement : public VisualElement
  {
  public:
    typedef graphic::GraphicManager::Rect Rect;
    typedef graphic::GraphicManager::Color Color;

    TextElement(const char* text, Color& col);
    TextElement(const TextElement&);
    
    ~TextElement();
    
    TextElement& operator=(const TextElement&);

    virtual void draw();

    int getWidth() const
    {
      return (*surf_)->w;
    }

    int getHeight() const
    {
      return (*surf_)->h;
    }

    void setColor(Color&);

    void refreshSurface();
  private:
    std::string         text_;
    Color		color_;
    utils::ResourceManager::SpSurface_t* surf_;
  };
};


#endif /* !GRAPHIC_TEXTELEMENT_HH_ */
