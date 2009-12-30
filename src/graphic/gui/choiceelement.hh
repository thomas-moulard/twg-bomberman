#ifndef GRAPHIC_GUI_CHOICEELEMENT_HH_
# define GRAPHIC_GUI_CHOICEELEMENT_HH_
# include <vector>
# include "core/inputmanager.hh"
# include "graphic/graphicmanager.hh"
# include "graphic/textelement.hh"
# include "graphic/gui/guielement.hh"

# define max(a, b) ((a) > (b) ? (a) : (b))

namespace graphic
{
  namespace gui
  {
    class ChoiceElement : public GuiElement
    {
    public:
      typedef graphic::GraphicManager::Color Color;
      typedef std::vector<graphic::TextElement*> choices_t;
      typedef core::InputManager::Key Key;

      ChoiceElement(std::string, Color&);
      ChoiceElement(const ChoiceElement&);

      virtual ~ChoiceElement();

      ChoiceElement& operator=(const ChoiceElement&);

      ChoiceElement& pushChoice(std::string, Color&);

      void handle(Key& previousKey, Key& nextKey);
      virtual void draw();

      void setChoice(unsigned);
      unsigned getChoice() const;

      static const unsigned defaultMargin = 20;

      virtual void setPosition(unsigned x, unsigned y);

      void setColor(Color&);
      void setLabelColor(Color&);
      void setChoiceColor(unsigned, Color&);

      unsigned getWidth() const
      {
        int m = 0;
        for (choices_t::const_iterator i = choices_.begin();
             i != choices_.end(); ++i)
          m = max(m, (*i)->getWidth());
        return label_.getWidth() + margin_ + m;
      }

      unsigned getHeight() const
      {
        return label_.getHeight();
      }
    private:
      graphic::TextElement label_;
      choices_t choices_;
      unsigned currentChoice_;
      unsigned margin_;
    };

  }; // End of namespace gui
}; // End of namespace graphic


#endif /* !GRAPHIC_GUI_CHOICEELEMENT_HH_ */
