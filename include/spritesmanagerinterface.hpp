#ifndef KULKI_SPRITESMANAGERINTERFACE_HPP
#define KULKI_SPRITESMANAGERINTERFACE_HPP

#include "sprite.hpp"

template <typename T>
struct IteratorConst {
  const T* p;
  T& operator*() const { return *p; }
  bool operator!=(const IteratorConst& rhs) const {
    return p != rhs.p;
  }
  void operator++() { ++p; }
};

class SpritesManagerInterface {
 public:
  virtual ~SpritesManagerInterface() = default;
  virtual constexpr const IteratorConst<Sprite> begin() const = 0;
  virtual constexpr const IteratorConst<Sprite> end() const = 0;
  virtual constexpr const Sprite& operator[](size_t pos) const = 0;
  virtual constexpr const Sprite& get(size_t pos) const = 0;
  virtual void update(size_t row) = 0;
};

#endif