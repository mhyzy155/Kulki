#ifndef KULKI_DRAWABLERENDERER_HPP
#define KULKI_DRAWABLERENDERER_HPP

#include "drawable.hpp"
#include "style.hpp"

class DrawableRenderer : public Drawable {
 protected:
  SDL_Renderer* const m_renderer;
  Style m_style;

  void draw_border_solid(SDL_Rect rect) const noexcept;
  void draw_border_2colors(SDL_Rect rect, const SDL_Color& color1, const SDL_Color& color2) const noexcept;

 public:
  DrawableRenderer(SDL_Renderer* t_renderer, SDL_Point t_shift = {0, 0}, Style&& t_style = {});
  DrawableRenderer(Uint32 windowID, SDL_Point t_shift = {0, 0}, Style&& t_style = {});

  void draw_border(const SDL_Rect& rect) const noexcept;
  void draw_background(const SDL_Rect& rect) const noexcept;
  void draw_shadow(SDL_Rect rect, const int offset) const noexcept;
};

#endif