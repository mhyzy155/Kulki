#ifndef KULKI_WINDOWINTERACTIVE_HPP
#define KULKI_WINDOWINTERACTIVE_HPP

#include "window.hpp"

class WindowInteractive {
 protected:
  bool m_running{true};
  const Window m_window;

 public:
  bool m_blocked{false};

  WindowInteractive(SDL_Point t_size, const char* t_title = nullptr, Uint32 flags = 0);
  virtual ~WindowInteractive() = default;
  bool is_running() const;
  SDL_Window* get_window() const;
  Uint32 get_windowID() const;
  virtual void update();
  virtual void draw() const = 0;
  virtual void handle_event(const SDL_Event& event);
  virtual void react_mousebutton_down(const SDL_Event& event);
  virtual void react_mouse_motion(const SDL_Event& event);
};

#endif