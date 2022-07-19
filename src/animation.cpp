#include "../include/animation.hpp"
#include "../include/math.hpp"

Animation::Animation(const Sprite& t_sprite, Uint32 t_tick) : m_tick{t_tick}, m_sprite{t_sprite} {};

void Animation::schedule(Uint32 t_tick) {
  m_tick = t_tick;
}

bool Animation::is_finished() const {
  return m_finished;
}

void AnimationType::Jump::draw(SDL_Point pos) const noexcept {
  constexpr int SQUASH = 8;
  const auto curr_tick = SDL_GetTicks();
  if (curr_tick < m_tick) {
    m_sprite.draw(pos);
  } else {
    const auto step = ((curr_tick - m_tick) % 132) / 33;
    switch (step) {
      case 0:
        //upwards 1st
        m_sprite.draw({pos.x, pos.y - 4});
        break;
      case 1:
        //upwards 2nd
        m_sprite.draw({pos.x, pos.y - 4});
        break;
      case 2:
        //squashed
        m_sprite.draw({pos.x, pos.y + SQUASH}, 1.0f, float(31 - SQUASH) / 31.0f);
        break;
      case 3:
        //default
        m_sprite.draw(pos);
        break;
    }
  }
}

void AnimationType::JumpInplace::draw(SDL_Point pos) const noexcept {
  constexpr int SQUASH = 8;
  const auto curr_tick = SDL_GetTicks();
  if (curr_tick < m_tick) {
    m_sprite.draw(pos);
  } else {
    const auto step = ((curr_tick - m_tick) % 335) / 67;
    switch (step) {
      case 0:
      case 2:
        //downwards 1st / upwards 1st
        m_sprite.draw({pos.x, pos.y + SQUASH / 2}, 1.0f, float(31 - SQUASH / 2) / 31.0f);
        break;
      case 1:
        //downwards 2nd
        m_sprite.draw({pos.x, pos.y + SQUASH}, 1.0f, float(31 - SQUASH) / 31.0f);
        break;
      case 3:
        //upwards 2nd
        m_sprite.draw(pos);
        break;
      case 4:
        //in the air
        m_sprite.draw({pos.x, pos.y - 4});
        break;
    }
  }
}

void AnimationType::Spawn::draw(SDL_Point pos) const noexcept {
  constexpr int SQUASH = 8;
  const auto curr_tick = SDL_GetTicks();
  if (m_finished) {
    m_sprite.draw(pos);
  } else if (curr_tick > m_tick) {
    const auto diff = curr_tick - m_tick;
    if (diff > 250) {
      m_finished = true;
      m_sprite.draw(pos);
    } else {
      const auto frame = diff % 250;
      const auto step = frame / 63;
      switch (step) {
        case 0:
        case 1: {
          //grow
          const float ratio = float(frame) / 126.0f;
          m_sprite.draw(pos + SDL_Point{int((1 - ratio) * 31 / 2), int((1 - ratio) * 31 / 2)}, ratio);
          break;
        }

        case 2: {
          //downwards
          const float ratio = float(frame - 126) / 63.0f;
          m_sprite.draw({pos.x, pos.y + int(ratio * SQUASH)}, 1.0, float(31 - ratio * SQUASH) / 31.0f);
          break;
        }

        case 3: {
          //upwards
          const float ratio = 1.0f - float(frame - 189) / 63.0f;
          m_sprite.draw({pos.x, pos.y + int(ratio * SQUASH)}, 1.0, float(31 - ratio * SQUASH) / 31.0f);
          break;
        }
      }
    }
  }
}

void AnimationType::Shrink::draw(SDL_Point pos) const noexcept {
  const auto curr_tick = SDL_GetTicks();
  if (curr_tick < m_tick) {
    m_sprite.draw(pos);
  } else if (!m_finished) {
    const auto diff = curr_tick - m_tick;
    if (diff > 125) {
      m_finished = true;
    } else {
      const float ratio = float(diff) / 125.0f;
      m_sprite.draw(pos + SDL_Point{int(ratio * 31 / 2), int(ratio * 31 / 2)}, 1.0f - ratio);
    }
  }
}