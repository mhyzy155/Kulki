#include "../include/drawable.hpp"

#include "../include/logger.hpp"

Drawable::Drawable(SDL_Point t_shift) : m_shift{t_shift} {};

void Drawable::shift(SDL_Point t_shift) {
  m_shift = m_shift + t_shift;
}

void Drawable::draw() const noexcept {
  Logger::log("Called virtual draw function.", LoggerMode::warning);
};

bool Drawable::react(const SDL_Event&) {
  return false;
}