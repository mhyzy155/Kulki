#ifndef KULKI_DROPDOWNLISTHEADED_HPP
#define KULKI_DROPDOWNLISTHEADED_HPP

#include "buttonbase.hpp"
#include "dropdownlist.hpp"

template <size_t N>
class DropdownListHeaded : public DropdownList<N> {
  static const int SHIFT_Y = 19;
  ButtonBase m_button_main;

 public:
  DropdownListHeaded(SDL_Renderer* t_renderer, ButtonBase&& t_button_main, std::array<ButtonBaseR, N>&& t_buttons)
  : DropdownList<N>{t_renderer, std::move(t_buttons)},
    m_button_main{std::move(t_button_main)} {
    DropdownList<N>::shift({0, SHIFT_Y});
  }

  virtual void draw() const noexcept final {
    m_button_main.draw();
    DropdownList<N>::draw();
  }

  virtual void shift(SDL_Point t_shift) noexcept final {
    m_button_main.shift(t_shift);
    DropdownList<N>::shift(t_shift);
  }

  void unhover() noexcept final {
    m_button_main.set_hover(false);
    DropdownList<N>::unhover();
  }

  ButtonBase* is_hovered(SDL_Point point) noexcept final {
    if (m_button_main.is_hovered(point)) {
      return &m_button_main;
    }

    return DropdownList<N>::is_hovered(point);
  }

  bool set_if_hovered(SDL_Point point) noexcept final {
    if (m_button_main.is_hovered(point)) {
      m_button_main.set_hover(true);
      for (ButtonBase& button : this->m_buttons) {
        button.set_hover(false);
      }
      return true;
    }

    return DropdownList<N>::set_if_hovered(point);
  }

  SDL_Point get_size() const noexcept final {
    return m_button_main.get_size();
  }
};

#endif