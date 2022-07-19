#include "../include/buttonexpandable.hpp"

#if defined(_WIN32) || defined(WIN32)
#define ARROW_TEXT u"4"
#define ARROW_FF FontFamily::Marlett
#define ARROW_SIZE 13
#define ARROW_X_OFF 15
#define ARROW_Y_OFF 0
#else
#define ARROW_TEXT u"▶"
#define ARROW_FF FontFamily::Tahoma
#define ARROW_SIZE 9
#define ARROW_X_OFF 12
#define ARROW_Y_OFF 0
#endif

ButtonExpandable::ButtonExpandable(const std::u16string& t_text, SDL_Renderer* t_renderer, const SDL_Point t_shift, Style&& t_style)
: ButtonBase(t_text, t_renderer, t_shift, std::move(t_style)),
  m_arrow{t_renderer, ARROW_TEXT, t_shift, StyleText{ARROW_FF, ARROW_SIZE}} {
  m_arrow.shift(SDL_Point{m_style.size.x - ARROW_X_OFF, m_style.margin.y});
}

void ButtonExpandable::shift(SDL_Point t_shift) {
  ButtonBase::shift(t_shift);
  m_arrow.shift(t_shift);
}

void ButtonExpandable::draw() const noexcept {
  ButtonBase::draw();
  m_arrow.draw();
}

void ButtonExpandable::set_hover(bool t_is_hovered) {
  ButtonBase::set_hover(t_is_hovered);
  m_arrow.set_hover(t_is_hovered);
}

void ButtonExpandable::set_size(SDL_Point t_size) {
  auto size_old = get_size();
  ButtonBase::set_size(t_size);
  auto shift = get_size() - size_old;
  m_arrow.shift(shift);
}