#ifndef KULKI_TEXTUREDELETER_HPP
#define KULKI_TEXTUREDELETER_HPP

#if defined(_WIN32) || defined(WIN32)
#include "SDL.h"
#else
#include <SDL2/SDL.h>
#endif

#include "logger.hpp"

struct TextureDeleter {
  void operator()(SDL_Texture* t_texture) {
    SDL_DestroyTexture(t_texture);
    Logger::log("Texture deleted.");
  }
};

#endif