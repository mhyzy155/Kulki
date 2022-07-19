#include "../include/sprite.hpp"

Sprite::Sprite(const Texture& t_texture, size_t t_id) : m_texture{t_texture}, m_rect{t_texture.get_rect(t_id)} {
}

void Sprite::update(size_t t_id) {
  m_rect = m_texture.get_rect(t_id);
}

void Sprite::draw(SDL_Point t_pos) const noexcept {
  SDL_Rect rect_dest{m_rect};
  rect_dest.x = t_pos.x;
  rect_dest.y = t_pos.y;
  m_texture.draw(m_rect, rect_dest);
}

void Sprite::draw(SDL_Point t_pos, float scale) const noexcept {
  SDL_Rect rect_dest{m_rect};
  rect_dest.x = t_pos.x;
  rect_dest.y = t_pos.y;
  rect_dest.h = int(float(rect_dest.h) * scale);
  rect_dest.w = int(float(rect_dest.w) * scale);
  m_texture.draw(m_rect, rect_dest);
}

void Sprite::draw(SDL_Point t_pos, float scaleX, float scaleY) const noexcept {
  SDL_Rect rect_dest{m_rect};
  rect_dest.x = t_pos.x;
  rect_dest.y = t_pos.y;
  rect_dest.h = int(float(rect_dest.h) * scaleY);
  rect_dest.w = int(float(rect_dest.w) * scaleX);
  m_texture.draw(m_rect, rect_dest);
}