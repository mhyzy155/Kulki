#ifndef KULKI_BUTTONDIVIDER_HPP
#define KULKI_BUTTONDIVIDER_HPP

#include "buttonbase.hpp"

class ButtonDivider : public ButtonBase {
 public:
  ButtonDivider(SDL_Renderer* t_renderer, const SDL_Point t_shift = {0,0});
  virtual void draw() const noexcept;
  virtual void set_size(SDL_Point t_size);
};

#endif