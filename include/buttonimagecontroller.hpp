#ifndef KULKI_BUTTONIMAGECONTROLLER_HPP
#define KULKI_BUTTONIMAGECONTROLLER_HPP

#include <array>

#include "buttonimage.hpp"
#include "mouse.hpp"
#include "ref.hpp"

using ButtonImageR = Ref<ButtonImage>;

template <WindowName name, size_t N>
class ButtonImageController {
  const std::array<ButtonImageR, N> m_buttons;
  MouseListener<name, SDL_BUTTON_LEFT> m_listener;

  void react_motion_pressed(Sint32 x, Sint32 y) {
    for (ButtonImage& button : m_buttons) {
      if (m_listener.is_hovered(x, y, button.get_rect())) {
        for (ButtonImage& button2 : m_buttons) {
          button2.set_pressed(false);
          button2.set_focused(false);
        }
        button.set_pressed(true);
        button.set_focused(true);
        return;
      } else {
        button.set_pressed(false);
      }
    }
  }

  void react_button_down(Sint32 x, Sint32 y) {
    for (ButtonImage& button : m_buttons) {
      if (m_listener.is_hovered(x, y, button.get_rect())) {
        button.set_pressed(true);
        button.set_focused(true);
        return;
      }
    }
  }

  void react_button_up(Sint32 x, Sint32 y) {
    for (ButtonImage& button : m_buttons) {
      if (m_listener.is_hovered(x, y, button.get_rect())) {
        button.set_pressed(false);
        button.press();
        return;
      }
    }
  }

 public:
  ButtonImageController(std::array<ButtonImageR, N>&& t_buttons)
  : m_buttons{std::move(t_buttons)},
    m_listener{[this](Sint32 x, Sint32 y) { react_button_down(x, y); },
               [this](Sint32 x, Sint32 y) { react_motion_pressed(x, y); },
               [this](Sint32 x, Sint32 y) { react_button_up(x, y); },
               [](Sint32, Sint32) {}} {
    m_buttons[0].get().set_focused(true);
  }
};

#endif