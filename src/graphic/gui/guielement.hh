#ifndef GRAPHIC_GUI_GUIELEMENT_HH_
# define GRAPHIC_GUI_GUIELEMENT_HH_
# include "graphic/visualelement.hh"

namespace graphic
{
  namespace gui
  {
    class GuiElement : public VisualElement
    {
    public:
      GuiElement();
      GuiElement(const GuiElement&);

      ~GuiElement();

      GuiElement& operator=(const GuiElement&);

    private:
    };

  }; // End of namespace gui
}; // End of namespace graphic


#endif /* !GRAPHIC_GUI_GUIELEMENT_HH_ */
