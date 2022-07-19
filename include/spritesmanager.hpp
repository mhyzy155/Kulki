#ifndef KULKI_SPRITESMANAGER_HPP
#define KULKI_SPRITESMANAGER_HPP

#include "spritesmanagerinterface.hpp"
#include "utils_containers.hpp"

template <size_t Columns>
class SpritesManager : public SpritesManagerInterface {
  std::array<Sprite, Columns> m_sprites;

 public:
  SpritesManager(const Texture& t_texture)
  : m_sprites{filled_array_incr<Columns>([&t_texture](const size_t i) { return Sprite{t_texture, i}; })} {}

  constexpr const IteratorConst<Sprite> begin() const {
    return IteratorConst<Sprite>{&(*m_sprites.begin())};
  }
  constexpr const IteratorConst<Sprite> end() const {
    return IteratorConst<Sprite>{&(*m_sprites.end())};
  }

  constexpr const Sprite& operator[](size_t pos) const {
    return m_sprites[pos];
  }

  constexpr const Sprite& get(size_t pos) const {
    return m_sprites[pos];
  }

  void update(size_t row) {
    for (size_t i = 0; i < Columns; i++) {
      m_sprites[i].update(row * Columns + i);
    }
  }
};

#endif