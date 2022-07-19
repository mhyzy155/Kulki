#ifndef KULKI_MAPFIXED_HPP
#define KULKI_MAPFIXED_HPP

#include <array>
#include <stdexcept>
#include <utility>

#include "conceptual.hpp"

template <class Key, class Value, size_t N>
class MapFixed {
  std::array<std::pair<Key, Value>, N> data;

 public:
  template <class... Args>
  requires (std::same_as<std::pair<Key, Value>, Args>&&...)
  constexpr MapFixed(Args&&... args)
  : data{{std::forward<Args>(args)...}} {}

  template <Pair P, class... Args>
  requires std::same_as<std::pair<Key, Value>, P> && (std::same_as<P, Args>&&...)
  constexpr MapFixed(P&& arg, Args&&... args)
  : data{{std::forward<P>(arg), std::forward<Args>(args)...}} {}

  constexpr auto& operator[](const Key& key) const {
    for (const auto& [data_key, data_value] : data) {
      if (data_key == key) {
        return data_value;
      }
    }
    throw std::out_of_range("Key does not exist.");
  }

  constexpr bool contains(const Key& key) const {
    for (const auto& [data_key, _] : data) {
      if (data_key == key) {
        return true;
      }
    }
    return false;
  }

  constexpr auto begin() const {
    return data.begin();
  }

  constexpr auto end() const {
    return data.end();
  }
};

template <class Key, class Value, class... Args>
MapFixed(Args...) -> MapFixed<Key, Value, sizeof...(Args)>;

template <Pair P, class... Args>
MapFixed(P p, Args...) -> MapFixed<decltype(p.first), decltype(p.second), sizeof...(Args)+size_t(1)>;

#endif