#ifndef KULKI_USEREVENTS_HPP
#define KULKI_USEREVENTS_HPP

#if defined(_WIN32) || defined(WIN32)
#include "SDL.h"
#else
#include <SDL2/SDL.h>
#endif

namespace UserEvents{ // make it static?
  constexpr Uint32 USER_QUIT = SDL_USEREVENT;
  constexpr Uint32 USER_NEWGAME = SDL_USEREVENT + 1;
  constexpr Uint32 USER_NEWSCORE = SDL_USEREVENT + 2;
  constexpr Uint32 USER_SHOWSCORE = SDL_USEREVENT + 3;
  constexpr Uint32 USER_SHOWQUIT = SDL_USEREVENT + 4;
  constexpr Uint32 USER_GAMEOVER = SDL_USEREVENT + 5;
  constexpr Uint32 USER_CHANGECOLORS = SDL_USEREVENT + 6;
  constexpr Uint32 USER_CHANGEHINT = SDL_USEREVENT + 7;
  constexpr Uint32 USER_CHANGETEXTURE = SDL_USEREVENT + 8;
  constexpr Uint32 USER_SHOWCONTENTS = SDL_USEREVENT + 9;
  constexpr Uint32 USER_SHOWTUTORIAL = SDL_USEREVENT + 10;
  constexpr Uint32 USER_SHOWCOMMANDS = SDL_USEREVENT + 11;
  constexpr Uint32 USER_SHOWSHORTCUTS = SDL_USEREVENT + 12;
  constexpr Uint32 USER_SHOWABOUT = SDL_USEREVENT + 13;
  constexpr Uint32 USER_REQUESTMOVE = SDL_USEREVENT + 14;
  constexpr Uint32 USER_MOVEBALL = SDL_USEREVENT + 15;
  constexpr Uint32 USER_FINDMATCHES = SDL_USEREVENT + 16;
  constexpr Uint32 USER_MENUCOLLAPSE = SDL_USEREVENT + 17;
  constexpr Uint32 USER_FLASHOTHERWINDOW = SDL_USEREVENT + 18;
  const Uint32 last_user_event = SDL_RegisterEvents(19);
}

/*
struct UserEvents {
  //static Uint32 userevents;
  static constexpr Uint32 register_event(Uint32 userevents);

  const static Uint32 USER_NEWGAME;
  const static Uint32 USER_SHOWSCORE;
  const static Uint32 USER_QUIT;
  const static Uint32 USER_CHANGECOLORS;
  const static Uint32 USER_CHANGEHINT;
  const static Uint32 USER_CHANGETEXTURE;
  const static Uint32 USER_SHOWCONTENTS;
  const static Uint32 USER_SHOWTUTORIAL;
  const static Uint32 USER_SHOWCOMMANDS;
  const static Uint32 USER_SHOWSHORTCUTS;
  const static Uint32 USER_SHOWABOUT;
  const static Uint32 USER_REQUESTMOVE;
  const static Uint32 USER_MOVEBALL;
  const static Uint32 USER_FINDMATCHES;
};
*/

void push_event(Uint32 event_type, Uint32 windowID = 0);

#endif
