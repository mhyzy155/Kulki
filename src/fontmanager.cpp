#include "../include/fontmanager.hpp"

// TODO: add locks

void FontManager::load_font_if_needed() const {
  if (!font.is_same(m_path, m_size)) {
    font = Font(m_path, m_size);
  }
}

FontManager::FontManager(const std::string_view t_path, const int t_size) : m_path{t_path}, m_size{t_size} {}

std::unique_ptr<SDL_Texture, TextureDeleter> FontManager::create_texture(const Uint16* text, const SDL_Color& color, SDL_Renderer* renderer) {
  load_font_if_needed();
  SDL_Surface* surface = TTF_RenderUNICODE_Blended(font.get(), text, color);

  std::unique_ptr<SDL_Texture, TextureDeleter> m_texture{SDL_CreateTextureFromSurface(renderer, surface)};
  SDL_FreeSurface(surface);
  return m_texture;
}

SDL_Point FontManager::get_size(const Uint16* text) const {
  SDL_Point size{0, 0};
  
  load_font_if_needed();
  TTF_SizeUNICODE(font.get(), text, &size.x, &size.y);

  return size;
}

Font FontManager::font{"", 0};