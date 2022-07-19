#ifndef KULKI_BUTTONEXPANDABLE_HPP
#define KULKI_BUTTONEXPANDABLE_HPP

#include "buttonbase.hpp"

class ButtonExpandable : public ButtonBase {
  Text m_arrow;

 public:
  ButtonExpandable(const std::u16string& t_text, SDL_Renderer* t_renderer, const SDL_Point t_shift, Style&& t_style);
  virtual void shift(SDL_Point t_shift);
  virtual void draw() const noexcept override;
  virtual void set_hover(bool t_is_hovered);
  virtual void set_size(SDL_Point t_size);
};

#endif