#include "../include/textbox.hpp"

#include "../include/logger.hpp"

TextBox::TextBox(SDL_Renderer* t_renderer, const std::u16string& t_text, const SDL_Point t_shift, StyleText&& t_style_text, Style&& t_style, size_t t_size_max)
: DrawableRenderer(t_renderer, t_shift, std::move(t_style)),
  m_size_max{t_size_max},
  m_string{t_text},
  m_cursor_pos{m_string.length()},
  m_text{m_renderer, m_string, m_shift + SDL_Point{m_style.margin.x, m_style.margin.y}, std::move(t_style_text)},
  m_precursor_size{m_text.get_size()} {
}

void TextBox::draw() const noexcept {
  SDL_Rect rect_shifted{m_shift.x, m_shift.y, m_style.size.x, m_style.size.y};

  draw_background(rect_shifted);

  m_text.draw();

  static constexpr auto cycle_len = 2000;
  if(int(SDL_GetTicks() % cycle_len) < int(cycle_len * 0.5)){
    const auto shift = m_shift + SDL_Point{m_style.margin.x, m_style.margin.y-1};
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(m_renderer, shift.x + m_precursor_size.x, shift.y, shift.x + m_precursor_size.x, shift.y + m_precursor_size.y);
  }

  draw_border(rect_shifted);
}

bool TextBox::react(const SDL_Event& event) {
  switch (event.type) {
    case SDL_TEXTINPUT:
      Logger::log("SDL_TEXTINPUT");
      if (m_string.size() < m_size_max) {
        auto substring = m_converter.from_bytes(event.text.text);
        m_string.insert(m_cursor_pos, substring);
        m_cursor_pos += substring.length();
        m_precursor_size = m_text.get_size(m_string.substr(0, m_cursor_pos));
        m_text.update_string(m_string);
        return true;
      }
      break;
    case SDL_KEYDOWN:
      Logger::log("SDL_KEYDOWN");
      switch (event.key.keysym.sym) {
        case SDLK_BACKSPACE:
          if (m_cursor_pos > 0) {
            Logger::log("  SDLK_BACKSPACE");
            --m_cursor_pos;
            m_string.erase(m_cursor_pos, 1);
            m_precursor_size = m_text.get_size(m_string.substr(0, m_cursor_pos));
            m_text.update_string(m_string);
            return true;
          }
          break;
        case SDLK_LEFT:
          Logger::log("  SDLK_LEFT");
          if (m_cursor_pos > 0) {
            --m_cursor_pos;
            m_precursor_size = m_text.get_size(m_string.substr(0, m_cursor_pos));
            return true;
          }
          break;
        case SDLK_RIGHT:
          Logger::log("  SDLK_RIGHT");
          if(m_cursor_pos < m_string.length()){
            ++m_cursor_pos;
            m_precursor_size = m_text.get_size(m_string.substr(0, m_cursor_pos));
            return true;
          }
          break;
      }

      break;
  }
  return false;
}

const std::u16string& TextBox::str() const {
  return m_string;
}