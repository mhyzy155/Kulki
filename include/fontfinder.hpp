#ifndef KULKI_FONTFINDER_HPP
#define KULKI_FONTFINDER_HPP

#include <string_view>
#include <unordered_map>
#include <vector>

#include "fontfamily.hpp"
#include "mapfixed.hpp"

class FontFinder {
  static std::unordered_map<FontFamily, std::string_view> m_cache;
  static const std::unordered_map<FontFamily, std::vector<std::string_view>> m_lookup;

  static std::string_view search(FontFamily);

 public:
  static std::string_view find(FontFamily);
};

#endif