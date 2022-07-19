#ifndef KULKI_TEXTURE_HPP
#define KULKI_TEXTURE_HPP

#include <cassert>

#include "math.hpp"
#include "texturebase.hpp"

class Texture : public TextureBase {
  const SDL_Point m_count;

 public:
  Texture(const std::filesystem::path& t_path, SDL_Renderer* t_renderer, SDL_Point t_count = {1, 1}) noexcept;

  SDL_Texture* load_texture_from_path(const std::filesystem::path& path, SDL_Renderer* renderer) const;

  [[nodiscard]] constexpr SDL_Rect get_rect(size_t id = 0) const noexcept {
    assert(int(id) < m_count.x * m_count.y);
    SDL_Rect out_rect{};
    out_rect.w = m_rect.w / m_count.x;
    out_rect.h = m_rect.h / m_count.y;
    auto [rem, quot] = modquot(int(id), m_count.x);
    out_rect.x = out_rect.w * rem;
    out_rect.y = out_rect.h * quot;
    return out_rect;
  }
};

#endif