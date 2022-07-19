#include "../include/texturebase.hpp"

TextureBase::TextureBase(SDL_Texture* t_texture, SDL_Renderer* t_renderer) noexcept : m_texture{t_texture}, m_renderer{t_renderer} {};

SDL_Texture* TextureBase::get_texture() const noexcept {
  return m_texture.get();
}

/*
void TextureBase::draw(SDL_Renderer* renderer) const noexcept {
  SDL_Rect dest_rect{m_rect};
  dest_rect.x = m_shift.x;
  dest_rect.y = m_shift.y;
  SDL_RenderCopy(renderer, m_texture.get(), &m_rect, &dest_rect);
}

void TextureBase::draw(SDL_Renderer* renderer, float scale) const noexcept {
  SDL_Rect dest_rect{m_rect};
  dest_rect.x = m_shift.x;
  dest_rect.y = m_shift.y;
  dest_rect.h = int(float(dest_rect.h) * scale);
  dest_rect.w = int(float(dest_rect.w) * scale);
  SDL_RenderCopy(renderer, m_texture.get(), &m_rect, &dest_rect);
}
*/

void TextureBase::draw(SDL_Point t_pos) const noexcept {
  SDL_Rect dest_rect{m_rect};
  dest_rect.x = t_pos.x;
  dest_rect.y = t_pos.y;
  SDL_RenderCopy(m_renderer, m_texture.get(), &m_rect, &dest_rect);
}

void TextureBase::draw(SDL_Point t_pos, float scale) const noexcept {
  SDL_Rect dest_rect{m_rect};
  dest_rect.x = t_pos.x;
  dest_rect.y = t_pos.y;
  dest_rect.h = int(float(dest_rect.h) * scale);
  dest_rect.w = int(float(dest_rect.w) * scale);
  SDL_RenderCopy(m_renderer, m_texture.get(), &m_rect, &dest_rect);
}

void TextureBase::draw(const SDL_Rect& rect_src, const SDL_Rect& rect_dest) const noexcept {
  SDL_RenderCopy(m_renderer, m_texture.get(), &rect_src, &rect_dest);
}