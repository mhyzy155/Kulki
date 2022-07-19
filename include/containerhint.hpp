#ifndef KULKI_CONTAINERHINT_HPP
#define KULKI_CONTAINERHINT_HPP

#include "container.hpp"
#include "gamestate.hpp"
#include "resourcemanager.hpp"
#include "texturedrawable.hpp"
#include "utils_containers.hpp"

class ContainerHint : public Drawable {
  static constexpr SDL_Point HINT_TEXT_SHIFT{1, 34};
  static constexpr SDL_Point HINT_BOX_SHIFT{10, 70};
  static constexpr SDL_Point HINT_BOX_SIZE{181, 61};
  static constexpr SDL_Point HINT_SIZE{200, 150};

  const GameState& m_state;
  std::array<uint8_t, 3> m_balls_hint{0, 0, 0};

  ResourceManager<WindowName::WindowMain> m_resource_manager;
  SpritesManagerInterface* m_sprites_balls{m_resource_manager.load_sprites<9, 2>("balls.png")};
  const Texture& m_texture_hint_text{m_resource_manager.load_texture("hint_text.png")};
  TextureDrawable m_hint_text{m_texture_hint_text, HINT_TEXT_SHIFT};
  Container<0> m_hint_box;
  Container<2> m_container;

 public:
  ContainerHint(const GameState& t_state, const Uint32 windowID, const SDL_Point t_shift)
  : Drawable(t_shift),
    m_state{t_state},
    m_resource_manager{windowID},
    m_hint_box{windowID,
               HINT_BOX_SHIFT,
               Style{HINT_BOX_SIZE, {}, Color::GRAY, Style::BorderType::inwards, 1, Color::GRAY}},
    m_container{windowID,
                t_shift,
                Style{HINT_SIZE, {}, Color::GRAY, Style::BorderType::inwards, 1, Color::GRAY},
                make_array<DrawableR>(m_hint_text, m_hint_box)} {};

  virtual void draw() const noexcept override {
    m_container.draw();
    if (m_state.hint) {
      SDL_Point point = SDL_Point{25, 85} + this->m_shift;
      for (const auto& ball : m_balls_hint) {
        if (ball != 0) {
          (*m_sprites_balls)[ball - 1].draw(point);
          point = point + SDL_Point{60, 0};
        }
      }
    }
  }

  virtual bool react(const SDL_Event&) override {
    return false;
  }

  void update_hint(std::array<uint8_t, 3> t_balls_hint = filled_array<3>()) {
    m_balls_hint = t_balls_hint;
  }
};

#endif