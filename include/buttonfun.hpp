#ifndef KULKI_BUTTONFUN_HPP
#define KULKI_BUTTONFUN_HPP

#include <functional>

#include "buttonbase.hpp"

class ButtonFun : public ButtonBase {
 protected:
  using Function = std::function<void()>;
  Function m_fun_press;

 public:
  ButtonFun(const std::u16string& t_text, SDL_Renderer* t_renderer, Function&& t_fun_press, const SDL_Point t_shift = {0, 0}, Style&& t_style = Style{});
  virtual void press() override;
};

#endif