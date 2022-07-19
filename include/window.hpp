#ifndef KULKI_WINDOW_HPP
#define KULKI_WINDOW_HPP

#if defined(_WIN32) || defined(WIN32)
#include "SDL.h"
#else
#include <SDL2/SDL.h>
#endif

#include <iostream>
#include <memory>

#include "logger.hpp"

class Window {
  struct WindowDeleter {
    void operator()(SDL_Window* t_window) {
      if (t_window) {
        SDL_DestroyWindow(t_window);
        Logger::log("Window deleted.");
      }
    }
  };

  struct RendererDeleter {
    void operator()(SDL_Renderer* t_renderer) {
      if (t_renderer) {
        SDL_DestroyRenderer(t_renderer);
        Logger::log("Renderer deleted.");
      }
    }
  };

 protected:
  //SDL_Point m_size;
  std::unique_ptr<SDL_Window, WindowDeleter> m_window = nullptr;
  std::unique_ptr<SDL_Renderer, RendererDeleter> m_renderer = nullptr;

 public:
  Window(SDL_Point t_size, Uint32 flags = 0);
  virtual ~Window() = default;
  //Window(const Window&) = delete;
  //Window& operator=(const Window&) = delete;
  //Window(Window&& other) noexcept;
  //Window& operator=(Window&& other) = delete;
  SDL_Window* get_window() const;
  SDL_Renderer* get_renderer() const;
  Uint32 get_windowID() const;

  void clear() const;
  void display() const;
};

#endif