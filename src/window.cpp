#include "../include/window.hpp"

#include <stdexcept>

Window::Window(SDL_Point t_size, Uint32 flags) {
  SDL_Window* _window;
  SDL_Renderer* _renderer;
  if (SDL_CreateWindowAndRenderer(t_size.x, t_size.y, flags, &_window, &_renderer) == -1) {
    throw std::runtime_error("SDL_CreateWindowAndRenderer");
  }
  m_window = std::unique_ptr<SDL_Window, WindowDeleter>(_window);
  m_renderer = std::unique_ptr<SDL_Renderer, RendererDeleter>(_renderer);
}

/*
Window::Window(Window&& other) noexcept : m_size{other.m_size}, m_window{other.m_window}, m_renderer{other.m_renderer} {
  other.m_renderer = nullptr;
  other.m_window = nullptr;
}
*/

SDL_Window* Window::get_window() const {
  return m_window.get();
}

SDL_Renderer* Window::get_renderer() const {
  return m_renderer.get();
}

Uint32 Window::get_windowID() const {
  return SDL_GetWindowID(m_window.get());
}

void Window::clear() const {
  if (SDL_SetRenderDrawColor(m_renderer.get(), 0, 0, 0, SDL_ALPHA_OPAQUE) < 0) {
    Logger::log("SDL_SetRenderDrawColor error: " + std::string{SDL_GetError()}, LoggerMode::error);
  }
  SDL_RenderClear(m_renderer.get());
}

void Window::display() const {
  SDL_RenderPresent(m_renderer.get());
}