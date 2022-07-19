#ifndef KULKI_DROPDOWNLISTHEADEDNESTED_HPP
#define KULKI_DROPDOWNLISTHEADEDNESTED_HPP

#include "buttonbase.hpp"
#include "dropdownlistnested.hpp"

template <size_t N>
class DropdownListHeadedNested : public DropdownListNested<N> {
  static const int SHIFT_Y = 19;
  ButtonBase m_button_main;

 public:
  DropdownListHeadedNested(SDL_Renderer* t_renderer, ButtonBase&& t_button_main, std::array<ButtonBaseR, N>&& t_buttons, std::array<std::unique_ptr<DropdownListBase>, N>&& t_ddlists = generated_array<N>([]() { return std::unique_ptr<DropdownListBase>(nullptr); }))
  : DropdownListNested<N>{t_renderer, std::move(t_buttons), std::move(t_ddlists)},
    m_button_main{std::move(t_button_main)} {
    DropdownListNested<N>::shift({0, SHIFT_Y});
  }

  virtual void draw() const noexcept final {
    m_button_main.draw();
    DropdownListNested<N>::draw();
  }

  virtual void shift(SDL_Point t_shift) noexcept final {
    m_button_main.shift(t_shift);
    DropdownListNested<N>::shift(t_shift);
  }

  void unhover() noexcept final {
    m_button_main.set_hover(false);
    DropdownListNested<N>::unhover();
  }

  ButtonBase* is_hovered(SDL_Point point) noexcept final {
    if (m_button_main.is_hovered(point)) {
      return &m_button_main;
    }

    return DropdownListNested<N>::is_hovered(point);
  }

  bool set_if_hovered(SDL_Point point) noexcept final {
    if (m_button_main.is_hovered(point)) {
      m_button_main.set_hover(true);
      for (ButtonBase& button : this->m_buttons) {
        button.set_hover(false);
      }
      for (const auto& ddlist : this->m_ddlists) {
        CHECK_THEN(ddlist, set_expand(false));
      }
      return true;
    }

    return DropdownListNested<N>::set_if_hovered(point);
  }

  SDL_Point get_size() const noexcept final {
    return m_button_main.get_size();
  }
};

#endif