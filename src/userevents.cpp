#include "../include/userevents.hpp"

//const Uint32 UserEvents::last_user_event = SDL_RegisterEvents(14);

//Uint32 UserEvents::userevents = SDL_USEREVENT;

/*
constexpr Uint32 UserEvents::register_event(Uint32 userevents) {
  Uint32 event_base;

  if (userevents + 1 < SDL_LASTEVENT) {
    event_base = userevents + 1;
  } else {
    event_base = Uint32(-1);
  }
  return event_base;
}
*/

/*
const Uint32 UserEvents::USER_NEWGAME = SDL_RegisterEvents(1);
const Uint32 UserEvents::USER_SHOWSCORE = SDL_RegisterEvents(1);
const Uint32 UserEvents::USER_QUIT = SDL_RegisterEvents(1);
const Uint32 UserEvents::USER_CHANGECOLORS = SDL_RegisterEvents(1);
const Uint32 UserEvents::USER_CHANGEHINT = SDL_RegisterEvents(1);
const Uint32 UserEvents::USER_CHANGETEXTURE = SDL_RegisterEvents(1);
const Uint32 UserEvents::USER_SHOWCONTENTS = SDL_RegisterEvents(1);
const Uint32 UserEvents::USER_SHOWTUTORIAL = SDL_RegisterEvents(1);
const Uint32 UserEvents::USER_SHOWCOMMANDS = SDL_RegisterEvents(1);
const Uint32 UserEvents::USER_SHOWSHORTCUTS = SDL_RegisterEvents(1);
const Uint32 UserEvents::USER_SHOWABOUT = SDL_RegisterEvents(1);
const Uint32 UserEvents::USER_REQUESTMOVE = SDL_RegisterEvents(1);
const Uint32 UserEvents::USER_MOVEBALL = SDL_RegisterEvents(1);
const Uint32 UserEvents::USER_FINDMATCHES = SDL_RegisterEvents(1);
*/

/*
const Uint32 UserEvents::USER_NEWGAME = UserEvents::register_event(SDL_USEREVENT);
const Uint32 UserEvents::USER_SHOWSCORE = UserEvents::register_event(SDL_USEREVENT+1);
const Uint32 UserEvents::USER_QUIT = UserEvents::register_event(SDL_USEREVENT+2);
const Uint32 UserEvents::USER_CHANGECOLORS = UserEvents::register_event(SDL_USEREVENT+3);
const Uint32 UserEvents::USER_CHANGEHINT = UserEvents::register_event(SDL_USEREVENT+4);
const Uint32 UserEvents::USER_CHANGETEXTURE = UserEvents::register_event(SDL_USEREVENT+5);
const Uint32 UserEvents::USER_SHOWCONTENTS = UserEvents::register_event(SDL_USEREVENT+6);
const Uint32 UserEvents::USER_SHOWTUTORIAL = UserEvents::register_event(SDL_USEREVENT+7);
const Uint32 UserEvents::USER_SHOWCOMMANDS = UserEvents::register_event(SDL_USEREVENT+8);
const Uint32 UserEvents::USER_SHOWSHORTCUTS = UserEvents::register_event(SDL_USEREVENT+9);
const Uint32 UserEvents::USER_SHOWABOUT = UserEvents::register_event(SDL_USEREVENT+10);
const Uint32 UserEvents::USER_REQUESTMOVE = UserEvents::register_event(SDL_USEREVENT+11);
const Uint32 UserEvents::USER_MOVEBALL = UserEvents::register_event(SDL_USEREVENT+12);
const Uint32 UserEvents::USER_FINDMATCHES = UserEvents::register_event(SDL_USEREVENT+13);
*/

void push_event(Uint32 event_type, Uint32 windowID) {
  SDL_Event event;
  event.type = event_type;
  event.window.windowID = windowID;
  SDL_PushEvent(&event);
}
