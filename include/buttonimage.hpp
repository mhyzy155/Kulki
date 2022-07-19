#ifndef KULKI_BUTTONIMAGE_HPP
#define KULKI_BUTTONIMAGE_HPP

#include <functional>

#include "drawablerenderer.hpp"
#include "texture.hpp"

class ButtonImage : public DrawableRenderer {
  using Function = std::function<void()>;
  bool m_is_pressed{false};
  bool m_is_focused{false};
  const Texture& m_texture;
  const Texture& m_texture_pressed;
  Function m_fun;

 public:
  ButtonImage(const Texture& t_texture, const Texture& t_texture_pressed, Function&& t_fun, const SDL_Point t_shift = {0, 0})
  : DrawableRenderer(t_texture.get_renderer(),
                     t_shift,
                     Style().set_border_type(Style::BorderType::solid).set_border_width(1).set_border_color(Color::BLACK)),
    m_texture{t_texture},
    m_texture_pressed{t_texture_pressed},
    m_fun{std::move(t_fun)} {};

  void draw() const noexcept {
    m_is_pressed ? m_texture_pressed.draw(m_shift) : m_texture.draw(m_shift);
    if (m_is_focused) {
      auto rect = m_texture.get_rect();
      rect.x += m_shift.x - 1;
      rect.y += m_shift.y - 1;
      rect.w += 2;
      rect.h += 2;
      draw_border(rect);
    }
  }

  void constexpr set_pressed(bool t_is_pressed) {
    m_is_pressed = t_is_pressed;
  }

  void constexpr set_focused(bool t_is_focused) {
    m_is_focused = t_is_focused;
  }

  void press() const {
    m_fun();
  }

  [[nodiscard]] constexpr SDL_Rect get_rect() const {
    auto rect = m_texture.get_rect();
    rect.x += m_shift.x;
    rect.y += m_shift.y;
    return rect;
  }
};

#endif