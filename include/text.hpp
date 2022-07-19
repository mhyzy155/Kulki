#ifndef KULKI_TEXT_HPP
#define KULKI_TEXT_HPP

#if defined(_WIN32) || defined(WIN32)
#include "SDL_ttf.h"
#else
#include <SDL2/SDL_ttf.h>
#endif

#include <codecvt>
#include <iostream>
#include <locale>
#include <memory>

#include "drawablerenderer.hpp"
#include "fontfinder.hpp"
#include "fontmanager.hpp"
#include "logger.hpp"
#include "mapfixed.hpp"
#include "style.hpp"
#include "texturedeleter.hpp"

class Text : public DrawableRenderer {
  bool m_is_hovered{false};
  std::unique_ptr<SDL_Texture, TextureDeleter> m_texture;
  std::unique_ptr<SDL_Texture, TextureDeleter> m_texture_hover;
  SDL_Rect m_rect{};
  StyleText m_style;
  FontManager m_font_manager{FontFinder::find(m_style.name), m_style.size};

  std::basic_string<Uint16> to_uint16(const std::u16string& text) const;

 public:
  Text(SDL_Renderer* t_renderer, const std::u16string& t_text, const SDL_Point t_shift = {0, 0}, StyleText&& t_style = StyleText{});
  void update_string(const std::u16string& t_text);
  virtual void draw() const noexcept;
  void set_hover(bool t_is_hovered) noexcept;
  SDL_Point get_size() const noexcept;
  SDL_Point get_size(const Uint16* text) const;
  SDL_Point get_size(const std::u16string& str) const;
  SDL_Rect get_rect() const noexcept;
};

#endif