#ifndef KULKI_OPTIONAL_TINY_HPP
#define KULKI_OPTIONAL_TINY_HPP

#include <limits>
#include <initializer_list>

/*
namespace std {
template <>
class numeric_limits<SDL_Rect> {
 public:
  static SDL_Rect max() {
    constexpr auto int_max = std::numeric_limits<int>::max();
    return {int_max, int_max, int_max, int_max};
  };
};
}  // namespace std
*/

template <class T>
class optional_max {
  T m_value;

 public:
  constexpr optional_max() : m_value{std::numeric_limits<T>::max()} {}
  constexpr optional_max(const T t_value) : m_value{t_value} {}
  constexpr auto operator=(const T& t_value) {
    m_value = t_value;
    return *this;
  }
  constexpr auto operator=(T&& t_value) {
    m_value = t_value;
    return *this;
  }
  constexpr operator bool() const { return (m_value == std::numeric_limits<T>::max()) ? false : true; }
  constexpr T& value() { return m_value; }
  constexpr const T& value() const { return m_value; }
};

#endif