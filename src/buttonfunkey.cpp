#include "../include/buttonfunkey.hpp"

ButtonFunKey::ButtonFunKey(const std::u16string& t_text, const std::u16string& t_text_key, SDL_Renderer* t_renderer, Function&& t_fun_press, const SDL_Point t_shift, Style&& t_style)
: ButtonFun(t_text, t_renderer, std::move(t_fun_press), t_shift, std::move(t_style)),
  m_text_key{t_renderer, t_text_key, t_shift} {
  const auto size = m_text_key.get_size();

  m_text_key.shift(SDL_Point{m_style.size.x - m_style.margin.w, m_style.margin.y});

  m_style.size.x += size.x;
  m_style.size.y = std::max(m_style.size.y, size.y);
}

void ButtonFunKey::shift(SDL_Point t_shift) {
  ButtonFun::shift(t_shift);
  m_text_key.shift(t_shift);
}

void ButtonFunKey::draw() const noexcept {
  ButtonFun::draw();
  m_text_key.draw();
}

void ButtonFunKey::set_hover(bool t_is_hovered) {
  ButtonFun::set_hover(t_is_hovered);
  m_text_key.set_hover(t_is_hovered);
}

SDL_Point ButtonFunKey::get_size() const noexcept{
  const auto size_key = m_text_key.get_size();
  return {m_style.size.x + size_key.x, m_style.size.y};
}

void ButtonFunKey::set_size(SDL_Point t_size){
  const auto size_old = m_style.size;
  m_style.size = t_size;
  m_text_key.shift({m_style.size.x - size_old.x, 0});
}