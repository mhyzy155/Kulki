#include "../include/windowmain.hpp"

#include "../include/logger.hpp"

WindowMain::WindowMain(GameState& t_gamestate)
: WindowInteractive(WINDOW_SIZE, "Kulki"),
  m_gamestate{t_gamestate} {}

void WindowMain::draw() const {
  m_window.clear();
  m_texture_bg.draw();
  container_score.draw();
  container_hint.draw();
  container_board.draw();
  m_barmenu.draw();
  m_window.display();
}

void WindowMain::update() {
  container_board.update();
}

void WindowMain::handle_event(const SDL_Event& event) {
  switch (event.type) {
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
        case SDLK_F1:
          Logger::log("F1");
          break;
        case SDLK_F2:
          Logger::log("F2");
          new_game();
          break;
      }
      break;
    case SDL_MOUSEMOTION:
      if (m_blocked) {
        push_event(UserEvents::USER_FLASHOTHERWINDOW, m_window.get_windowID());
      } else {
        m_mouse.handle_mouse_motion(event);
        react_mouse_motion(event);
      }
      break;
    case SDL_MOUSEBUTTONDOWN:
      if (m_blocked) {
        push_event(UserEvents::USER_FLASHOTHERWINDOW, m_window.get_windowID());
      } else {
        m_mouse.handle_mouse_button_down(event);
        react_mousebutton_down(event);
      }
      break;
    case SDL_MOUSEBUTTONUP:
      if (!m_blocked) {
        m_mouse.handle_mouse_button_up(event);
      }
      break;
    case UserEvents::USER_NEWGAME:
      Logger::log("USER_NEWGAME");
      new_game();
      break;
    case UserEvents::USER_CHANGECOLORS:
      Logger::log("USER_CHANGECOLORS");
      m_gamestate.colors = *static_cast<uint8_t*>(event.user.data1);
      new_game();
      break;
    case UserEvents::USER_CHANGEHINT:
      Logger::log("USER_CHANGEHINT");
      m_gamestate.hint = *static_cast<bool*>(event.user.data1);
      break;
    case UserEvents::USER_CHANGETEXTURE:
      Logger::log("USER_CHANGETEXTURE");
      m_gamestate.textures_alt = *static_cast<bool*>(event.user.data1);
      m_sprites_balls->update(size_t(m_gamestate.textures_alt));
      break;
    case UserEvents::USER_SHOWCONTENTS:
      Logger::log("USER_SHOWCONTENTS");
      break;
    case UserEvents::USER_SHOWTUTORIAL:
      Logger::log("USER_SHOWTUTORIAL");
      break;
    case UserEvents::USER_SHOWCOMMANDS:
      Logger::log("USER_SHOWCOMMANDS");
      break;
    case UserEvents::USER_SHOWSHORTCUTS:
      Logger::log("USER_SHOWSHORTCUTS");
      break;
    case UserEvents::USER_SHOWABOUT:
      Logger::log("USER_SHOWABOUT");
      break;
    case UserEvents::USER_REQUESTMOVE: {
      Logger::log("USER_REQUESTMOVE");
      const auto& from = *static_cast<Point<size_t>*>(event.user.data1);
      const auto& to = *static_cast<Point<size_t>*>(event.user.data2);
      const auto path = m_board.get_path(from, to);
      if (!path.empty()) {
        m_board.move(from, to);
        container_board.move_ball(path);
      }
      break;
    }
    case UserEvents::USER_MOVEBALL: {
      Logger::log("USER_MOVEBALL");
      const auto& ball_moved = *static_cast<std::pair<Point<size_t>, uint8_t>*>(event.user.data1);
      handle_matches(std::map<Point<size_t>, uint8_t>{ball_moved}, [this]() { draw_after_move(); });
      break;
    }
    case UserEvents::USER_FINDMATCHES: {
      Logger::log("USER_FINDMATCHES");
      const auto& balls_new = *static_cast<std::map<Point<size_t>, uint8_t>*>(event.user.data1);
      handle_matches(balls_new, [this]() {if (m_board.is_full()) game_over(); });
      container_hint.update_hint(m_board.get_drawn());
      break;
    }
    case UserEvents::USER_MENUCOLLAPSE:
      Logger::log("USER_MENUCOLLAPSE");
      m_barmenu.collapse();
      break;
  }
}

void WindowMain::react_mousebutton_down(const SDL_Event& event) {
  m_barmenu.react_mousebutton_down(event);
  container_board.react(event);
}

void WindowMain::react_mouse_motion(const SDL_Event& event) {
  m_barmenu.react_mouse_motion(event);
}

void WindowMain::new_game() {
  m_board.reset();
  container_score.update_score(0);
  container_hint.update_hint();
  container_board.reset();
  container_board.add_balls(m_board.index_to_point(m_board.init(5)));
}

void WindowMain::game_over() {
  Logger::log("Game over.", LoggerMode::info);
  if (const auto score = m_board.get_score(); m_scoreboard_data.is_competetive(score)) {
    m_scoreboard_data.insert(score);
    send_scoreboard(UserEvents::USER_NEWSCORE);
  } else {
    push_event(UserEvents::USER_GAMEOVER, m_window.get_windowID());
  }
}

void WindowMain::draw_after_move() {
  const auto drawn_balls = m_board.add_random();
  container_board.add_balls(m_board.index_to_point(drawn_balls));
}

void WindowMain::send_scoreboard(Uint32 event_type) {
  SDL_Event event;
  event.type = event_type;
  event.window.windowID = m_window.get_windowID();
  event.user.data1 = &m_scoreboard_data;
  SDL_PushEvent(&event);
}

void WindowMain::handle_matches(const std::map<Point<size_t>, uint8_t>& balls, const std::function<void()>& fn_matches_empty) {
  const auto matches = m_board.find_matches(m_board.point_to_index(balls));

  if (matches.empty()) {
    fn_matches_empty();
  } else {
    container_score.update_score(m_board.clear_matches(matches));
    container_board.remove_balls(m_board.index_to_point(matches));
  }
}