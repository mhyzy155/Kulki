#include "../include/buttonswitch.hpp"

#if defined(_WIN32) || defined(WIN32)
#define TICK_TEXT u"a"
#define TICK_FF FontFamily::Marlett
#define TICK_SIZE 14
#define ARROW_X_OFF 15
#else
#define TICK_TEXT u"✓"
#define TICK_FF FontFamily::Tahoma
#define TICK_SIZE 12
#define ARROW_X_OFF 12
#endif

#define ARROW_Y_OFF 1

ButtonSwitch::ButtonSwitch(const std::u16string& t_text, SDL_Renderer* t_renderer, const SDL_Point t_shift, Style&& t_style, const bool t_is_checked)
: ButtonBase(t_text, t_renderer, t_shift, std::move(t_style)),
  m_is_checked{t_is_checked},
  m_tick{t_renderer, TICK_TEXT, t_shift + SDL_Point{t_style.margin.x - ARROW_X_OFF, t_style.margin.y + ARROW_Y_OFF}, StyleText{TICK_FF, TICK_SIZE}} {
}

void ButtonSwitch::shift(SDL_Point t_shift) {
  ButtonBase::shift(t_shift);
  m_tick.shift(t_shift);
}

void ButtonSwitch::draw() const noexcept {
  ButtonBase::draw();
  if (m_is_checked) {
    m_tick.draw();
  }
}

void ButtonSwitch::set_hover(bool t_is_hovered) {
  ButtonBase::set_hover(t_is_hovered);
  m_tick.set_hover(t_is_hovered);
}

void ButtonSwitch::press() {
  m_is_checked = !m_is_checked;
}

void ButtonSwitch::uncheck() {
  m_is_checked = false;
}