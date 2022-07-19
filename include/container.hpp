#ifndef KULKI_CONTAINER_HPP
#define KULKI_CONTAINER_HPP

#include <array>
#include <memory>
#include <ranges>
#include <type_traits>
#include <utility>

#include "drawablerenderer.hpp"
#include "math.hpp"
#include "ref.hpp"
#include "style.hpp"
#include "utils_containers.hpp"

using DrawableR = Ref<Drawable>;

template <size_t N>
class Container : public DrawableRenderer {
 protected:
  std::array<DrawableR, N> m_drawables;

 public:
  Container(const Uint32 windowID, const SDL_Point t_shift, Style&& t_style, std::array<DrawableR, N>&& t_drawables = make_array<DrawableR>())
  : DrawableRenderer(windowID, t_shift, std::move(t_style)),
    m_drawables{std::move(t_drawables)} {
    for (Drawable& drawable : m_drawables) {
      drawable.shift(m_shift);
    }
  };

  virtual void draw() const noexcept override {
    SDL_Rect rect_shifted{m_shift.x, m_shift.y, m_style.size.x, m_style.size.y};

    draw_background(rect_shifted);

    for (const Drawable& drawable : m_drawables) {
      drawable.draw();
    }

    draw_border(rect_shifted);
  }

  virtual bool react(const SDL_Event& event) {
    for (Drawable& drawable : m_drawables | std::views::reverse) {
      if (drawable.react(event)) return true;
    }
    return false;
  }
};

#endif