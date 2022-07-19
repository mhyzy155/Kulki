#include "../include/buttondivider.hpp"

ButtonDivider::ButtonDivider(SDL_Renderer* t_renderer, const SDL_Point t_shift)
: ButtonBase(u"", t_renderer, t_shift, Style{{}, {1, 3, 1, 5}, {255, 255, 255, 255}}) {
  m_style.size = {0, m_style.margin.y + m_style.margin.h + 1};
}

void ButtonDivider::draw() const noexcept {
  const auto& [r, g, b, a] = Color::GRAY_DARK;
  SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
  const auto y = m_shift.y + m_style.margin.y;
  SDL_RenderDrawLine(m_renderer, m_shift.x + m_style.margin.x, y, m_shift.x + m_style.size.x - m_style.margin.x - 1, y);
}

void ButtonDivider::set_size(SDL_Point t_size) {
  m_style.size.x = t_size.x;
}