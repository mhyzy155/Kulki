#include "../include/score.hpp"

#include "../include/math.hpp"

Score::Score(const Uint32 windowID, SDL_Point t_shift)
: Drawable(t_shift),
  m_resource_manager{windowID},
  m_texture_box{m_resource_manager.load_texture("score_box.png"), t_shift},
  m_texture_digits{m_resource_manager.load_texture("digits.png", {10, 1})} {};

void Score::update_score(size_t t_score) {
  m_score.clear();
  if (t_score == 0)
    m_score.push_back(0);
  else {
    do {
      m_score.push_back(t_score % 10);
      t_score /= 10;
    } while (t_score > 0);
  }
}

void Score::draw() const noexcept {
  m_texture_box.draw();
  SDL_Point point{103, 8};
  for (const auto& digit : m_score) {
    m_sprites_digits[digit].draw(this->m_shift + point);
    point = point - SDL_Point{19, 0};
  }
}