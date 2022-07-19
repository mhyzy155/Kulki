#include "../include/drawablerenderer.hpp"

DrawableRenderer::DrawableRenderer(SDL_Renderer* t_renderer, SDL_Point t_shift, Style&& t_style)
: Drawable(t_shift),
  m_renderer{t_renderer},
  m_style{std::move(t_style)} {}

DrawableRenderer::DrawableRenderer(Uint32 windowID, SDL_Point t_shift, Style&& t_style)
: Drawable(t_shift),
  m_renderer{SDL_GetRenderer(SDL_GetWindowFromID(windowID))},
  m_style{std::move(t_style)} {}

void DrawableRenderer::draw_border_solid(SDL_Rect rect) const noexcept {
  const auto& [b_r, b_g, b_b, b_a] = m_style.border_color;
  SDL_SetRenderDrawColor(m_renderer, b_r, b_g, b_b, b_a);

  rect.w -= 1;
  rect.h -= 1;
  for (size_t i = 0; (i < m_style.border_width) && (rect.w >= 0) && (rect.h >= 0); i++) {
    const auto xw = rect.x + rect.w;
    const auto yh = rect.y + rect.h;
    SDL_RenderDrawLine(m_renderer, rect.x, rect.y, xw, rect.y);
    SDL_RenderDrawLine(m_renderer, rect.x, yh, xw, yh);
    SDL_RenderDrawLine(m_renderer, xw, rect.y, xw, yh);
    SDL_RenderDrawLine(m_renderer, rect.x, rect.y, rect.x, yh);

    rect.x += 1;
    rect.y += 1;
    rect.w -= 2;
    rect.h -= 2;
  }
}

void DrawableRenderer::draw_border_2colors(SDL_Rect rect, const SDL_Color& color1, const SDL_Color& color2) const noexcept {
  const auto& [r1, g1, b1, a1] = color1;
  const auto& [r2, g2, b2, a2] = color2;

  rect.w -= 1;
  rect.h -= 1;
  for (size_t i = 0; (i < m_style.border_width) && (rect.w >= 0) && (rect.h >= 0); i++) {
    const auto xw = rect.x + rect.w;
    const auto yh = rect.y + rect.h;
    SDL_SetRenderDrawColor(m_renderer, r2, g2, b2, a2);
    SDL_RenderDrawLine(m_renderer, rect.x, rect.y, xw, rect.y);
    SDL_SetRenderDrawColor(m_renderer, r1, g1, b1, a1);
    SDL_RenderDrawLine(m_renderer, rect.x, yh, xw, yh);
    SDL_RenderDrawLine(m_renderer, xw, rect.y, xw, yh);
    SDL_SetRenderDrawColor(m_renderer, r2, g2, b2, a2);
    SDL_RenderDrawLine(m_renderer, rect.x, rect.y, rect.x, yh);

    rect.x += 1;
    rect.y += 1;
    rect.w -= 2;
    rect.h -= 2;
  }
}

void DrawableRenderer::draw_border(const SDL_Rect& rect) const noexcept {
  switch (m_style.border_type) {
    case Style::BorderType::none:
      break;
    case Style::BorderType::solid:
      draw_border_solid(rect);
      break;
    case Style::BorderType::inwards:
      draw_border_2colors(rect, m_style.border_color + SDL_Color{64, 64, 64, 0}, m_style.border_color - SDL_Color{64, 64, 64, 0});
      break;
    case Style::BorderType::outwards:
      draw_border_2colors(rect, m_style.border_color - SDL_Color{64, 64, 64, 0}, m_style.border_color + SDL_Color{64, 64, 64, 0});
      break;
    default:
      break;
  }
}

void DrawableRenderer::draw_background(const SDL_Rect& rect) const noexcept {
  const auto& [b_r, b_g, b_b, b_a] = m_style.background_color;
  SDL_SetRenderDrawColor(m_renderer, b_r, b_g, b_b, b_a);
  SDL_RenderFillRect(m_renderer, &rect);
}

void DrawableRenderer::draw_shadow(SDL_Rect rect, const int offset) const noexcept {
  rect.x += offset;
  rect.y += offset;
  SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 128);
  SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
  SDL_RenderFillRect(m_renderer, &rect);
  SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_NONE);
}