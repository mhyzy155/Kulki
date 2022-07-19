#ifndef KULKI_SCOREBOARDDATA_HPP
#define KULKI_SCOREBOARDDATA_HPP

#include <functional>
#include <map>
#include <string>

class ScoreboardData {
  using Map = std::multimap<size_t, std::u16string, std::greater<size_t>>;
  static constexpr size_t MAX_NO_SCORES{10};
  static constexpr auto PATH = "BestScr.dat";
  Map m_multimap;
  Map::iterator m_recent{m_multimap.end()};

  Map load_map() const;
  Map load_map_default() const;
  Map::const_iterator last() const;

 public:
  ScoreboardData();
  ~ScoreboardData();
  bool is_competetive(size_t score) const;
  void insert(size_t score);
  void set_recent(const std::u16string& name);
  Map::const_iterator get_recent_it() const;
  const Map& map() const;
};

#endif