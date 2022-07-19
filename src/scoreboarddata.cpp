#include "scoreboarddata.hpp"

#include <filesystem>
#include <iterator>

#include "deserializer.hpp"
#include "logger.hpp"
#include "serializer.hpp"

ScoreboardData::Map ScoreboardData::load_map() const {
  if (std::filesystem::exists(PATH)) {
    Deserializer deserializer{PATH};
    Map map{deserializer.deserialize<Map>()};

    if (map.size() < MAX_NO_SCORES) {
      return load_map_default();
    }

    if (map.size() > MAX_NO_SCORES) {
      const auto overhead = map.size() - MAX_NO_SCORES;
      map.erase(std::prev(map.end(), overhead), map.end());
    }

    return map;
  }
  return load_map_default();
}

ScoreboardData::Map ScoreboardData::load_map_default() const {
  return {{20, u"Józio"},
          {19, u"Zuzia"},
          {18, u"Franek"},
          {17, u"Mirka"},
          {16, u"Zenek"},
          {15, u"Witek"},
          {14, u"Jancio"},
          {13, u"Krzyś"},
          {12, u"Madzia"},
          {11, u"Madzia"}};
}

ScoreboardData::Map::const_iterator ScoreboardData::last() const{
  return std::prev(m_multimap.end());
}

ScoreboardData::ScoreboardData() : m_multimap{load_map()} {}

ScoreboardData::~ScoreboardData() {
  Logger::log("Saving scoreboard.");
  Serializer serializer{PATH};
  Logger::log("Serializer created.");
  serializer.serialize(m_multimap);
  Logger::log("Saved scoreboard.");
}

bool ScoreboardData::is_competetive(size_t score) const {
  return last()->first < score;
}

void ScoreboardData::insert(size_t score) {
  m_multimap.erase(last());
  m_recent = m_multimap.emplace(score, u"Anon");
}

void ScoreboardData::set_recent(const std::u16string& name) {
  Logger::log("Setting recent.");
  if (m_recent != m_multimap.end() && !name.empty()) {
    Logger::log("Str accepted.");
    m_recent->second = name;
  }
  m_recent = m_multimap.end();
}

ScoreboardData::Map::const_iterator ScoreboardData::get_recent_it() const {
  return m_recent;
}

const ScoreboardData::Map& ScoreboardData::map() const {
  return m_multimap;
}