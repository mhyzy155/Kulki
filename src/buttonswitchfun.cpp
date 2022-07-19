#include "../include/buttonswitchfun.hpp"

ButtonSwitchFun::ButtonSwitchFun(const std::u16string& t_text, SDL_Renderer* t_renderer, Function&& t_fun_press, const SDL_Point t_shift, Style&& t_style, const bool t_is_checked)
: ButtonSwitch(t_text, t_renderer, t_shift, std::move(t_style), t_is_checked),
  m_fun_press{std::move(t_fun_press)} {
}

void ButtonSwitchFun::press() {
  this->m_is_checked = !this->m_is_checked;
  this->m_fun_press(this->m_is_checked);
}