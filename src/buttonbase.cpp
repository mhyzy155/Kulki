#include "../include/buttonbase.hpp"

ButtonBase::ButtonBase(const std::u16string& t_text, SDL_Renderer* t_renderer, const SDL_Point t_shift, Style&& t_style)
: DrawableRenderer(t_renderer, t_shift, std::move(t_style)),
  m_text{t_renderer, t_text, t_shift} {
  const auto size = m_text.get_size();
  m_style.size.x = (size.x + m_style.margin.x + m_style.margin.w);
  m_style.size.y = (size.y + m_style.margin.y + m_style.margin.h);

  m_text.shift(SDL_Point{m_style.margin.x, m_style.margin.y});
}

void ButtonBase::shift(SDL_Point t_shift) {
  DrawableRenderer::shift(t_shift);
  m_text.shift(t_shift);
}

void ButtonBase::draw() const noexcept {
  SDL_Rect rect_shifted{m_shift.x, m_shift.y, m_style.size.x, m_style.size.y};
  //Draw the background
  const auto& [bg_r, bg_g, bg_b, bg_a] = (m_is_hovered) ? m_style.background_color_hover : m_style.background_color;
  SDL_SetRenderDrawColor(m_renderer, bg_r, bg_g, bg_b, bg_a);
  SDL_RenderFillRect(m_renderer, &rect_shifted);
  m_text.draw();
}

void ButtonBase::set_hover(bool t_is_hovered) {
  m_is_hovered = t_is_hovered;
  m_text.set_hover(m_is_hovered);
}

bool ButtonBase::is_hovered(SDL_Point point) const noexcept {
  return ((point.x >= m_shift.x) && (point.y >= m_shift.y) && (point.x < (m_shift.x + m_style.size.x)) && (point.y < (m_shift.y + m_style.size.y))) ? true : false;
}

SDL_Point ButtonBase::get_size() const noexcept {
  return m_style.size;
}

void ButtonBase::set_size(SDL_Point t_size) {
  m_style.size = t_size;
}

void ButtonBase::press() {}