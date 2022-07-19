#ifndef KULKI_DROPDOWNLISTBASE_HPP
#define KULKI_DROPDOWNLISTBASE_HPP

#include "buttonbase.hpp"
#include "drawablerenderer.hpp"

class DropdownListBase : public DrawableRenderer {
 protected:
  bool m_expanded{false};

 public:
  DropdownListBase(SDL_Renderer* t_renderer, Style&& t_style = Style{}) : DrawableRenderer(t_renderer, {0,0}, std::move(t_style)) {};
  virtual void draw() const noexcept = 0;
  virtual void shift(SDL_Point t_shift) noexcept = 0;
  virtual void unhover() noexcept = 0;
  virtual ButtonBase* is_hovered(SDL_Point point) noexcept = 0;
  virtual bool set_if_hovered(SDL_Point point) noexcept = 0;
  virtual SDL_Point get_size() const noexcept = 0;
  void set_expand(bool t_expanded) {
    m_expanded = t_expanded;
  }

  virtual ~DropdownListBase() = default;
};

#endif