#ifndef KULKI_BUTTONBASE_HPP
#define KULKI_BUTTONBASE_HPP

#include "drawablerenderer.hpp"
#include "text.hpp"

class ButtonBase : public DrawableRenderer {
 protected:
  bool m_is_hovered{false};
  Text m_text;

 public:
  ButtonBase(const std::u16string& t_text, SDL_Renderer* t_renderer, const SDL_Point t_shift = {0, 0}, Style&& t_style = Style{});
  virtual void shift(SDL_Point t_shift);
  virtual void draw() const noexcept;
  virtual void set_hover(bool t_is_hovered);
  bool is_hovered(SDL_Point point) const noexcept;
  virtual SDL_Point get_size() const noexcept;
  virtual void set_size(SDL_Point t_size);
  virtual void press();

  template <class T>
  static SDL_Point get_size_max(const T& container);
};

template <class T>
SDL_Point ButtonBase::get_size_max(const T& container) {
  SDL_Point size_max{0, 0};
  for (const ButtonBase& button : container) {
    auto size_btn = button.get_size();
    if (size_btn.x > size_max.x) {
      size_max = size_btn;
    }
  }
  return size_max;
}

#endif