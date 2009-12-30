/**
 * \file graphic/visualelement.hh
 * \brief Déclaration de Graphic::VisualElement.
 */
#ifndef GRAPHIC_VISUALELEMENT_HH_
# define GRAPHIC_VISUALELEMENT_HH_

namespace graphic
{
  class VisualElement
  {
  public:
    VisualElement();
    VisualElement(const VisualElement&);

    virtual ~VisualElement();

    VisualElement& operator=(const VisualElement&);

    virtual void draw() = 0;

    void hide()
    {
    	isVisible_ = false;
    }

    void show()
    {
    	isVisible_ = true;
    }

    bool isVisible() const
    {
    	return isVisible_;
    }

    unsigned getX() const
    {
      return x_;
    }

    unsigned getY() const
    {
      return y_;
    }

    virtual void setPosition(unsigned x, unsigned y)
    {
      x_ = x;
      y_ = y;
    }

  protected:
    unsigned x_;
    unsigned y_;

    bool isVisible_;
  };
};

#endif /* !GRAPHIC_VISUALELEMENT_HH_ */
