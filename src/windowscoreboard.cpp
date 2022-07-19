#include "../include/windowscoreboard.hpp"

#include "../include/logger.hpp"
#include "../include/userevents.hpp"

WindowScoreboard::WindowScoreboard(const SDL_Event& event, bool new_score)
: WindowInteractive(WINDOW_SIZE, "Najlepsze Wyniki"),
  m_container_scoreboard{*static_cast<ScoreboardData*>(event.user.data1), m_window.get_windowID(), TABLE_SHIFT} {};

void WindowScoreboard::update() {
  SDL_RaiseWindow(m_window.get_window());
}

void WindowScoreboard::draw() const {
  m_window.clear();
  m_container.draw();
  m_window.display();
}

void WindowScoreboard::handle_event(const SDL_Event& event) {
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
    case SDL_TEXTINPUT:
    case SDL_KEYDOWN:
      m_container_scoreboard.react(event);
      break;
  }
}