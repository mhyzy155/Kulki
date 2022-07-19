#ifndef KULKI_BUTTONSWITCHFUN_HPP
#define KULKI_BUTTONSWITCHFUN_HPP

#include <functional>

#include "buttonswitch.hpp"

class ButtonSwitchFun : public ButtonSwitch {
  using Function = std::function<void(bool&)>;
  Function m_fun_press;

 public:
  ButtonSwitchFun(const std::u16string& t_text, SDL_Renderer* t_renderer, Function&& t_fun_press, const SDL_Point t_shift = {0, 0}, Style&& t_style = Style{}, const bool t_is_checked = false);
  virtual void press() override;
};

#endif