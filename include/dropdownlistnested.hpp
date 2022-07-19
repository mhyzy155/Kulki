#ifndef KULKI_DROPDOWNLISTNESTED_HPP
#define KULKI_DROPDOWNLISTNESTED_HPP

#include "buttonbase.hpp"
#include "dropdownlist.hpp"
#include "macros.hpp"

template <size_t N>
class DropdownListNested : public DropdownList<N> {
 protected:
  std::array<std::unique_ptr<DropdownListBase>, N> m_ddlists;
  static constexpr int ddlist_x_offset = -6;

 public:
  DropdownListNested(SDL_Renderer* t_renderer, std::array<ButtonBaseR, N>&& t_buttons, std::array<std::unique_ptr<DropdownListBase>, N>&& t_ddlists)
  : DropdownList<N>{t_renderer, std::move(t_buttons)},
    m_ddlists{std::move(t_ddlists)} {

    const auto button_size_max_y = this->m_size.y/int(N);
    auto shift = this->m_shift;
    shift.x += this->m_size.x + ddlist_x_offset;
    for (const auto& ddlist : m_ddlists) {
      CHECK_THEN(ddlist, shift(shift));
      shift.y += button_size_max_y;
    }
  }

  virtual void draw() const noexcept {
    if (this->m_expanded) {
      DropdownList<N>::draw();

      //nested lists
      for (const auto& ddlist : m_ddlists) {
        CHECK_THEN(ddlist, draw());
      }
    }
  }

  virtual void shift(SDL_Point t_shift) noexcept {
    DropdownList<N>::shift(t_shift);

    for (const auto& ddlist : m_ddlists) {
      CHECK_THEN(ddlist, shift(t_shift));
    }
  }

  void unhover() noexcept {
    DropdownList<N>::unhover();

    for (const auto& ddlist : m_ddlists) {
      CHECK_THEN(ddlist, unhover());
      CHECK_THEN(ddlist, set_expand(false));
    }
  }

  ButtonBase* is_hovered(SDL_Point point) noexcept {
    if (this->m_expanded) {
      for (const auto& ddlist : m_ddlists) {
        if (ddlist) {
          if (auto button_ptr = ddlist->is_hovered(point)) {
            return button_ptr;
          }
        }
      }
    }
    return DropdownList<N>::is_hovered(point);
  }

  bool set_if_hovered(SDL_Point point) noexcept {
    if (this->m_expanded) {
      for (const auto& ddlist : m_ddlists) {
        if (ddlist) {
          if (ddlist->set_if_hovered(point)){
            return true;
          } 
        }
      }

      for (size_t i = 0; i < N; i++) {
        if (this->m_buttons[i].get().is_hovered(point)) {
          for(size_t j = 0; j < N; j++){
            this->m_buttons[j].get().set_hover(false);
            CHECK_THEN(m_ddlists[j], set_expand(false));
          }
          this->m_buttons[i].get().set_hover(true);
          CHECK_THEN(m_ddlists[i], set_expand(true));
          CHECK_THEN(m_ddlists[i], unhover());
          return true;
        }
      }

      for(size_t i = 0; i < N; i++){
        if(m_ddlists[i]){
          m_ddlists[i]->unhover();
        } else{
          this->m_buttons[i].get().set_hover(false);
        }
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
    return this->m_size;  // or zero?
  }
};

#endif