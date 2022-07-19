#ifndef KULKI_WINDOWQUIT_HPP
#define KULKI_WINDOWQUIT_HPP

#include "buttonimagecontroller.hpp"
#include "container.hpp"
#include "resourcemanager.hpp"
#include "text.hpp"
#include "texturedrawable.hpp"
#include "texturetiled.hpp"
#include "userevents.hpp"
#include "windowinteractive.hpp"

class WindowQuit : public WindowInteractive {
  constexpr static SDL_Point WINDOW_SIZE{287, 197};
  constexpr static SDL_Point BUTTON_YES_SHIFT{59, 142};
  constexpr static SDL_Point BUTTON_NO_SHIFT{164, 142};
  constexpr static SDL_Point MESSAGE_SIZE{261, 99};
  constexpr static SDL_Point MESSAGE_SHIFT{14, 13};
  constexpr static SDL_Point MARK_SHIFT{21, 18};
  constexpr static SDL_Point TEXT_SHIFT{80, 7};

  MouseStateMachine<WindowName::WindowQuit, SDL_BUTTON_LEFT> m_mouse{};
  ResourceManager<WindowName::WindowQuit> m_resource_manager{m_window.get_windowID()};
  TextureTiled& m_texture_bg{m_resource_manager.load_texture_tiled("background2.png", WINDOW_SIZE, {}, {1, 0})};

  const Texture& m_texture_button_yes{m_resource_manager.load_texture("btn_yes.png")};
  const Texture& m_texture_button_yes_pressed{m_resource_manager.load_texture("btn_yes_pressed.png")};
  const Texture& m_texture_button_no{m_resource_manager.load_texture("btn_no.png")};
  const Texture& m_texture_button_no_pressed{m_resource_manager.load_texture("btn_no_pressed.png")};

  const Texture& m_texture_mark_question{m_resource_manager.load_texture("mark_question.png")};
  TextureDrawable m_mark_question{m_texture_mark_question, MARK_SHIFT};

  ButtonImage m_button_yes{m_texture_button_yes, m_texture_button_yes_pressed, []() { push_event(UserEvents::USER_QUIT); }, BUTTON_YES_SHIFT};
  ButtonImage m_button_no{m_texture_button_no, m_texture_button_no_pressed, [this]() { m_running = false; }, BUTTON_NO_SHIFT};
  ButtonImageController<WindowName::WindowQuit, 2> m_button_controller{make_array<ButtonImageR>(m_button_yes, m_button_no)};

  Text m_text_question{m_window.get_renderer(), u"Chcesz zakończyć Kulki?", TEXT_SHIFT, StyleText{FontFamily::MSSansSerif, 12}};

  Container<2> m_container_message{m_window.get_windowID(),
                                   MESSAGE_SHIFT,
                                   Style{MESSAGE_SIZE,
                                         {},
                                         Color::GRAY,
                                         Style::BorderType::inwards,
                                         1,
                                         Color::GRAY},
                                   make_array<DrawableR>(m_mark_question, m_text_question)};
  const Container<4> m_container{m_window.get_windowID(),
                                 {},
                                 Style{WINDOW_SIZE,
                                       {},
                                       {},
                                       Style::BorderType::outwards,
                                       1,
                                       Color::GRAY},
                                 make_array<DrawableR>(m_texture_bg, m_button_yes, m_button_no, m_container_message)};

 public:
  WindowQuit();
  virtual void update();
  void draw() const;
  void handle_event(const SDL_Event& event);
};

#endif
