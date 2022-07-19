#include "../include/windowquit.hpp"

WindowQuit::WindowQuit() : WindowInteractive(WINDOW_SIZE, "Kulki"){};

void WindowQuit::update() {
  SDL_RaiseWindow(m_window.get_window());
}

void WindowQuit::draw() const {
  m_window.clear();
  m_container.draw();
  m_window.display();
}

void WindowQuit::handle_event(const SDL_Event& event) {
  switch (event.type) {
    case SDL_WINDOWEVENT:
      switch (event.window.event) {
        case SDL_WINDOWEVENT_CLOSE:
          m_running = false;
          break;
      }
      break;
    case SDL_MOUSEMOTION:
      m_mouse.handle_mouse_motion(event);
      break;
    case SDL_MOUSEBUTTONDOWN:
      m_mouse.handle_mouse_button_down(event);
      break;
    case SDL_MOUSEBUTTONUP:
      m_mouse.handle_mouse_button_up(event);
      break;
  }
}