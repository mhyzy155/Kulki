#ifndef KULKI_TEXTUREBASE_HPP
#define KULKI_TEXTUREBASE_HPP

#include <filesystem>
#include <iostream>
#include <memory>

#if defined(_WIN32) || defined(WIN32)
#include "SDL.h"
#else
#include <SDL2/SDL.h>
#endif

#include "logger.hpp"
#include "texturedeleter.hpp"

class TextureBase {

 protected:
  const std::unique_ptr<SDL_Texture, TextureDeleter> m_texture;
  SDL_Renderer* const m_renderer;
  SDL_Rect m_rect{};

 public:
  TextureBase(SDL_Texture* t_texture, SDL_Renderer* t_renderer) noexcept;

  [[nodiscard]] SDL_Texture* get_texture() const noexcept;
  [[nodiscard]] constexpr SDL_Renderer* get_renderer() const noexcept {
    return m_renderer;
  }

  //void draw() const noexcept override;
  //void draw(float scale) const noexcept;
  void draw(SDL_Point t_pos) const noexcept;
  void draw(SDL_Point t_pos, float scale) const noexcept;
  void draw(const SDL_Rect& rect_src, const SDL_Rect& rect_dest) const noexcept;
};

#endif