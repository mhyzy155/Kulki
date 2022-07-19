#ifndef KULKI_BUTTONRADIO_HPP
#define KULKI_BUTTONRADIO_HPP

#include <functional>

#include "buttonradiocontroller.hpp"
#include "buttonswitch.hpp"

class ButtonRadio : public ButtonSwitch {
  using Function = std::function<void()>;
  Function m_fun_press;
  ButtonRadioController& m_button_controller;

 public:
  ButtonRadio(const std::u16string& t_text, SDL_Renderer* t_renderer, Function&& t_fun_press, ButtonRadioController& t_button_controller, const SDL_Point t_shift = {0, 0}, Style&& t_style = Style{}, const bool t_is_checked = false);
  virtual void press() override;
};

#endif