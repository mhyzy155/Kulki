#ifndef KULKI_SPRITE_HPP
#define KULKI_SPRITE_HPP

#include "texture.hpp"

class Sprite {
  const Texture& m_texture;
  SDL_Rect m_rect;
  
 public:
  Sprite(const Texture& t_texture, size_t t_id = 0);

  void update(size_t t_id);
  void draw(SDL_Point t_pos) const noexcept;
  void draw(SDL_Point t_pos, float scale) const noexcept;
  void draw(SDL_Point t_pos, float scaleX, float scaleY) const noexcept;
};

#endif