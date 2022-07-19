#ifndef KULKI_SCORE_HPP
#define KULKI_SCORE_HPP

#include <array>
#include <vector>

#include "drawable.hpp"
#include "resourcemanager.hpp"
#include "sprite.hpp"
#include "texturedrawable.hpp"

class Score : public Drawable {
  ResourceManager<WindowName::WindowMain> m_resource_manager;
  std::vector<size_t> m_score{0};
  TextureDrawable m_texture_box;
  const Texture& m_texture_digits;
  std::array<Sprite, 10> m_sprites_digits{
      Sprite{m_texture_digits, 0},
      Sprite{m_texture_digits, 1},
      Sprite{m_texture_digits, 2},
      Sprite{m_texture_digits, 3},
      Sprite{m_texture_digits, 4},
      Sprite{m_texture_digits, 5},
      Sprite{m_texture_digits, 6},
      Sprite{m_texture_digits, 7},
      Sprite{m_texture_digits, 8},
      Sprite{m_texture_digits, 9}};

 public:
  Score(const Uint32 windowID, SDL_Point t_shift = {0, 0});
  void update_score(size_t t_score);
  void draw() const noexcept;
};

#endif