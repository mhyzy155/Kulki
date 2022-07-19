#include <iostream>

#include "game.hpp"
#include "logger.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
  if ((SDL_Init(SDL_INIT_EVERYTHING) == 0) && (TTF_Init() == 0)) {
    Game game;
    while (game.is_running()) {
      game.run();
    }

  } else {
    Logger::log("SDL_Init error.", LoggerMode::error);
  }

  SDL_Quit();

  return 0;
}