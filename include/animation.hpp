#ifndef KULKI_ANIMATION_HPP
#define KULKI_ANIMATION_HPP

#include "sprite.hpp"

class Animation {
 protected:
  Uint32 m_tick;
  const Sprite& m_sprite;
  mutable bool m_finished{false};

 public:
  Animation(const Sprite& t_sprite, Uint32 t_tick = SDL_GetTicks());
  void schedule(Uint32 t_tick);
  bool is_finished() const;
};

namespace AnimationType {
class Jump : public Animation {
 public:
  using Animation::Animation;
  void draw(SDL_Point pos) const noexcept;
};

class JumpInplace : public Animation {
 public:
  using Animation::Animation;
  void draw(SDL_Point pos) const noexcept;
};

class Spawn : public Animation {
 public:
  using Animation::Animation;
  void draw(SDL_Point pos) const noexcept;
};

class Shrink : public Animation {
 public:
  using Animation::Animation;
  void draw(SDL_Point pos) const noexcept;
};
}  // namespace AnimationType

#endif