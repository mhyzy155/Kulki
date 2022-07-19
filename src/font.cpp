#include "../include/font.hpp"

#include "../include/logger.hpp"

void Font::FontDeleter::operator()(TTF_Font* ptr) {
  TTF_CloseFont(ptr);
  Logger::log("Font closed.");
}

Font::Font(std::string_view t_path, int t_size) : m_path{t_path}, m_size{t_size}, m_font{TTF_OpenFont(m_path.data(), m_size)} {};

TTF_Font* Font::get() const {
  return m_font.get();
}

std::string_view Font::get_path() const {
  return m_path;
}

int Font::get_size() const {
  return m_size;
}

bool Font::is_same(const std::string_view path, const int size) const{
  return (m_path == path) && (m_size == size);
}