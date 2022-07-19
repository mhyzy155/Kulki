#ifndef KULKI_RESOURCEMANAGER_HPP
#define KULKI_RESOURCEMANAGER_HPP

// TODO: add locks

#include <set>
#include <unordered_map>
#include <utility>

#include <cassert>
#include <type_traits>

#include "spritesmanager.hpp"
#include "texture.hpp"
#include "texturetiled.hpp"
#include "windowname.hpp"

static const std::filesystem::path MEDIA_PATH{"../media/"};

template <WindowName name>
class ResourceManager {
  const Uint32 m_id;
  static Uint32 m_id_max;
  SDL_Renderer* const m_renderer;
  static std::unordered_map<std::string, Texture> m_textures;
  static std::unordered_map<std::string, std::set<Uint32>> m_textures_ids;
  static std::unordered_map<std::string, TextureTiled> m_textures_tiled;
  static std::unordered_map<std::string, std::set<Uint32>> m_textures_tiled_ids;
  static std::unordered_map<std::string, std::unique_ptr<SpritesManagerInterface>> m_sprites_managers;
  static std::unordered_map<std::string, std::set<Uint32>> m_sprites_managers_ids;

 public:
  ResourceManager(Uint32 windowID) : m_id{get_unique_id()}, m_renderer{SDL_GetRenderer(SDL_GetWindowFromID(windowID))} {
    Logger::log("ResourceManager ID: " + std::to_string(m_id));
  }

  template <class T>
  void remove_unused(std::unordered_map<std::string, T>& map_resources, std::unordered_map<std::string, std::set<Uint32>>& map_ids) {
    for (auto it = map_ids.begin(); it != map_ids.end();) {
      if (it->second.erase(m_id) > 0 && it->second.empty()) {
        const auto filename = it->first;
        it = map_ids.erase(it);
        map_resources.erase(filename);
      } else {
        ++it;
      }
    }
  }

  ~ResourceManager() {
    remove_unused(m_sprites_managers, m_sprites_managers_ids);
    remove_unused(m_textures, m_textures_ids);
    remove_unused(m_textures_tiled, m_textures_tiled_ids);
    // Logger::log("~ResourceManager() end");
  }

  static Uint32 get_unique_id() {
    return m_id_max++;
  }

  template <class Subclass, class Base, class... Args>
  auto load_ptr(std::unordered_map<std::string, std::unique_ptr<Base>>& map_resources, std::unordered_map<std::string, std::set<Uint32>>& map_ids, const std::string& filename, Args&&... args) {
    if (map_resources.contains(filename)) {
      map_ids[filename].insert(m_id);
      return map_resources[filename].get();
    } else {
      const auto [it, _] = map_resources.emplace(filename, std::make_unique<Subclass>(std::forward<Args>(args)...));
      map_ids.emplace(filename, std::set{m_id});
      return it->second.get();
    }
  }

  template <class T, class... Args>
  T& load(std::unordered_map<std::string, T>& map_resources, std::unordered_map<std::string, std::set<Uint32>>& map_ids, const std::string& filename, Args&&... args) {
    if(const auto it1 = map_resources.find(filename); it1 != map_resources.end()){
      map_ids[filename].insert(m_id);
      return it1->second;
    } else{
      const auto [it2, _] = map_resources.emplace(std::piecewise_construct, std::forward_as_tuple(filename), std::forward_as_tuple(std::forward<Args>(args)...));
      map_ids.emplace(filename, std::set{m_id});
      return it2->second;
    }
  }

  Texture& load_texture(const std::string& filename, SDL_Point t_count = {1, 1}) {
    return load(m_textures, m_textures_ids, filename, MEDIA_PATH / filename, m_renderer, t_count);
  }

  TextureTiled& load_texture_tiled(const std::string& filename, SDL_Point t_size, SDL_Point spacing = {0, 0}, SDL_Point t_shift = {0, 0}) {
    return load(m_textures_tiled, m_textures_tiled_ids, filename, MEDIA_PATH / filename, m_renderer, t_size, spacing, t_shift);
  }

  template <size_t Columns, size_t Rows>
  SpritesManagerInterface* load_sprites(const std::string& filename) {
    auto& texture = load_texture(filename, SDL_Point(Columns, Rows));
    return load_ptr<SpritesManager<Columns>>(m_sprites_managers, m_sprites_managers_ids, filename, texture);
  }
};

template <WindowName name>
Uint32 ResourceManager<name>::m_id_max{0};

template <WindowName name>
std::unordered_map<std::string, Texture> ResourceManager<name>::m_textures{};

template <WindowName name>
std::unordered_map<std::string, std::set<Uint32>> ResourceManager<name>::m_textures_ids{};

template <WindowName name>
std::unordered_map<std::string, TextureTiled> ResourceManager<name>::m_textures_tiled{};

template <WindowName name>
std::unordered_map<std::string, std::set<Uint32>> ResourceManager<name>::m_textures_tiled_ids{};

template <WindowName name>
std::unordered_map<std::string, std::unique_ptr<SpritesManagerInterface>> ResourceManager<name>::m_sprites_managers{};

template <WindowName name>
std::unordered_map<std::string, std::set<Uint32>> ResourceManager<name>::m_sprites_managers_ids{};

#endif

/*

template <WindowName name>
class ResourceManager {
  const Uint32 m_id;
  static Uint32 m_id_max;
  SDL_Renderer* const m_renderer;
  static std::unordered_map<std::string, std::unique_ptr<Texture>> m_textures;
  static std::unordered_map<std::string, std::set<Uint32>> m_textures_ids;
  static std::unordered_map<std::string, std::unique_ptr<TextureTiled>> m_textures_tiled;
  static std::unordered_map<std::string, std::set<Uint32>> m_textures_tiled_ids;
  static std::unordered_map<std::string, std::unique_ptr<SpritesManagerInterface>> m_sprites_managers;
  static std::unordered_map<std::string, std::set<Uint32>> m_sprites_managers_ids;

 public:
  ResourceManager(Uint32 windowID) : m_id{get_unique_id()}, m_renderer{SDL_GetRenderer(SDL_GetWindowFromID(windowID))} {
    Logger::log("ResourceManager ID: " + std::to_string(m_id));
  }

  ~ResourceManager() {
    remove_unused(m_sprites_managers, m_sprites_managers_ids);
    remove_unused(m_textures, m_textures_ids);
    remove_unused(m_textures_tiled, m_textures_tiled_ids);
    //Logger::log("~ResourceManager() end");
  }

  static Uint32 get_unique_id() {
    return m_id_max++;
  }

  Texture* load_texture(const std::string& filename, SDL_Point t_count = {1, 1}) {
    return load(m_textures, m_textures_ids, filename, MEDIA_PATH / filename, m_renderer, t_count);
  }

  TextureTiled* load_texture_tiled(const std::string& filename, SDL_Point t_size, SDL_Point spacing = {0, 0}, SDL_Point t_shift = {0, 0}) {
    return load(m_textures_tiled, m_textures_tiled_ids, filename, MEDIA_PATH / filename, m_renderer, t_size, spacing, t_shift);
  }

  template <size_t Columns, size_t Rows>
  SpritesManagerInterface* load_sprites(const std::string& filename) {
    auto const texture = load_texture(filename, SDL_Point(Columns, Rows));
    return load<SpritesManager<Columns>>(m_sprites_managers, m_sprites_managers_ids, filename, texture);
  }

  template <class Subclass, class Base, class... Args>
  auto load(std::unordered_map<std::string, std::unique_ptr<Base>>& map_resources, std::unordered_map<std::string, std::set<Uint32>>& map_ids, const std::string& filename, Args&&... args) {
    if (map_resources.contains(filename)) {
      map_ids[filename].insert(m_id);
      return map_resources[filename].get();
    } else {
      const auto [it, _] = map_resources.emplace(filename, std::make_unique<Subclass>(std::forward<Args>(args)...));
      map_ids.emplace(filename, std::set{m_id});
      return it->second.get();
    }
  }

  template <class T, class... Args>
  auto load(std::unordered_map<std::string, std::unique_ptr<T>>& map_resources, std::unordered_map<std::string, std::set<Uint32>>& map_ids, const std::string& filename, Args&&... args) {
    return load<T, T, Args...>(map_resources, map_ids, filename, std::forward<Args>(args)...);
  }

  template <class T>
  void remove_unused(std::unordered_map<std::string, std::unique_ptr<T>>& map_resources, std::unordered_map<std::string, std::set<Uint32>>& map_ids) {
    for (auto it = map_ids.begin(); it != map_ids.end();) {
      if (it->second.erase(m_id) > 0 && it->second.empty()) {
        const auto filename = it->first;
        it = map_ids.erase(it);
        map_resources.erase(filename);
      } else {
        ++it;
      }
    }
  }
};

template <WindowName name>
Uint32 ResourceManager<name>::m_id_max{0};

template <WindowName name>
std::unordered_map<std::string, std::unique_ptr<Texture>> ResourceManager<name>::m_textures{};

template <WindowName name>
std::unordered_map<std::string, std::set<Uint32>> ResourceManager<name>::m_textures_ids{};

template <WindowName name>
std::unordered_map<std::string, std::unique_ptr<TextureTiled>> ResourceManager<name>::m_textures_tiled{};

template <WindowName name>
std::unordered_map<std::string, std::set<Uint32>> ResourceManager<name>::m_textures_tiled_ids{};

template <WindowName name>
std::unordered_map<std::string, std::unique_ptr<SpritesManagerInterface>> ResourceManager<name>::m_sprites_managers{};

template <WindowName name>
std::unordered_map<std::string, std::set<Uint32>> ResourceManager<name>::m_sprites_managers_ids{};

*/