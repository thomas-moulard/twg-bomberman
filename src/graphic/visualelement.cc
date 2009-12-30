#include "graphic/visualelement.hh"

namespace graphic
{
  VisualElement::VisualElement() :
    x_ (0),
    y_ (0),
    isVisible_ (true)
  {
  }

  VisualElement::VisualElement(const VisualElement&)
  {
  }

  VisualElement::~VisualElement()
  {
  }

  VisualElement& VisualElement::operator=(const VisualElement&)
  {
    return *this; //FIXME
  }
};
