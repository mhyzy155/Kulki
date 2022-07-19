#ifndef KULKI_MOUSE_HPP
#define KULKI_MOUSE_HPP

#include <algorithm>
#include <functional>
#include <utility>
#include <vector>

#if defined(_WIN32) || defined(WIN32)
#include "SDL.h"
#else
#include <SDL2/SDL.h>
#endif

#include "logger.hpp"
#include "ref.hpp"
#include "windowname.hpp"

enum class MouseState {
  button_down,
  motion_pressed,
  button_up,
  motion_released
};

template <WindowName name, Uint32 mouse_button>
class MouseListener;

template <WindowName name, Uint32 mouse_button>
class MouseStateMachine {
  using Type = MouseListener<name, mouse_button>;
  using TypeR = Ref<const Type>;
  Sint32 m_x{0};
  Sint32 m_y{0};
  MouseState m_state{MouseState::motion_released};
  static std::vector<TypeR> m_listeners;

  void notify() const {
    for (const Type& listener : m_listeners) {
      listener.notify(m_state, m_x, m_y);
    }
  }

 public:
  void handle_mouse_motion(const SDL_Event& event) {
    m_x = event.button.x;
    m_y = event.button.y;
    switch (m_state) {
      case MouseState::button_down:
        m_state = MouseState::motion_pressed;
        break;
      case MouseState::motion_pressed:
        break;
      case MouseState::button_up:
        m_state = MouseState::motion_released;
        break;
      case MouseState::motion_released:
        break;
    }
    notify();
  }

  void handle_mouse_button_down(const SDL_Event& event) {
    m_x = event.button.x;
    m_y = event.button.y;
    switch (m_state) {
      case MouseState::button_down:
        break;
      case MouseState::motion_pressed:
        Logger::log("Wrong sequence(motion_pressed->button_down)", LoggerMode::warning);
        break;
      case MouseState::button_up:
        m_state = MouseState::button_down;
        break;
      case MouseState::motion_released:
        m_state = MouseState::button_down;
        break;
    }
    notify();
  }

  void handle_mouse_button_up(const SDL_Event& event) {
    m_x = event.button.x;
    m_y = event.button.y;
    switch (m_state) {
      case MouseState::button_down:
        m_state = MouseState::button_up;
        break;
      case MouseState::motion_pressed:
        m_state = MouseState::button_up;
        break;
      case MouseState::button_up:
        break;
      case MouseState::motion_released:
        Logger::log("Wrong sequence(motion_released->button_up)", LoggerMode::warning);
        break;
    }
    notify();
  }

  void handle_event(const SDL_Event& event) {
    switch (event.type) {
      case SDL_MOUSEMOTION:
        handle_mouse_motion(event);
        break;
      case SDL_MOUSEBUTTONDOWN:
        handle_mouse_button_down(event);
        break;
      case SDL_MOUSEBUTTONUP:
        handle_mouse_button_up(event);
        break;
    }
  }

  static void register_listener(const Type& t_listener) {
    m_listeners.emplace_back(t_listener);
  }

  static void deregister_listener(const Type& t_listener) {
    const auto ret = std::erase_if(m_listeners, [&t_listener](const Type& other) { return &t_listener == &other; });
  }
};

template <WindowName name, Uint32 mouse_button>
std::vector<Ref<const MouseListener<name, mouse_button>>> MouseStateMachine<name, mouse_button>::m_listeners{};

template <WindowName name, Uint32 mouse_button>
class MouseListener {
  using Function = std::function<void(Sint32, Sint32)>;
  Function m_fun_button_down;
  Function m_fun_motion_pressed;
  Function m_fun_button_up;
  Function m_fun_motion_released;

 public:
  MouseListener(
      Function&& t_fun_button_down = [](Sint32, Sint32) {}, Function&& t_fun_motion_pressed = [](Sint32, Sint32) {}, Function&& t_fun_button_up = [](Sint32, Sint32) {}, Function&& t_fun_motion_released = [](Sint32, Sint32) {})
  : m_fun_button_down{std::move(t_fun_button_down)},
    m_fun_motion_pressed{std::move(t_fun_motion_pressed)},
    m_fun_button_up{std::move(t_fun_button_up)},
    m_fun_motion_released{std::move(t_fun_motion_released)} {
    MouseStateMachine<name, mouse_button>::register_listener(*this);
  }

  ~MouseListener() {
    MouseStateMachine<name, mouse_button>::deregister_listener(*this);
  }

  void set_callback(MouseState state, Function&& t_fun) {
    switch (state) {
      case MouseState::button_down:
        m_fun_button_down = std::move(t_fun);
        break;
      case MouseState::motion_pressed:
        m_fun_motion_pressed = std::move(t_fun);
        break;
      case MouseState::button_up:
        m_fun_button_up = std::move(t_fun);
        break;
      case MouseState::motion_released:
        m_fun_motion_released = std::move(t_fun);
        break;
    }
  }

  bool is_hovered(Sint32 x, Sint32 y, const SDL_Rect& rect) const {
    return (x >= rect.x) && (x <= rect.x + rect.w) && (y >= rect.y) && (y <= rect.y + rect.h);
  }

  void notify(const MouseState state, const Sint32 x, const Sint32 y) const {
    switch (state) {
      case MouseState::button_down:
        m_fun_button_down(x, y);
        break;
      case MouseState::motion_pressed:
        m_fun_motion_pressed(x, y);
        break;
      case MouseState::button_up:
        m_fun_button_up(x, y);
        break;
      case MouseState::motion_released:
        m_fun_motion_released(x, y);

        break;
    }
  }
};

#endif