#ifndef KULKI_BUTTONSWITCH_HPP
#define KULKI_BUTTONSWITCH_HPP

#include "buttonbase.hpp"

class ButtonSwitch : public ButtonBase {
 protected:
  bool m_is_checked;
  Text m_tick;

 public:
  ButtonSwitch(const std::u16string& t_text, SDL_Renderer* t_renderer, const SDL_Point t_shift = {0, 0}, Style&& t_style = Style{}, const bool t_is_checked = false);
  void shift(SDL_Point t_shift) override;
  virtual void draw() const noexcept override;
  virtual void set_hover(bool t_is_hovered);
  virtual void press() override;
  void uncheck();
};

#endif