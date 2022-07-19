#ifndef KULKI_DRAWABLE_HPP
#define KULKI_DRAWABLE_HPP

#include "math.hpp"

class Drawable {
 protected:
  SDL_Point m_shift;

 public:
  Drawable(SDL_Point t_shift = {0, 0});
  void shift(SDL_Point t_shift);
  virtual void draw() const noexcept;
  virtual bool react(const SDL_Event& event);
  virtual ~Drawable() = default;
};

#endif