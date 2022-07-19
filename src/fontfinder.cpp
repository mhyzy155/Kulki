#include "../include/fontfinder.hpp"

#include <filesystem>
#include "../include/logger.hpp"

std::string_view FontFinder::search(FontFamily ff) {
  const auto it = m_lookup.find(ff);
  if (it != m_lookup.end()) {
    for (const auto& sv : it->second) {
      if (std::filesystem::exists(sv)) {
        Logger::log("Found font " + std::string(sv));
        m_cache.emplace(ff, sv);
        return sv;
      }
    }
  }
  return "";
}

std::string_view FontFinder::find(FontFamily ff) {
  const auto it = m_cache.find(ff);
  if (it != m_cache.end()) {
    return it->second;
  } else {
    return search(ff);
  }
}

std::unordered_map<FontFamily, std::string_view> FontFinder::m_cache{};

#if defined(_WIN32) || defined(WIN32)
const std::unordered_map<FontFamily, std::vector<std::string_view>> FontFinder::m_lookup{
    {FontFamily::Tahoma, std::vector<std::string_view>{"C:\\Windows\\Fonts\\Tahoma.ttf"}},
    {FontFamily::Marlett, std::vector<std::string_view>{"C:\\Windows\\Fonts\\marlett.ttf"}},
    {FontFamily::MSSansSerif, std::vector<std::string_view>{"C:\\Windows\\Fonts\\micross.ttf"}}};
#elif __APPLE__
const std::unordered_map<FontFamily, std::vector<std::string_view>> FontFinder::m_lookup{
    {FontFamily::Tahoma, std::vector<std::string_view>{"/System/Library/Fonts/Supplemental/Tahoma.ttf"}},
    {FontFamily::MSSansSerif, std::vector<std::string_view>{"/System/Library/Fonts/Supplemental/Microsoft Sans Serif.ttf"}}};
#else
const std::unordered_map<FontFamily, std::vector<std::string_view>> FontFinder::m_lookup{
    {FontFamily::Tahoma, std::vector<std::string_view>{"/usr/share/fonts/dejavu/DejaVuSansCondensed.ttf", "/usr/share/fonts/TTF/DejaVuSansCondensed.ttf"}},
    {FontFamily::MSSansSerif, std::vector<std::string_view>{"/usr/share/fonts/liberation/LiberationSans-Bold.ttf"}}};
#endif