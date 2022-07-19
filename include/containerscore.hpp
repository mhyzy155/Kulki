#ifndef KULKI_CONTAINERSCORE_HPP
#define KULKI_CONTAINERSCORE_HPP

#include "container.hpp"
#include "math.hpp"
#include "score.hpp"

class ContainerScore : public Drawable {
  static constexpr SDL_Point SCORE_TEXT_SHIFT{20, 36};
  static constexpr SDL_Point SCORE_SIZE{200, 190};

  Score m_score;

  ResourceManager<WindowName::WindowMain> m_resource_manager;
  const Texture& m_texture_score_text{m_resource_manager.load_texture("score_text.png")};
  TextureDrawable m_score_text{m_texture_score_text, SCORE_TEXT_SHIFT};
  Container<1> m_container;

 public:
  ContainerScore(const Uint32 windowID, const SDL_Point t_shift)
  : Drawable(t_shift),
    m_score{windowID, t_shift + SDL_Point{36, 111}},
    m_resource_manager{windowID},
    m_container{windowID,
                t_shift,
                Style{SCORE_SIZE,
                      {},
                      Color::GRAY,
                      Style::BorderType::inwards,
                      1,
                      Color::GRAY},
                make_array<DrawableR>(m_score_text)} {};

  virtual void draw() const noexcept override {
    m_container.draw();
    m_score.draw();
  }

  virtual bool react(const SDL_Event&) override {
    return false;
  }

  void update_score(size_t t_score) {
    m_score.update_score(t_score);
  }
};

#endif