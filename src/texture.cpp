#include "../include/texture.hpp"

#if defined(_WIN32) || defined(WIN32)
#include "SDL_image.h"
#else
#include <SDL2/SDL_image.h>
#endif

#include "../include/logger.hpp"
#include "../include/texturemapping.hpp"

Texture::Texture(const std::filesystem::path& t_path, SDL_Renderer* t_renderer, SDL_Point t_count) noexcept
: TextureBase(load_texture_from_path(t_path, t_renderer), t_renderer),
  m_count{t_count} {
  if (m_texture.get() == NULL) {
    Logger::log("Failed to load texture " + t_path.string() + "\n\terror: " + std::string{SDL_GetError()}, LoggerMode::error);
  } else {
    Logger::log("Texture " + t_path.string() + " loaded.");
    SDL_QueryTexture(m_texture.get(), NULL, NULL, &m_rect.w, &m_rect.h);
  }
}

SDL_Texture* Texture::load_texture_from_path(const std::filesystem::path& path, SDL_Renderer* renderer) const {
  if (TextureMapping::map.contains(path.string())) {
    Logger::log("Texture from bytes.");
    const RawDataInterface& raw_texture = TextureMapping::map[path.string()];
    return IMG_LoadTextureTyped_RW(renderer, SDL_RWFromConstMem(raw_texture.data(), raw_texture.size()), 1, raw_texture.type());
  } else {
    Logger::log("Texture from disk.");
    return IMG_LoadTexture(renderer, path.string().c_str());
  }
}