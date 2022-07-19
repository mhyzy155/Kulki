#ifndef KULKI_WINDOWSCOREBOARD_HPP
#define KULKI_WINDOWSCOREBOARD_HPP

#include "buttonimagecontroller.hpp"
#include "container.hpp"
#include "containerscoreboard.hpp"
#include "resourcemanager.hpp"
#include "texturetiled.hpp"
#include "utils_containers.hpp"
#include "windowinteractive.hpp"

class WindowScoreboard : public WindowInteractive {
  constexpr static SDL_Point WINDOW_SIZE{338, 332};
  constexpr static SDL_Point BUTTON_SHIFT{263, 279};
  constexpr static SDL_Point TABLE_SHIFT{12, 18};
  constexpr static SDL_Point TABLE_SIZE{214, 300};

  MouseStateMachine<WindowName::WindowScoreboard, SDL_BUTTON_LEFT> m_mouse{};
  ResourceManager<WindowName::WindowScoreboard> m_resource_manager{m_window.get_windowID()};
  TextureTiled& m_texture_bg{m_resource_manager.load_texture_tiled("background2.png", WINDOW_SIZE, {}, {1, 0})};

  const Texture& m_texture_button_ok{m_resource_manager.load_texture("btn_ok.png")};
  const Texture& m_texture_button_ok_pressed{m_resource_manager.load_texture("btn_ok_pressed.png")};

  ButtonImage m_button_ok{m_texture_button_ok, m_texture_button_ok_pressed, [this]() { m_running = false; }, BUTTON_SHIFT};
  ButtonImageController<WindowName::WindowScoreboard, 1> m_button_controller{make_array<ButtonImageR>(m_button_ok)};

  ContainerScoreboard<10> m_container_scoreboard;
  const Container<3> m_container{m_window.get_windowID(),
                                 SDL_Point{},
                                 Style{WINDOW_SIZE, {}, {}, Style::BorderType::outwards, 1, Color::GRAY},
                                 make_array<DrawableR>(m_texture_bg, m_button_ok, m_container_scoreboard)};

 public:
  WindowScoreboard(const SDL_Event& event, bool new_score = false);
  virtual void update();
  void draw() const;
  void handle_event(const SDL_Event& event);
  void handle_newscore();
};

#endif
