#ifndef KULKI_GAME_HPP
#define KULKI_GAME_HPP

#if defined(_WIN32) || defined(WIN32)
#include "SDL.h"
#else
#include <SDL2/SDL.h>
#endif

#include "gamestate.hpp"
#include "windowmain.hpp"

class Game {
  bool m_running{true};
  Uint32 m_tick = SDL_GetTicks();
  GameState m_gamestate{9};
  WindowMain m_windowmain{m_gamestate};
  std::unique_ptr<WindowInteractive> m_windowquit{nullptr};
  std::unique_ptr<WindowInteractive> m_windowscoreboard{nullptr};
  std::unique_ptr<WindowInteractive> m_windowgameover{nullptr};
  std::unique_ptr<WindowInteractive> m_windowabout{nullptr};

 public:
  bool is_running() const;
  void run();
};

#endif