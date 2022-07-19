#ifndef KULKI_DROPDOWNLIST_HPP
#define KULKI_DROPDOWNLIST_HPP

#include <functional>

#include "buttonbase.hpp"
#include "dropdownlistbase.hpp"
#include "macros.hpp"
#include "utils_containers.hpp"

using ButtonBaseR = std::reference_wrapper<ButtonBase>;

template <size_t N>
class DropdownList : public DropdownListBase {
 protected:
  std::array<ButtonBaseR, N> m_buttons;
  SDL_Point m_size;

 public:
  DropdownList(SDL_Renderer* t_renderer, std::array<ButtonBaseR, N>&& t_buttons)
  : DropdownListBase(t_renderer, Style{{}, {3, 3, 3, 3}, Color::WHITE, Style::BorderType::solid, 1, Color::GRAY_DARK}),
    m_buttons{std::move(t_buttons)} {
    SDL_Point button_size_max{};
    // second loop because of buttons with keys
    for (size_t i = 0; i < 2; i++) {
      button_size_max = ButtonBase::get_size_max(m_buttons);
      for (ButtonBase& button : m_buttons) {
        button.set_size(button_size_max);
      }
    }

    m_size = button_size_max;
    m_size.x += m_style.margin.x + m_style.margin.w;
    m_size.y = m_style.margin.y + m_style.margin.h;

    auto shift = this->m_shift + SDL_Point{m_style.margin.x, m_style.margin.y};
    for (ButtonBase& button : m_buttons) {
      const auto size = button.get_size();
      m_size.y += size.y;
      button.shift(shift);
      shift.y += size.y;
    }
  }

  virtual void draw() const noexcept {
    if (m_expanded) {
      SDL_Rect rect_shifted{this->m_shift.x, this->m_shift.y, m_size.x, m_size.y};

      draw_shadow(rect_shifted, 5);
      draw_background(rect_shifted);

      for (const ButtonBase& button : m_buttons) {
        button.draw();
      }

      draw_border(rect_shifted);
    }
  }

  virtual void shift(SDL_Point t_shift) noexcept {
    Drawable::shift(t_shift);

    for (ButtonBase& button : m_buttons) {
      button.shift(t_shift);
    }
  }

  void unhover() noexcept {
    for (ButtonBase& button : m_buttons) {
      button.set_hover(false);
    }
  }

  ButtonBase* is_hovered(SDL_Point point) noexcept {
    if (m_expanded) {
      for (ButtonBase& button : m_buttons) {
        if (button.is_hovered(point)) {
          return &button;
        }
      }
    }
    return nullptr;
  }

  bool set_if_hovered(SDL_Point point) noexcept {
    if (m_expanded) {
      for (ButtonBase& button : m_buttons) {
        if (button.is_hovered(point)) {
          for (ButtonBase& button2 : m_buttons) {
            button2.set_hover(false);
          }
          button.set_hover(true);
          return true;
        }
      }

      for (ButtonBase& button : m_buttons) {
        button.set_hover(false);
      }
    }
    return false;
  }

  /*
  bool set_if_hovered(SDL_Point point) noexcept {
    if (m_expanded) {
      for (const auto& button : m_buttons) {
        button->set_hover(false);
      }

      for (const auto& button : m_buttons) {
        if (button->is_hovered(point)) {
          button->set_hover(true);
          return true;
        }
      }
    }
    return false;
  }
  */

  SDL_Point get_size() const noexcept {
    return m_size;  // or zero?
  }
};

#endif