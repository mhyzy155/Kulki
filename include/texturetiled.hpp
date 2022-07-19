#ifndef KULKI_TEXTURETILED_HPP
#define KULKI_TEXTURETILED_HPP

#include "texturebase.hpp"
#include "drawable.hpp"

class TextureTiled final : public TextureBase, public Drawable {
 public:
  TextureTiled(const std::filesystem::path& t_path, SDL_Renderer* t_renderer, SDL_Point t_size, SDL_Point spacing = {0,0}, SDL_Point t_shift = {0, 0}) noexcept;
  void draw() const noexcept;
  SDL_Rect get_rect() const noexcept;
};

#endif