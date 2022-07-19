#ifndef KULKI_FUNCTOREVENT_HPP
#define KULKI_FUNCTOREVENT_HPP

// TODO: split into .hpp and .cpp

#include "userevents.hpp"

struct FunctorEvent {
  const Uint32 m_windowID;

  constexpr FunctorEvent(const Uint32 t_windowID) : m_windowID{t_windowID} {};
};

struct FunctorNewgame : public FunctorEvent {
  constexpr FunctorNewgame(const Uint32 t_windowID) : FunctorEvent{t_windowID} {};

  void operator()() const {
    push_event(UserEvents::USER_MENUCOLLAPSE, m_windowID);
    push_event(UserEvents::USER_NEWGAME, m_windowID);
  }
};

struct FunctorShowScoreboard : public FunctorEvent {
  constexpr FunctorShowScoreboard(const Uint32 t_windowID) : FunctorEvent{t_windowID} {};

  void operator()() const {
    push_event(UserEvents::USER_MENUCOLLAPSE, m_windowID);
    SDL_Event event;
    event.type = UserEvents::USER_SHOWSCORE;
    event.window.windowID = m_windowID;
    //event.user.data1 = const_cast<uint8_t*>(&m_n);
    SDL_PushEvent(&event);
  }
};

struct FunctorShowQuit : public FunctorEvent {
  constexpr FunctorShowQuit(const Uint32 t_windowID) : FunctorEvent{t_windowID} {};

  void operator()() const {
    push_event(UserEvents::USER_MENUCOLLAPSE, m_windowID);
    push_event(UserEvents::USER_SHOWQUIT, m_windowID);
  }
};

struct FunctorChangeColors : public FunctorEvent {
  const uint8_t m_n;

  constexpr FunctorChangeColors(const Uint32 t_windowID, const uint8_t t_n) : FunctorEvent{t_windowID}, m_n{t_n} {};

  void operator()() const {
    push_event(UserEvents::USER_MENUCOLLAPSE, m_windowID);
    SDL_Event event;
    event.type = UserEvents::USER_CHANGECOLORS;
    event.window.windowID = m_windowID;
    event.user.data1 = const_cast<uint8_t*>(&m_n);
    SDL_PushEvent(&event);
  }
};

struct FunctorChangeHint : public FunctorEvent {
  constexpr FunctorChangeHint(const Uint32 t_windowID) : FunctorEvent{t_windowID} {};

  void operator()(const bool& x) const {
    push_event(UserEvents::USER_MENUCOLLAPSE, m_windowID);
    SDL_Event event;
    event.type = UserEvents::USER_CHANGEHINT;
    event.window.windowID = m_windowID;
    event.user.data1 = const_cast<bool*>(&x);
    SDL_PushEvent(&event);
  }
};

struct FunctorChangeTexture : public FunctorEvent {
  constexpr FunctorChangeTexture(const Uint32 t_windowID) : FunctorEvent{t_windowID} {};

  void operator()(const bool& x) const {
    push_event(UserEvents::USER_MENUCOLLAPSE, m_windowID);
    SDL_Event event;
    event.type = UserEvents::USER_CHANGETEXTURE;
    event.window.windowID = m_windowID;
    event.user.data1 = const_cast<bool*>(&x);
    SDL_PushEvent(&event);
  }
};

struct FunctorShowContents : public FunctorEvent {
  constexpr FunctorShowContents(const Uint32 t_windowID) : FunctorEvent{t_windowID} {};

  void operator()() const {
    push_event(UserEvents::USER_SHOWCONTENTS, m_windowID);
  }
};

struct FunctorShowTutorial : public FunctorEvent {
  constexpr FunctorShowTutorial(const Uint32 t_windowID) : FunctorEvent{t_windowID} {};

  void operator()() const {
    push_event(UserEvents::USER_SHOWTUTORIAL, m_windowID);
  }
};

struct FunctorShowCommands : public FunctorEvent {
  constexpr FunctorShowCommands(const Uint32 t_windowID) : FunctorEvent{t_windowID} {};

  void operator()() const {
    push_event(UserEvents::USER_SHOWCOMMANDS, m_windowID);
  }
};

struct FunctorShowShortcuts : public FunctorEvent {
  constexpr FunctorShowShortcuts(const Uint32 t_windowID) : FunctorEvent{t_windowID} {};

  void operator()() const {
    push_event(UserEvents::USER_SHOWSHORTCUTS, m_windowID);
  }
};

struct FunctorShowAbout : public FunctorEvent {
  constexpr FunctorShowAbout(const Uint32 t_windowID) : FunctorEvent{t_windowID} {};

  void operator()() const {
    push_event(UserEvents::USER_MENUCOLLAPSE, m_windowID);
    push_event(UserEvents::USER_SHOWABOUT, m_windowID);
  }
};

#endif