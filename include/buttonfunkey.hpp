#ifndef KULKI_BUTTONFUNKEY_HPP
#define KULKI_BUTTONFUNKEY_HPP

#include "buttonfun.hpp"

class ButtonFunKey : public ButtonFun {
  Text m_text_key;

 public:
  ButtonFunKey(const std::u16string& t_text, const std::u16string& t_text_key, SDL_Renderer* t_renderer, Function&& t_fun_press, const SDL_Point t_shift = {0, 0}, Style&& t_style = Style{});
  virtual void shift(SDL_Point t_shift);
  virtual void draw() const noexcept;
  virtual void set_hover(bool t_is_hovered);
  SDL_Point get_size() const noexcept;
  virtual void set_size(SDL_Point t_size);
};

#endif