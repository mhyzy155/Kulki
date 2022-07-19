#ifndef KULKI_GAMESTATE_HPP
#define KULKI_GAMESTATE_HPP

#include <cstdint>

struct GameState {
  uint8_t colors = 5;
  bool textures_alt = false; //TODO: is this even needed?
  bool hint = false;
};

#endif