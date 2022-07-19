#ifndef KULKI_STYLE_HPP
#define KULKI_STYLE_HPP

#if defined(_WIN32) || defined(WIN32)
#include "SDL.h"
#else
#include <SDL2/SDL.h>
#endif

#include "fontfamily.hpp"
#include "optional_tiny.hpp"

namespace Color {
constexpr SDL_Color BLACK{0, 0, 0, 255};
constexpr SDL_Color WHITE{255, 255, 255, 255};
constexpr SDL_Color GRAY{192, 192, 192, 255};
constexpr SDL_Color GRAY_LIGHT{236, 233, 216, 255};
constexpr SDL_Color GRAY_DARK{172, 168, 153, 255};
}  // namespace Color

struct Style {
  enum class BorderType {
    none,
    solid,
    dashed,
    dotted,
    inwards,
    outwards
  };

  SDL_Point size{0, 0};
  SDL_Rect margin{0, 0, 0, 0};
  SDL_Color background_color{255, 255, 255, 255};
  BorderType border_type{BorderType::none};
  size_t border_width{0};
  SDL_Color border_color{0, 0, 0, 0};
  SDL_Color background_color_hover{49, 106, 197, 255};

  template <class C>
  requires std::same_as<SDL_Color, std::remove_const_t<std::remove_reference_t<C>>>
  [[nodiscard]] constexpr Style&& set_background_color(C&& color) {
    background_color = std::forward<C>(color);
    return std::move(*this);
  }

  [[nodiscard]] constexpr Style&& set_border_type(BorderType type) {
    border_type = type;
    return std::move(*this);
  }

  [[nodiscard]] constexpr Style&& set_border_width(size_t width) {
    border_width = width;
    return std::move(*this);
  }

  template <class C>
  requires std::same_as<SDL_Color, std::remove_const_t<std::remove_reference_t<C>>>
  [[nodiscard]] constexpr Style&& set_border_color(C&& color) {
    border_color = std::forward<C>(color);
    return std::move(*this);
  }
};

struct StyleText {
  enum class AlignH {
    left,
    center,
    right
  };

  enum class AlignV {
    top,
    center,
    bottom
  };

  FontFamily name{FontFamily::Tahoma};
  int size{11};
  SDL_Color color{0, 0, 0, 255};
  SDL_Color color_hover{255, 255, 255, 255};
  AlignH align_h{AlignH::left};
  AlignV align_v{AlignV::top};
};

#endif