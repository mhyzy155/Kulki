#include "../include/texturetiled.hpp"

#include "../include/texture.hpp"

TextureTiled::TextureTiled(const std::filesystem::path& t_path, SDL_Renderer* t_renderer, SDL_Point t_size, SDL_Point spacing, SDL_Point t_shift) noexcept
: TextureBase(SDL_CreateTexture(t_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, t_size.x, t_size.y), t_renderer),
  Drawable(t_shift) {
  Texture texture_temp{t_path, t_renderer};
  SDL_Texture* texture_temp_ptr = texture_temp.get_texture();

  SDL_SetRenderTarget(m_renderer, m_texture.get());
  SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
  SDL_RenderClear(m_renderer);

  const auto [_x, _y, w, h] = texture_temp.get_rect();
  const auto [sp_w, sp_h] = spacing;
  for (int y = 0; y < t_size.y; y += h + sp_h) {
    for (int x = 0; x < t_size.x; x += w + sp_w) {
      SDL_Rect rect_temp{x, y, w, h};
      SDL_RenderCopy(m_renderer, texture_temp_ptr, NULL, &rect_temp);
    }
  }
  SDL_SetRenderTarget(m_renderer, NULL);
  SDL_QueryTexture(m_texture.get(), NULL, NULL, &m_rect.w, &m_rect.h);
}

void TextureTiled::draw() const noexcept {
  TextureBase::draw(m_shift);
}

SDL_Rect TextureTiled::get_rect() const noexcept {
  return m_rect;
}