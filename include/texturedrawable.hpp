#ifndef KULKI_TEXTUREDRAWABLE_HPP
#define KULKI_TEXTUREDRAWABLE_HPP

#include "drawable.hpp"
#include "texture.hpp"

class TextureDrawable final : public Drawable {
  const Texture& m_texture;
 public:
  TextureDrawable(const Texture& t_texture, SDL_Point t_shift = {0, 0});
  void draw() const noexcept;
};

#endif