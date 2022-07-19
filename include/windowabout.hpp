#ifndef KULKI_WINDOWABOUT_HPP
#define KULKI_WINDOWABOUT_HPP

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

class WindowAbout : public WindowInteractive {
  static constexpr SDL_Point WINDOW_SIZE{354, 360};
  static constexpr SDL_Point MESSAGE_SHIFT{30, 18};
  static constexpr SDL_Point MESSAGE_SIZE{294, 274};
  static constexpr SDL_Point BUTTON_OK_SHIFT{145, 309};
  static constexpr SDL_Point LOGO_SHIFT{46, 18};
  static constexpr SDL_Point TEXT1_SHIFT{146, 177};
  static constexpr SDL_Point TEXT2_SHIFT{146, 201};
  static constexpr SDL_Point TEXT3_SHIFT{146, 225};
  static constexpr SDL_Point TEXT4_SHIFT{146, 249};
  static constexpr StyleText STYLE_TEXT{FontFamily::MSSansSerif, 12, {0, 0, 0, 255}, {0, 0, 0, 0}, StyleText::AlignH::center};

  MouseStateMachine<WindowName::WindowAbout, SDL_BUTTON_LEFT> m_mouse{};
  ResourceManager<WindowName::WindowAbout> m_resource_manager{m_window.get_windowID()};
  TextureTiled& m_texture_bg{m_resource_manager.load_texture_tiled("background2.png", WINDOW_SIZE, {}, {1, 0})};

  const Texture& m_texture_button_ok{m_resource_manager.load_texture("btn_ok.png")};
  const Texture& m_texture_button_ok_pressed{m_resource_manager.load_texture("btn_ok_pressed.png")};

  const Texture& m_texture_logo{m_resource_manager.load_texture("logo.png")};
  TextureDrawable m_logo{m_texture_logo, LOGO_SHIFT};

  ButtonImage m_button_ok{m_texture_button_ok, m_texture_button_ok_pressed, [this]() { m_running = false; }, BUTTON_OK_SHIFT};
  ButtonImageController<WindowName::WindowAbout, 1> m_button_controller{make_array<ButtonImageR>(m_button_ok)};

  Text m_text1_about{m_window.get_renderer(), u"© 1995, Jarosław Lewandowski", TEXT1_SHIFT, StyleText{STYLE_TEXT}};
  Text m_text2_about{m_window.get_renderer(), u"lewandow@gumbeers.elka.pg.gda.pl", TEXT2_SHIFT, StyleText{STYLE_TEXT}};
  Text m_text3_about{m_window.get_renderer(), u"odtworzone przez mhyzy155", TEXT3_SHIFT, StyleText{STYLE_TEXT}};
  Text m_text4_about{m_window.get_renderer(), u"github.com/mhyzy155", TEXT4_SHIFT, StyleText{STYLE_TEXT}};

  Container<5> m_container_message{m_window.get_windowID(),
                                   MESSAGE_SHIFT,
                                   Style{MESSAGE_SIZE,
                                         {},
                                         Color::GRAY,
                                         Style::BorderType::inwards,
                                         1,
                                         Color::GRAY},
                                   make_array<DrawableR>(m_logo, m_text1_about, m_text2_about, m_text3_about, m_text4_about)};
  const Container<3> m_container{m_window.get_windowID(),
                                 {},
                                 Style{WINDOW_SIZE, {}, {}, Style::BorderType::outwards, 1, Color::GRAY},
                                 make_array<DrawableR>(m_texture_bg, m_button_ok, m_container_message)};

 public:
  WindowAbout();
  virtual void update();
  void draw() const;
  void handle_event(const SDL_Event& event);
};

#endif
