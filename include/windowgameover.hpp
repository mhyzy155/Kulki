#ifndef KULKI_WINDOWGAMEOVER_HPP
#define KULKI_WINDOWGAMEOVER_HPP

#include "buttonimage.hpp"
#include "buttonimagecontroller.hpp"
#include "container.hpp"
#include "mouse.hpp"
#include "resourcemanager.hpp"
#include "text.hpp"
#include "texturedrawable.hpp"
#include "texturetiled.hpp"
#include "utils_containers.hpp"
#include "windowinteractive.hpp"

class WindowGameover : public WindowInteractive {
  constexpr static SDL_Point WINDOW_SIZE{287, 190};
  constexpr static SDL_Point MESSAGE_SHIFT{14, 13};
  constexpr static SDL_Point MESSAGE_SIZE{261, 94};
  constexpr static SDL_Point BUTTON_OK_SHIFT{111, 138};
  constexpr static SDL_Point MARK_SHIFT{25, 17};
  constexpr static SDL_Point TEXT_SHIFT{80, 7};

  MouseStateMachine<WindowName::WindowGameover, SDL_BUTTON_LEFT> m_mouse{};
  ResourceManager<WindowName::WindowGameover> m_resource_manager{m_window.get_windowID()};
  TextureTiled& m_texture_bg{m_resource_manager.load_texture_tiled("background2.png", WINDOW_SIZE)};

  const Texture& m_texture_button_ok{m_resource_manager.load_texture("btn_ok.png")};
  const Texture& m_texture_button_ok_pressed{m_resource_manager.load_texture("btn_ok_pressed.png")};

  const Texture& m_texture_mark_exclamation{m_resource_manager.load_texture("mark_exclamation.png")};
  TextureDrawable m_mark_exclamation{m_texture_mark_exclamation, MARK_SHIFT};

  ButtonImage m_button_ok{m_texture_button_ok, m_texture_button_ok_pressed, [this]() { m_running = false; }, BUTTON_OK_SHIFT};
  ButtonImageController<WindowName::WindowGameover, 1> m_button_controller{make_array<ButtonImageR>(m_button_ok)};

  Text m_text_gameover{m_window.get_renderer(), u"Koniec Gry.", TEXT_SHIFT, StyleText{FontFamily::MSSansSerif, 12}};

  Container<2> m_container_message{m_window.get_windowID(),
                                   MESSAGE_SHIFT,
                                   Style{MESSAGE_SIZE,
                                         {},
                                         Color::GRAY,
                                         Style::BorderType::inwards,
                                         1,
                                         Color::GRAY},
                                   make_array<DrawableR>(m_mark_exclamation, m_text_gameover)};
  const Container<3> m_container{m_window.get_windowID(),
                                 {},
                                 Style{WINDOW_SIZE, {}, {}, Style::BorderType::outwards, 1, Color::GRAY},
                                 make_array<DrawableR>(m_texture_bg, m_button_ok, m_container_message)};

 public:
  WindowGameover();
  virtual void update();
  void draw() const;
  void handle_event(const SDL_Event& event);
};

#endif
