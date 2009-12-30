#include "graphic/gui/guielement.hh"

namespace graphic
{
  namespace gui
  {
    GuiElement::GuiElement() :
      VisualElement()
    {
    }

    GuiElement::GuiElement(const GuiElement&) :
      VisualElement()
    {
    }

    GuiElement::~GuiElement()
    {
    }

    GuiElement&
    GuiElement::operator=(const GuiElement&)
    {
      return *this;
    }

  }; // End of namespace gui
}; // End of namespace graphic
