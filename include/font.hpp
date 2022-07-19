#ifndef KULKI_FONT_HPP
#define KULKI_FONT_HPP

#if defined(_WIN32) || defined(WIN32)
#include "SDL_ttf.h"
#else
#include <SDL2/SDL_ttf.h>
#endif

#include <memory>
#include <string_view>

class Font {
  struct FontDeleter {
    void operator()(TTF_Font* ptr);
  };

  std::string_view m_path;
  int m_size;
  std::unique_ptr<TTF_Font, FontDeleter> m_font;

 public:
  Font(const std::string_view t_path, const int t_size);
  TTF_Font* get() const;
  std::string_view get_path() const;
  int get_size() const;
  bool is_same(const std::string_view path, const int size) const;
};

#endif