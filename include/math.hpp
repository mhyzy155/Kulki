#ifndef KULKI_MATH_HPP
#define KULKI_MATH_HPP

#if defined(_WIN32) || defined(WIN32)
#include "SDL.h"
#else
#include <SDL2/SDL.h>
#endif

#include <algorithm>
#include <concepts>
#include <utility>

template <class T>
requires std::unsigned_integral<T>
[[nodiscard]] constexpr T mod(const T a, const T b) noexcept {
  T temp = a / b;
  return a - (b * temp);
}

template <class T>
requires std::unsigned_integral<T>
[[nodiscard]] constexpr T quot(const T a, const T b) noexcept {
  return a / b;
}

template <class T>
[[nodiscard]] constexpr std::pair<T, T> modquot(const T a, const T b) noexcept {
  T temp = a / b;
  return std::make_pair(a - (b * temp), temp);
}

template <class T>
struct Point {
  T x;
  T y;

  constexpr Point(T a, T b) : x{a}, y{b} {}
  constexpr Point(std::pair<T, T> pair) : x{pair.first}, y{pair.second} {}
  constexpr bool operator==(const Point<T>& rhs) const {
    return (x == rhs.x) && (y == rhs.y);
  }

  constexpr bool operator<(const Point<T>& rhs) const {
    return (x < rhs.x) || ((x == rhs.x) && (y < rhs.y));
  }
};

constexpr SDL_Color operator+(SDL_Color lhs, const SDL_Color& rhs) {
  lhs.r = Uint8(std::min(lhs.r + rhs.r, 255));
  lhs.g = Uint8(std::min(lhs.g + rhs.g, 255));
  lhs.b = Uint8(std::min(lhs.b + rhs.b, 255));
  lhs.a = Uint8(std::min(lhs.a + rhs.a, 255));
  return lhs;
}

constexpr SDL_Color operator-(SDL_Color lhs, const SDL_Color& rhs) {
  lhs.r = Uint8(std::max(lhs.r - rhs.r, 0));
  lhs.g = Uint8(std::max(lhs.g - rhs.g, 0));
  lhs.b = Uint8(std::max(lhs.b - rhs.b, 0));
  lhs.a = Uint8(std::max(lhs.a - rhs.a, 0));
  return lhs;
}

constexpr SDL_Point operator+(SDL_Point lhs, const SDL_Point& rhs) {
  lhs.x += rhs.x;
  lhs.y += rhs.y;
  return lhs;
}

constexpr SDL_Point& operator+=(SDL_Point& lhs, SDL_Point&& rhs) {
  lhs.x += rhs.x;
  lhs.y += rhs.y;
  return lhs;
}

constexpr SDL_Point operator-(SDL_Point lhs, const SDL_Point& rhs) {
  lhs.x = std::max(lhs.x - rhs.x, 0);
  lhs.y = std::max(lhs.y - rhs.y, 0);
  return lhs;
}

constexpr SDL_Rect operator+(SDL_Rect lhs, const SDL_Point& rhs) {
  lhs.x += rhs.x;
  lhs.y += rhs.y;
  return lhs;
}

constexpr SDL_Rect operator-(SDL_Rect lhs, const SDL_Point& rhs) {
  lhs.x = std::max(lhs.x - rhs.x, 0);
  lhs.y = std::max(lhs.y - rhs.y, 0);
  return lhs;
}

#endif