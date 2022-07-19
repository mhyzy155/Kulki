#ifndef KULKI_WINDOWMAIN_HPP
#define KULKI_WINDOWMAIN_HPP

#include "barmenu.hpp"
#include "board.hpp"
#include "buttondivider.hpp"
#include "buttonexpandable.hpp"
#include "buttonfun.hpp"
#include "buttonfunkey.hpp"
#include "buttonradio.hpp"
#include "buttonradiocontroller.hpp"
#include "buttonswitchfun.hpp"
#include "containerboard.hpp"
#include "containerhint.hpp"
#include "containerscore.hpp"
#include "dropdownlistheaded.hpp"
#include "dropdownlistheadednested.hpp"
#include "functorevent.hpp"
#include "gamestate.hpp"
#include "mouse.hpp"
#include "resourcemanager.hpp"
#include "scoreboarddata.hpp"
#include "texturetiled.hpp"
#include "utils_containers.hpp"
#include "windowinteractive.hpp"

class WindowMain : public WindowInteractive {
  static constexpr SDL_Point WINDOW_SIZE{638, 452};
  static constexpr SDL_Point BACKGROUND_SHIFT{0, 20};
  static constexpr SDL_Point SCORE_SHIFT = BACKGROUND_SHIFT + SDL_Point{10, 10};
  static constexpr SDL_Point HINT_SHIFT = BACKGROUND_SHIFT + SDL_Point{10, 270};
  static constexpr SDL_Point BOARD_SHIFT = BACKGROUND_SHIFT + SDL_Point{220, 10};
#if defined(_WIN32) || defined(WIN32)
  static constexpr SDL_Rect TEXT_MARGIN{16, 1, 22, 2};
  static constexpr SDL_Rect TEXT_HEAD_MARGIN{5, 2, 7, 3};
#else
  static constexpr SDL_Rect TEXT_MARGIN{16, 1, 22, 3};
  static constexpr SDL_Rect TEXT_HEAD_MARGIN{5, 2, 6, 4};
#endif
  static constexpr Style BUTTON_STYLE{{0, 0}, TEXT_MARGIN};
  static constexpr Style BUTTON_HEAD_STYLE{{0, 0}, TEXT_HEAD_MARGIN, Color::GRAY_LIGHT};

  GameState& m_gamestate;
  Board<> m_board{m_gamestate};
  MouseStateMachine<WindowName::WindowMain, SDL_BUTTON_LEFT> m_mouse{};
  ButtonRadioController m_button_controller_colors{};
  ScoreboardData m_scoreboard_data{};

  ResourceManager<WindowName::WindowMain> m_resource_manager{m_window.get_windowID()};
  const TextureTiled& m_texture_bg{m_resource_manager.load_texture_tiled("background.png", WINDOW_SIZE - BACKGROUND_SHIFT, {}, BACKGROUND_SHIFT)};
  SpritesManagerInterface* m_sprites_balls{m_resource_manager.load_sprites<9, 2>("balls.png")};

  ButtonFunKey m_btn_newgame{u"Nowa", u"  F2", m_window.get_renderer(), FunctorNewgame(m_window.get_windowID()), SDL_Point{}, Style{BUTTON_STYLE}};
  ButtonFun m_btn_scoreboard{u"Najlepsze wyniki...", m_window.get_renderer(), [this]() {push_event(UserEvents::USER_MENUCOLLAPSE, m_window.get_windowID()); send_scoreboard(UserEvents::USER_SHOWSCORE); }, SDL_Point{}, Style{BUTTON_STYLE}};
  ButtonDivider m_divider1{m_window.get_renderer()};
  ButtonFun m_btn_exit{u"Wyjście", m_window.get_renderer(), FunctorShowQuit(m_window.get_windowID()), SDL_Point{}, Style{BUTTON_STYLE}};
  DropdownListHeaded<4> m_ddlist1{m_window.get_renderer(),
                                  ButtonBase{u"Gra", m_window.get_renderer(), {}, Style{BUTTON_HEAD_STYLE}},
                                  make_array<ButtonBaseR>(m_btn_newgame, m_btn_scoreboard, m_divider1, m_btn_exit)};

  ButtonExpandable m_btn_colors{u"Ilość kolorów", m_window.get_renderer(), SDL_Point{}, Style{BUTTON_STYLE}};
  ButtonSwitchFun m_btn_hint{u"Następne kolory", m_window.get_renderer(), FunctorChangeHint(m_window.get_windowID()), SDL_Point{}, Style{BUTTON_STYLE}};
  ButtonDivider m_btn_divider2{m_window.get_renderer()};
  ButtonSwitchFun m_btn_textures{u"Monitor mono", m_window.get_renderer(), FunctorChangeTexture(m_window.get_windowID()), SDL_Point{}, Style{BUTTON_STYLE}};
  ButtonRadio m_btn_col5{u"5", m_window.get_renderer(), FunctorChangeColors(m_window.get_windowID(), 5), m_button_controller_colors, SDL_Point{}, Style{BUTTON_STYLE}};
  ButtonRadio m_btn_col7{u"7", m_window.get_renderer(), FunctorChangeColors(m_window.get_windowID(), 7), m_button_controller_colors, SDL_Point{}, Style{BUTTON_STYLE}};
  ButtonRadio m_btn_col9{u"9", m_window.get_renderer(), FunctorChangeColors(m_window.get_windowID(), 9), m_button_controller_colors, SDL_Point{}, Style{BUTTON_STYLE}, true};
  DropdownListHeadedNested<4> m_ddlist2{m_window.get_renderer(),
                                        ButtonBase{u"Opcje", m_window.get_renderer(), {}, Style{BUTTON_HEAD_STYLE}},
                                        make_array<ButtonBaseR>(m_btn_colors, m_btn_hint, m_btn_divider2, m_btn_textures),
                                        make_array<std::unique_ptr<DropdownListBase>>(std::make_unique<DropdownList<3>>(m_window.get_renderer(), make_array<ButtonBaseR>(m_btn_col5, m_btn_col7, m_btn_col9)),
                                                                                      nullptr,
                                                                                      nullptr,
                                                                                      nullptr)};

  ButtonFunKey m_btn_contents{u"Spis treści", u"  F1", m_window.get_renderer(), FunctorShowContents(m_window.get_windowID()), SDL_Point{}, Style{BUTTON_STYLE}};
  ButtonFun m_btn_tutorial{u"Jak grać", m_window.get_renderer(), FunctorShowTutorial(m_window.get_windowID()), SDL_Point{}, Style{BUTTON_STYLE}};
  ButtonFun m_btn_commands{u"Polecenia menu", m_window.get_renderer(), FunctorShowCommands(m_window.get_windowID()), SDL_Point{}, Style{BUTTON_STYLE}};
  ButtonFun m_btn_shortcuts{u"Klawiatura", m_window.get_renderer(), FunctorShowShortcuts(m_window.get_windowID()), SDL_Point{}, Style{BUTTON_STYLE}};
  ButtonDivider m_btn_divider3{m_window.get_renderer()};
  ButtonFun m_btn_about{u"O programie...", m_window.get_renderer(), FunctorShowAbout(m_window.get_windowID()), SDL_Point{}, Style{BUTTON_STYLE}};
  DropdownListHeaded<6> m_ddlist3{m_window.get_renderer(),
                                  ButtonBase{u"Pomoc", m_window.get_renderer(), {}, Style{BUTTON_HEAD_STYLE}},
                                  make_array<ButtonBaseR>(m_btn_contents, m_btn_tutorial, m_btn_commands, m_btn_shortcuts, m_btn_divider3, m_btn_about)};

  BarMenu<3> m_barmenu{m_window.get_windowID(),
                       make_array<DropDownListBaseR>(m_ddlist1, m_ddlist2, m_ddlist3),
                       {},
                       Style().set_background_color(Color::GRAY_LIGHT)};

  ContainerScore container_score{m_window.get_windowID(), SCORE_SHIFT};
  ContainerHint container_hint{m_gamestate, m_window.get_windowID(), HINT_SHIFT};
  ContainerBoard container_board{m_gamestate, m_window.get_windowID(), BOARD_SHIFT};

  void new_game();
  void game_over();
  void draw_after_move();
  void send_scoreboard(Uint32 event_type);
  void handle_matches(const std::map<Point<size_t>, uint8_t>& balls, const std::function<void()>& fn_matches_empty);

 public:
  WindowMain(GameState& t_gamestate);
  void update();
  void handle_event(const SDL_Event& event);
  void draw() const;
  void react_mousebutton_down(const SDL_Event& event);
  void react_mouse_motion(const SDL_Event& event);
};

#endif