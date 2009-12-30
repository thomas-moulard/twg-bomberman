#include <cassert>

#include "core/inputmanager.hh"
#include "graphic/gui/choiceelement.hh"
#include "utils/debug.hh"
#include "utils/gettext.hh"

namespace graphic
{
  namespace gui
  {

    ChoiceElement::ChoiceElement(std::string label, Color& labelColor) :
      GuiElement(),
      label_ (label.c_str(), labelColor),
      choices_ (),
      currentChoice_ (0),
      margin_ (defaultMargin)
    {
      setPosition(0, 0);
    }

    ChoiceElement::ChoiceElement(const ChoiceElement& ce) :
      GuiElement(),
      label_ (ce.label_),
      choices_ (ce.choices_),
      currentChoice_ (ce.currentChoice_),
      margin_ (ce.margin_)
    {
    }

    ChoiceElement::~ChoiceElement()
    {
      for(choices_t::iterator i = choices_.begin(); i != choices_.end(); ++i)
        delete *i;
    }

    ChoiceElement&
    ChoiceElement::operator=(const ChoiceElement&)
    {
      assert(0);
      return *this;
    }

    ChoiceElement&
    ChoiceElement::pushChoice(std::string value, Color& valueColor)
    {
      choices_.push_back(new TextElement(value.c_str(), valueColor));
      choices_.back()->setPosition(x_ + label_.getWidth() + margin_, y_);
      return *this;
    }

    void
    ChoiceElement::handle(Key& previousKey, Key& nextKey)
    {
      core::InputManager* im = core::InputManager::get_instance();

      if (im->isKeyRelease(previousKey))
        if (currentChoice_ > 0)
          currentChoice_--;

      if (im->isKeyRelease(nextKey))
        if (currentChoice_ < choices_.size() - 1)
          currentChoice_++;
    }

    void
    ChoiceElement::draw()
    {
      label_.draw();

      if (choices_.size() != 0)
        choices_[currentChoice_]->draw();
    }

    void
    ChoiceElement::setChoice(unsigned v)
    {
      if (v >= choices_.size())
        {
          ERROR() << _("Invalid index choice.")
                  << std::endl;
          return;
        }
      currentChoice_ = v;
    }

    unsigned
    ChoiceElement::getChoice() const
    {
      return currentChoice_;
    }

    void
    ChoiceElement::setPosition(unsigned x, unsigned y)
    {
      VisualElement::setPosition(x, y);

      label_.setPosition(x, y);

      unsigned cx = x + label_.getWidth() + margin_;
      for(choices_t::iterator i = choices_.begin(); i != choices_.end(); ++i)
        (*i)->setPosition(cx, y);
    }

    void
    ChoiceElement::setColor(Color& col)
    {
      setLabelColor(col);
      for (unsigned i = 0; i < choices_.size(); ++i)
        setChoiceColor(i, col);
    }

    void
    ChoiceElement::setLabelColor(Color& col)
    {
      label_.setColor(col);
    }

    void
    ChoiceElement::setChoiceColor(unsigned c, Color& col)
    {
      if (c >= choices_.size())
        {
          ERROR() << _("Invalid index choice.")
                  << std::endl;
          return;
        }
      choices_[c]->setColor(col);
    }

  }; // End of namespace gui
}; // End of namespace graphic
