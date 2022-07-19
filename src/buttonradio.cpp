#include "../include/buttonradio.hpp"

ButtonRadio::ButtonRadio(const std::u16string& t_text, SDL_Renderer* t_renderer, Function&& t_fun_press, ButtonRadioController& t_button_controller, const SDL_Point t_shift, Style&& t_style, const bool t_is_checked)
: ButtonSwitch(t_text, t_renderer, t_shift, std::move(t_style), t_is_checked),
  m_fun_press{std::move(t_fun_press)},
  m_button_controller{t_button_controller} {
  if (t_is_checked) {
    m_button_controller.update(this);
  }
}

void ButtonRadio::press() {
  if (this->m_is_checked) {
    this->m_fun_press();
  } else {
    this->m_is_checked = true;
    m_button_controller.update(this);
    this->m_fun_press();
  }
}