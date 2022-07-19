#include "../include/buttonfun.hpp"

ButtonFun::ButtonFun(const std::u16string& t_text, SDL_Renderer* t_renderer, Function&& t_fun_press, const SDL_Point t_shift, Style&& t_style)
: ButtonBase(t_text, t_renderer, t_shift, std::move(t_style)),
  m_fun_press{std::move(t_fun_press)} {};

void ButtonFun::press() {
  m_fun_press();
}