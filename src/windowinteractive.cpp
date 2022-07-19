#include "../include/windowinteractive.hpp"

WindowInteractive::WindowInteractive(SDL_Point t_size, const char* t_title, Uint32 flags) : m_window{t_size, flags} {
  if(t_title){
    SDL_SetWindowTitle(m_window.get_window(), t_title);
  }
}

bool WindowInteractive::is_running() const {
  return m_running;
}

SDL_Window* WindowInteractive::get_window() const {
  return m_window.get_window();
}

Uint32 WindowInteractive::get_windowID() const {
  return m_window.get_windowID();
}

void WindowInteractive::update() {}

void WindowInteractive::handle_event(const SDL_Event&) {}

void WindowInteractive::react_mousebutton_down(const SDL_Event&) {}

void WindowInteractive::react_mouse_motion(const SDL_Event&) {}