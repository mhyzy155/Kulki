#ifndef KULKI_FONTMANAGER_HPP
#define KULKI_FONTMANAGER_HPP

#include <functional>
#include "texturedeleter.hpp"

#include "font.hpp"

class FontManager {
  static Font font;
  const std::string_view m_path;
  const int m_size;

  void load_font_if_needed() const;

 public:
  FontManager(const std::string_view t_path, const int t_size);
  std::unique_ptr<SDL_Texture, TextureDeleter> create_texture(const Uint16* text, const SDL_Color& color, SDL_Renderer* renderer);
  SDL_Point get_size(const Uint16* text) const;
};

#endif