#include "../include/text.hpp"

#include "../include/font.hpp"

std::basic_string<Uint16> Text::to_uint16(const std::u16string& text) const {
  std::basic_string<Uint16> output{text.begin(), text.end()};
  return output;
}

Text::Text(SDL_Renderer* t_renderer, const std::u16string& t_text, const SDL_Point t_shift, StyleText&& t_style)
: DrawableRenderer(t_renderer, t_shift),
  m_style{t_style} {
  update_string(t_text);
}

void Text::update_string(const std::u16string& t_text) {
  const auto text_uint16 = to_uint16(t_text);

  m_texture = m_font_manager.create_texture(text_uint16.data(), m_style.color, m_renderer);
  m_texture_hover = m_font_manager.create_texture(text_uint16.data(), m_style.color_hover, m_renderer);

  const auto size = get_size(text_uint16.data());
  m_rect.w = size.x;
  m_rect.h = size.y;
}

void Text::draw() const noexcept {
  SDL_Rect dest_rect{m_rect};

  switch (m_style.align_h) {
    case StyleText::AlignH::left:
      dest_rect.x = this->m_shift.x;
      break;
    case StyleText::AlignH::center:
      dest_rect.x = this->m_shift.x - m_rect.w / 2;
      break;
    case StyleText::AlignH::right:
      dest_rect.x = this->m_shift.x - m_rect.w;
      break;
  }

  switch (m_style.align_v) {
    case StyleText::AlignV::top:
      dest_rect.y = this->m_shift.y;
      break;
    case StyleText::AlignV::center:
      dest_rect.y = this->m_shift.y - m_rect.h / 2;
      break;
    case StyleText::AlignV::bottom:
      dest_rect.y = this->m_shift.y - m_rect.h;
      break;
  }

  m_is_hovered ? SDL_RenderCopy(m_renderer, m_texture_hover.get(), &m_rect, &dest_rect) : SDL_RenderCopy(m_renderer, m_texture.get(), &m_rect, &dest_rect);
}

void Text::set_hover(bool t_is_hovered) noexcept {
  m_is_hovered = t_is_hovered;
}

SDL_Point Text::get_size() const noexcept {
  return SDL_Point{m_rect.w, m_rect.h};
}

SDL_Point Text::get_size(const Uint16* text) const {
  return m_font_manager.get_size(text);
}

SDL_Point Text::get_size(const std::u16string& str) const {
  return get_size(to_uint16(str).data());
}

SDL_Rect Text::get_rect() const noexcept {
  return m_rect;
}