#include "../include/texturedrawable.hpp"

TextureDrawable::TextureDrawable(const Texture& t_texture, SDL_Point t_shift)
: Drawable(t_shift),
  m_texture{t_texture} {}

void TextureDrawable::draw() const noexcept {
  m_texture.draw(m_shift);
}