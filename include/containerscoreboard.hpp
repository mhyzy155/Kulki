#ifndef KULKI_CONTAINERSCOREBOARD_HPP
#define KULKI_CONTAINERSCOREBOARD_HPP

#include <codecvt>
#include <locale>

#include "container.hpp"
#include "drawablerenderer.hpp"
#include "logger.hpp"
#include "macros.hpp"
#include "mapfixed.hpp"
#include "math.hpp"
#include "scoreboarddata.hpp"
#include "text.hpp"
#include "textbox.hpp"
#include "utils_containers.hpp"

template <size_t Rows = 10>
class ContainerScoreboard : public DrawableRenderer {
  static constexpr SDL_Point NAME_SHIFT{22, 17};
  static constexpr SDL_Point SCORE_SHIFT{141, 17};
  static constexpr SDL_Point ENTRY_FIRST_SHIFT{14, 53};
  static constexpr StyleText STYLE_TEXT{FontFamily::MSSansSerif, 13};
  static constexpr StyleText STYLE_TEXT_SCORE{FontFamily::MSSansSerif, 13, {0, 0, 0, 255}, {0, 0, 0, 0}, StyleText::AlignH::right};
  static constexpr Style TABLE_STYLE{{214, 300}, {}, Color::GRAY, Style::BorderType::inwards, 1, Color::GRAY};
  static constexpr Style STYLE_TEXTBOX{{100, 24}, {2, 3, 0, 0}, {255, 255, 255, 255}, Style::BorderType::solid, 1, {0, 0, 0, 255}};

  ScoreboardData& m_scoreboard_data;
  Text m_text_name{this->m_renderer, u"Imię", NAME_SHIFT, StyleText{STYLE_TEXT}};
  Text m_text_score{this->m_renderer, u"Wynik", SCORE_SHIFT, StyleText{STYLE_TEXT}};
  std::unique_ptr<TextBox> m_text_box{nullptr};
  std::array<std::pair<Text, Text>, Rows> m_text_rows;
  Container<2> m_container;

 public:
  ContainerScoreboard(ScoreboardData& t_scoreboard_data, const Uint32 windowID, const SDL_Point t_shift)
  : DrawableRenderer(windowID, t_shift),
    m_scoreboard_data{t_scoreboard_data},
    m_container{windowID,
                t_shift,
                Style{TABLE_STYLE},
                make_array<DrawableR>(m_text_name, m_text_score)},
    m_text_rows{filled_array_incr<Rows>([this, it = m_scoreboard_data.map().begin(), it_input = m_scoreboard_data.get_recent_it(), shift = this->m_shift + ENTRY_FIRST_SHIFT](const size_t i) mutable {
      auto pair = std::make_pair(Text{this->m_renderer, it->second, shift, StyleText{STYLE_TEXT}}, Text{this->m_renderer, std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t>().from_bytes(std::to_string(it->first)), shift + SDL_Point{193, -2}, StyleText{STYLE_TEXT_SCORE}});
      if (it == it_input) {
        this->m_text_box = std::make_unique<TextBox>(this->m_renderer, u"", shift-SDL_Point{4, 5}, StyleText{STYLE_TEXT}, Style{STYLE_TEXTBOX}, 12);
      }
      ++it;
      shift += SDL_Point{0, 24};
      return pair;
    })} {}

  ContainerScoreboard(const ContainerScoreboard&) = default;
  ContainerScoreboard& operator=(const ContainerScoreboard&) = default;
  ContainerScoreboard(ContainerScoreboard&&) = default;
  ContainerScoreboard& operator=(ContainerScoreboard&&) = default;

  ~ContainerScoreboard(){
    Logger::log("ContainerScoreboard Dtor");
    if(m_text_box){
      m_scoreboard_data.set_recent(m_text_box->str());
    }
  }

  void draw() const noexcept override {
    m_container.draw();

    for (const auto& [name, score] : m_text_rows) {
      name.draw();
      score.draw();
    }

    CHECK_THEN(m_text_box, draw());

    // draw separating lines
    const auto [rd, gd, bd, ad] = TABLE_STYLE.background_color - SDL_Color{64, 64, 64, 0};
    const auto [rl, gl, bl, al] = TABLE_STYLE.background_color + SDL_Color{64, 64, 64, 0};
    const auto shift = this->m_shift;

    SDL_SetRenderDrawColor(this->m_renderer, rd, gd, bd, ad);
    SDL_RenderDrawLine(this->m_renderer, shift.x+7, shift.y+40, shift.x+204, shift.y+40);

    SDL_SetRenderDrawColor(this->m_renderer, rl, gl, bl, al);
    SDL_RenderDrawLine(this->m_renderer, shift.x+7, shift.y+41, shift.x+204, shift.y+41);
    SDL_RenderDrawLine(this->m_renderer, shift.x+119, shift.y+9, shift.x+119, shift.y+288);

    SDL_SetRenderDrawColor(this->m_renderer, rd, gd, bd, ad);
    SDL_RenderDrawLine(this->m_renderer, shift.x+118, shift.y+9, shift.x+118, shift.y+288);
  }

  bool react(const SDL_Event& event) override {
    if (m_text_box) {
      return m_text_box->react(event);
    }
    return false;
  }
};

#endif