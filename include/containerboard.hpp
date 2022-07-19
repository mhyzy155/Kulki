#ifndef KULKI_CONTAINERBOARD_HPP
#define KULKI_CONTAINERBOARD_HPP

#include <array>
#include <cassert>
#include <map>
#include <vector>

#include "animation.hpp"
#include "container.hpp"
#include "direction.hpp"
#include "gamestate.hpp"
#include "logger.hpp"
#include "math.hpp"
#include "resourcemanager.hpp"
#include "userevents.hpp"

class ContainerBoard : public Drawable {
  static constexpr SDL_Point CELLS_SIZE{413, 413};
  static constexpr SDL_Point BOARD_SIZE{415, 415};

  const GameState& m_state;
  const Uint32 m_windowID;
  bool m_blocked{false};
  std::map<Point<size_t>, uint8_t> m_balls{};
  std::map<Point<size_t>, uint8_t> m_balls_new{};
  std::map<Point<size_t>, uint8_t> m_balls_new_handle{};
  std::map<Point<size_t>, uint8_t> m_balls_old{};
  std::unique_ptr<std::pair<Point<size_t>, uint8_t>> m_ball_picked = nullptr;
  std::unique_ptr<std::pair<Point<double>, uint8_t>> m_ball_moved = nullptr;
  std::vector<std::pair<Point<size_t>, AnimationType::Spawn>> m_balls_new_animation{};
  std::map<Point<size_t>, AnimationType::Shrink> m_balls_old_animation{};
  std::unique_ptr<AnimationType::JumpInplace> m_ball_picked_animation = nullptr;
  std::unique_ptr<AnimationType::Jump> m_ball_moved_animation = nullptr;
  std::vector<Direction> m_path{};
  Direction m_direction;
  double m_ball_moved_diff{0.0};
  Uint32 m_ball_moved_tick{0};
  Point<size_t> m_from{0, 0};
  Point<size_t> m_to{0, 0};

  ResourceManager<WindowName::WindowMain> m_resource_manager{m_windowID};
  TextureTiled& m_texture_cells{m_resource_manager.load_texture_tiled("cell.png", CELLS_SIZE, {1, 1}, {1, 1})};
  SpritesManagerInterface* m_sprites_balls{m_resource_manager.load_sprites<9, 2>("balls.png")};
  Container<1> m_container;

 public:
  ContainerBoard(const GameState& t_state, const Uint32 t_windowID, const SDL_Point t_shift)
  : Drawable(t_shift),
    m_state{t_state},
    m_windowID{t_windowID},
    m_container{t_windowID, t_shift, Style{BOARD_SIZE, {}, Color::BLACK}, make_array<DrawableR>(m_texture_cells)} {};

  void reset() {
    m_balls.clear();
    m_balls_new.clear();
    m_balls_new_handle.clear();
    m_balls_old.clear();
    m_ball_picked.reset();
    m_ball_moved.reset();
    m_balls_new_animation.clear();
    m_balls_old_animation.clear();
    m_ball_picked_animation.reset();
    m_ball_moved_animation.reset();
    m_path.clear();
    m_ball_moved_diff = 0.0;
    m_ball_moved_tick = 0;
    m_from = Point<size_t>{0, 0};
    m_to = Point<size_t>{0, 0};
  }

  virtual void draw() const noexcept override {
    m_container.draw();
    for (const auto& [point, color] : m_balls) {
      SDL_Point pos{int(point.x * 46 + 8), int(point.y * 46 + 8)};
      m_sprites_balls->get(color - 1).draw(this->m_shift + pos);
    }

    for (const auto& [point, animation] : m_balls_new_animation) {
      SDL_Point pos{int(point.x * 46 + 8), int(point.y * 46 + 8)};
      animation.draw(this->m_shift + pos);
    }

    for (const auto& [point, animation] : m_balls_old_animation) {
      SDL_Point pos{int(point.x * 46 + 8), int(point.y * 46 + 8)};
      animation.draw(this->m_shift + pos);
    }

    if (m_ball_picked && m_ball_picked_animation) {
      m_ball_picked_animation->draw(this->m_shift + SDL_Point{int(m_ball_picked->first.x) * 46 + 8, int(m_ball_picked->first.y) * 46 + 8});
    } else if (m_ball_moved && m_ball_moved_animation) {
      m_ball_moved_animation->draw(this->m_shift + SDL_Point{int(m_ball_moved->first.x * 46 + 8), int(m_ball_moved->first.y * 46 + 8)});
    }
  }

  virtual bool react(const SDL_Event& event) override {
    if (!m_blocked) {
      const auto x = floor(float(event.button.x - this->m_shift.x) / 46.0f);
      const auto y = floor(float(event.button.y - this->m_shift.y) / 46.0f);
      if ((x < 0) || (y < 0) || (x >= 9) || (y >= 9)) return false;
      const Point<size_t> point{size_t(x), size_t(y)};
      const auto it = m_balls.find(point);
      const bool not_found = (it == m_balls.end());
      if (not_found && !m_ball_picked) return false;
      (not_found) ? event_move_request(point) : pick_ball(point);
      return true;
    }
    return false;
  }

  void update() {
    if (!m_balls_new.empty()) {
      auto finished = true;
      for (const auto& [point, animation] : m_balls_new_animation) {
        if (!animation.is_finished()) {
          finished = false;
          break;
        }
      }
      if (finished) {
        event_find_matches();
        m_balls.merge(m_balls_new);
        assert(m_balls_new.empty());
        m_balls_new.clear();
        m_balls_new_animation.clear();
        m_blocked = false;
        Logger::log("New animation finished.");
      }
    } else if (!m_balls_old_animation.empty()) {
      if (m_balls_old_animation.begin()->second.is_finished()) {
        m_balls_old.clear();
        m_balls_old_animation.clear();
        m_blocked = false;
        Logger::log("Old animation finished.");
      }
    } else if (m_ball_moved_animation) {
      if (m_path.empty() && (m_ball_moved_diff == 0.0)) {
        const auto ball_moved = std::make_pair<Point<size_t>, uint8_t>({size_t(round(m_ball_moved->first.x)), size_t(round(m_ball_moved->first.y))}, std::move(m_ball_moved->second));
        m_ball_moved = nullptr;
        m_ball_moved_animation = nullptr;

        const auto [it, success] = m_balls.emplace(ball_moved);
        event_move_ball(it);

        m_blocked = false;
      } else {
        if (!m_path.empty() && (m_ball_moved_diff == 0.0)) {
          m_direction = m_path.back();
          m_ball_moved_diff = 1.0;
          m_path.pop_back();
        }

        auto tick_new = SDL_GetTicks();
        const auto tick_diff = tick_new - m_ball_moved_tick;
        auto move_diff = tick_diff * 7.5 / 1000;
        if (move_diff > m_ball_moved_diff) {
          tick_new -= Uint32((move_diff - m_ball_moved_diff) * 1000 / 7.5);
          move_diff = m_ball_moved_diff;
        }

        const auto point = m_ball_moved->first;
        switch (m_direction) {
          case Direction::right:
            m_ball_moved->first = Point{point.x + move_diff, point.y};
            break;
          case Direction::down:
            m_ball_moved->first = Point{point.x, point.y + move_diff};
            break;
          case Direction::left:
            m_ball_moved->first = Point{point.x - move_diff, point.y};
            break;
          case Direction::up:
            m_ball_moved->first = Point{point.x, point.y - move_diff};
            break;
          default:
            break;
        }

        m_ball_moved_diff -= move_diff;
        m_ball_moved_tick = tick_new;
      }
    }
  }

  void pick_ball(const Point<size_t>& point) {
    auto node = m_balls.extract(point);
    if (node) {
      if (m_ball_picked) {
        m_balls.insert(*m_ball_picked);
      }

      const auto ball_picked_key = node.key();
      const auto ball_picked_value = node.mapped();
      m_ball_picked = std::make_unique<std::pair<Point<size_t>, uint8_t>>(ball_picked_key, ball_picked_value);
      m_ball_picked_animation = std::make_unique<AnimationType::JumpInplace>(m_sprites_balls->get(ball_picked_value - 1));
    }
  }

  void add_balls(const std::vector<std::pair<Point<size_t>, uint8_t>>& t_balls_new) {
    m_blocked = true;
    std::ranges::copy(t_balls_new, std::inserter(m_balls_new, m_balls_new.begin()));
    auto curr_tick = SDL_GetTicks();
    for (const auto& ball_new : t_balls_new) {
      m_balls_new_animation.emplace_back(ball_new.first, AnimationType::Spawn(m_sprites_balls->get(ball_new.second - 1), curr_tick));
      curr_tick += 250;
    }
  }

  void remove_balls(const std::vector<Point<size_t>>& t_balls_old) {
    m_blocked = true;
    for (const auto& point : t_balls_old) {
      const auto it = m_balls.find(point);
      if (it != m_balls.end()) {
        m_balls_old.insert(*it);
        m_balls.erase(it);
      }
    }

    auto curr_tick = SDL_GetTicks();
    for (const auto& ball_old : m_balls_old) {
      m_balls_old_animation.insert({ball_old.first, AnimationType::Shrink(m_sprites_balls->get(ball_old.second - 1), curr_tick)});
    }
  }

  void event_move_request(const Point<size_t>& to) {
    m_from = m_ball_picked->first;
    m_to = to;
    SDL_Event event;
    event.type = UserEvents::USER_REQUESTMOVE;
    event.window.windowID = m_windowID;
    event.user.data1 = &m_from;
    event.user.data2 = &m_to;
    SDL_PushEvent(&event);
  }

  void event_move_ball(std::map<Point<size_t>, uint8_t>::iterator ball_it) {
    SDL_Event event;
    event.type = UserEvents::USER_MOVEBALL;
    event.window.windowID = m_windowID;
    event.user.data1 = &*ball_it;
    SDL_PushEvent(&event);
  }

  void event_find_matches() {
    m_balls_new_handle = m_balls_new;
    SDL_Event event;
    event.type = UserEvents::USER_FINDMATCHES;
    event.window.windowID = m_windowID;
    event.user.data1 = &m_balls_new_handle;
    SDL_PushEvent(&event);
  }

  void move_ball(const std::vector<Direction>& t_path) {
    m_blocked = true;
    m_path = t_path;
    m_ball_moved = std::make_unique<std::pair<Point<double>, uint8_t>>(Point{double(m_ball_picked->first.x), double(m_ball_picked->first.y)}, m_ball_picked->second);
    m_ball_moved_animation = std::make_unique<AnimationType::Jump>(m_sprites_balls->get(m_ball_picked->second - 1));
    m_ball_moved_tick = SDL_GetTicks();
    m_ball_picked = nullptr;
  }

  void unblock() {
    m_blocked = false;
  }
};

#endif