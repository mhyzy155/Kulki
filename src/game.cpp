#include "../include/game.hpp"

#include "../include/logger.hpp"
#include "../include/macros.hpp"
#include "../include/userevents.hpp"
#include "../include/windowabout.hpp"
#include "../include/windowgameover.hpp"
#include "../include/windowquit.hpp"
#include "../include/windowscoreboard.hpp"

#define TICKS_FRAME 16

bool Game::is_running() const {
  return m_running;
}

void Game::run() {
  m_windowmain.update();
  CHECK_THEN(m_windowquit, update());
  CHECK_THEN(m_windowscoreboard, update());
  CHECK_THEN(m_windowgameover, update());
  CHECK_THEN(m_windowabout, update());

  m_windowmain.draw();
  CHECK_THEN(m_windowquit, draw());
  CHECK_THEN(m_windowscoreboard, draw());
  CHECK_THEN(m_windowgameover, draw());
  CHECK_THEN(m_windowabout, draw());

  SDL_Event event{};
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        m_running = false;
        break;
      case UserEvents::USER_QUIT:
        m_running = false;
        break;
      case UserEvents::USER_FLASHOTHERWINDOW: {
        WindowInteractive* window_target = nullptr;
        if (m_windowquit) {
          window_target = m_windowquit.get();
        } else if (m_windowscoreboard) {
          window_target = m_windowscoreboard.get();
        } else if (m_windowgameover) {
          window_target = m_windowgameover.get();
        } else if (m_windowabout) {
          window_target = m_windowabout.get();
        }

        if (window_target) {
          SDL_FlashWindow(window_target->get_window(), SDL_FLASH_BRIEFLY);
        }
        break;
      }
      case UserEvents::USER_SHOWQUIT:
        m_windowquit = std::make_unique<WindowQuit>();
        m_windowmain.m_blocked = true;
        break;
      case UserEvents::USER_GAMEOVER:
        m_windowgameover = std::make_unique<WindowGameover>();
        m_windowmain.m_blocked = true;
        break;
      case UserEvents::USER_NEWSCORE:
        m_windowscoreboard = std::make_unique<WindowScoreboard>(event, true);
        m_windowmain.m_blocked = true;
        break;
      case UserEvents::USER_SHOWSCORE:
        m_windowscoreboard = std::make_unique<WindowScoreboard>(event);
        m_windowmain.m_blocked = true;
        break;
      case UserEvents::USER_SHOWABOUT:
        m_windowabout = std::make_unique<WindowAbout>();
        m_windowmain.m_blocked = true;
        break;
      default:
        if (m_windowquit && event.window.windowID == m_windowquit->get_windowID()) {
          m_windowquit->handle_event(event);
          if (!m_windowquit->is_running()) {
            m_windowquit = nullptr;
            m_windowmain.m_blocked = false;
          }
        } else if (m_windowscoreboard && event.window.windowID == m_windowscoreboard->get_windowID()) {
          m_windowscoreboard->handle_event(event);
          if (!m_windowscoreboard->is_running()) {
            m_windowscoreboard = nullptr;
            m_windowmain.m_blocked = false;
          }
        } else if (m_windowgameover && event.window.windowID == m_windowgameover->get_windowID()) {
          m_windowgameover->handle_event(event);
          if (!m_windowgameover->is_running()) {
            m_windowgameover = nullptr;
            m_windowmain.m_blocked = false;
          }
        } else if (m_windowabout && event.window.windowID == m_windowabout->get_windowID()) {
          m_windowabout->handle_event(event);
          if (!m_windowabout->is_running()) {
            m_windowabout = nullptr;
            m_windowmain.m_blocked = false;
          }
        } else if (event.window.windowID == m_windowmain.get_windowID()) {
          m_windowmain.handle_event(event);
          m_running = m_windowmain.is_running();
        } else {
          // Logger::log("Unknown windowID.");
        }

        break;
    }
  }

  const auto elapsed = SDL_GetTicks() - m_tick;
  // Logger::log("FPS: " + std::to_string(1000.0f/float(elapsed)));
  if (elapsed < TICKS_FRAME) {
    SDL_Delay(TICKS_FRAME - elapsed);
  }
  m_tick = SDL_GetTicks();
}