#ifndef KULKI_BARMENU_HPP
#define KULKI_BARMENU_HPP

#include <array>
#include <functional>

#include "dropdownlistbase.hpp"

using DropDownListBaseR = std::reference_wrapper<DropdownListBase>;

template <size_t N>
class BarMenu : public DrawableRenderer {
  std::array<DropDownListBaseR, N> m_lists;
  DropdownListBase* m_toggled{nullptr};
  bool m_expanded{false};

 public:
  BarMenu(Uint32 windowID, std::array<DropDownListBaseR, N>&& t_lists, const SDL_Point t_shift = {0, 0}, Style&& t_style = {})
  : DrawableRenderer(windowID, t_shift, std::move(t_style)),
    m_lists{std::move(t_lists)} {
    SDL_Point size{0, 0};
    for (DropdownListBase& list : m_lists) {
      list.shift(size);
      size = size + list.get_size();
      size.y = 0;
    }
  }
  virtual void draw() const noexcept {
    SDL_Rect rect_shifted{0, 0, 638, 19};
    draw_background(rect_shifted);

    for (const DropdownListBase& list : m_lists) {
      list.draw();
    }
  }

  void collapse() noexcept {
    if (m_toggled) {
      m_expanded = false;
      m_toggled->set_expand(false);
      m_toggled->unhover();
      m_toggled = nullptr;
    }
  }

  void react_mousebutton_down(const SDL_Event& event) {
    const SDL_Point point{event.button.x, event.button.y};
    for (DropdownListBase& list : m_lists) {
      if (auto button_ptr = list.is_hovered(point)) {
        button_ptr->press();
        m_toggled = &list;
        m_expanded = true;
        m_toggled->set_expand(true);
        return;
      }
    }

    collapse();
  }

  void react_mouse_motion(const SDL_Event& event) {
    const SDL_Point point{event.button.x, event.button.y};
    for (DropdownListBase& list : m_lists) {
      if (list.set_if_hovered(point)) {
        if (m_toggled) {
          if (m_toggled != &list) {
            m_toggled->set_expand(false);
            m_toggled->unhover();
            m_toggled = &list;
          }
        } else {
          m_toggled = &list;
        }

        if (m_expanded) {
          m_toggled->set_expand(true);
        }
        return;
      }
    }
    if (!m_expanded && m_toggled) {
      m_toggled->unhover();
      m_toggled = nullptr;
    }
  }
};

#endif