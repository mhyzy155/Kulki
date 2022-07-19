#ifndef KULKI_BOARD_HPP
#define KULKI_BOARD_HPP

#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <deque>
#include <iostream>
#include <iterator>
#include <map>
#include <random>
#include <set>
#include <utility>
#include <vector>

#include "algorithm.hpp"
#include "direction.hpp"
#include "gamestate.hpp"
#include "logger.hpp"
#include "math.hpp"
#include "optional_tiny.hpp"
#include "utils_containers.hpp"

template <size_t N = 9, size_t M = 9, size_t TMinLineLen = 5, size_t TDraws = 3>
class Board {
  std::array<uint8_t, N * M> m_array;
  std::array<uint8_t, TDraws> m_drawn;
  const GameState& m_state;
  size_t m_points_per_ball;
  size_t score = 0;
  std::default_random_engine m_engine{static_cast<unsigned long>(std::chrono::steady_clock::now().time_since_epoch().count())};

  constexpr uint8_t at(const Point<size_t> point) const {
    assert((point.x < N) && (point.y < M));
    return m_array[point.y * N + point.x];
  }

  constexpr optional_max<size_t> next_index(const size_t ind, const Direction dir) const {
    assert(ind < N * M);
    switch (dir) {
      case Direction::right:
        if (mod(ind, N) == (N - 1))
          return {};
        else
          return ind + 1;
        break;

      case Direction::rightdown:
        if ((mod(ind, N) == (N - 1)) || (ind >= (M - 1) * N))
          return {};
        else
          return ind + N + 1;
        break;

      case Direction::down:
        if (ind >= (M - 1) * N)
          return {};
        else
          return ind + N;
        break;

      case Direction::leftdown:
        if ((mod(ind, N) == 0) || (ind >= (M - 1) * N))
          return {};
        else
          return ind + N - 1;
        break;

      case Direction::left:
        if (mod(ind, N) == 0)
          return {};
        else
          return ind - 1;
        break;

      case Direction::leftup:
        if ((mod(ind, N) == 0) || (ind < N))
          return {};
        else
          return ind - N - 1;
        break;

      case Direction::up:
        if (ind < N)
          return {};
        else
          return ind - N;
        break;

      case Direction::rightup:
        if ((mod(ind, N) == (N - 1)) || (ind < N))
          return {};
        else
          return ind - N + 1;
        break;

      default:
        return {};
        break;
    }
  }

  constexpr std::set<size_t> traverse_uni(const uint8_t color, size_t ind, const Direction dir) const {
    std::set<size_t> indicies;
    auto next = next_index(ind, dir);
    while (next) {
      const auto val = next.value();
      if (m_array[val] == color) {
        indicies.insert(val);
        next = next_index(val, dir);
      } else {
        break;
      }
    }
    return indicies;
  }

  constexpr std::set<size_t> traverse_bi(const uint8_t color, size_t ind, const Direction dir1, const Direction dir2) const {
    auto backward = traverse_uni(color, ind, dir1);
    auto forward = traverse_uni(color, ind, dir2);
    backward.insert(ind);
    backward.merge(forward);
    return backward;
  }

  constexpr std::array<bool, N * M> get_mask() const {
    std::array<bool, N * M> mask{};
    std::ranges::transform(m_array, mask.begin(), [](const auto x) { return (x == 0) ? false : true; });
    return mask;
  }

  constexpr std::vector<size_t> get_empty_indicies() const {
    std::vector<size_t> indicies;
    std::ranges::for_each(m_array, [i = size_t{0}, &indicies](const auto x) mutable {if (x == 0) indicies.push_back(i); ++i; });
    return indicies;
  }

  constexpr std::vector<size_t> get_neighbor_indicies(const size_t ind) const {
    assert(ind < N * M);
    if (ind < N) {
      if (ind == 0) {
        return std::vector<size_t>{1, N};
      } else if (ind == (N - 1)) {
        return std::vector<size_t>{N - 2, ind + N};
      } else {
        return std::vector<size_t>{ind - 1, ind + 1, ind + N};
      }
    } else if (ind >= (M - 1) * N) {
      if (mod(ind, N) == 0) {
        return std::vector<size_t>{ind - N, ind + 1};
      } else if (ind == (N * M - 1)) {
        return std::vector<size_t>{ind - 1, ind - N};
      } else {
        return std::vector<size_t>{ind - N, ind - 1, ind + 1};
      }
    } else if (mod(ind, N) == 0) {
      return std::vector<size_t>{ind - N, ind + 1, ind + N};
    } else if (mod(ind, N) == (N - 1)) {
      return std::vector<size_t>{ind - N, ind - 1, ind + N};
    } else {
      return std::vector<size_t>{ind - N, ind - 1, ind + 1, ind + N};
    }
  }

  void draw_random(auto& c) {
    std::uniform_int_distribution<unsigned short> distribution(1, m_state.colors);
    std::ranges::generate(c, [&]() { return uint8_t(distribution(m_engine)); });
  }

  std::vector<std::pair<size_t, uint8_t>> place_random(const auto& c) {
    const auto free_cells = get_empty_indicies();

    std::set<size_t> chosen_cells;
    std::ranges::sample(free_cells, std::inserter(chosen_cells, chosen_cells.end()), long(c.size()), std::mt19937{m_engine()});

    std::vector<std::pair<size_t, uint8_t>> output;
    std::ranges::transform(chosen_cells, c, std::back_inserter(output), [](const auto cell_ind, const auto ball_no) { return std::make_pair(cell_ind, ball_no); });

    for (const auto& [cell_ind, ball_no] : output) {
      m_array[cell_ind] = ball_no;
    }

    return output;
  }

  constexpr uint8_t points_per_ball(const uint8_t colors_num) const {
    return (colors_num <= 5) ? uint8_t(1) : uint8_t(double((colors_num - 8) * colors_num + 23) / 8);
  }

 public:
  constexpr Board(const GameState& t_state) : m_array{filled_array<N * M>()}, m_drawn{filled_array<TDraws>()}, m_state{t_state}, m_points_per_ball{points_per_ball(m_state.colors)} {}

  void reset() {
    score = 0;
    m_array = filled_array<N * M>();
    m_drawn = filled_array<TDraws>();
    m_points_per_ball = points_per_ball(m_state.colors);
  }

  constexpr void print() const {
    std::cout << "\x1B[37mScore: " << score << "\n  ";
    for (size_t i = 0; i < N; i++) {
      std::cout << i << ' ';
    }
    std::cout << "\x1B[0m\n";
    size_t j = 0;
    for (size_t i = 0; i < m_array.size(); i++) {
      if (i % N == 0) std::cout << "\x1B[37m" << j++ << "\x1B[0m ";
      switch (m_array[i]) {
        case 0:
          std::cout << "\x1B[37m0\x1B[0m ";
          break;
        case 1:
          std::cout << "\x1B[35m1\x1B[0m ";
          break;
        case 2:
          std::cout << "\x1B[31m2\x1B[0m ";
          break;
        case 3:
          std::cout << "\x1B[34m3\x1B[0m ";
          break;
        case 4:
          std::cout << "\x1B[33m4\x1B[0m ";
          break;
        case 5:
          std::cout << "\x1B[32m5\x1B[0m ";
          break;
        default:
          std::cout << "\x1B[30m" << int(m_array[i]) << "\x1B[0m ";
          break;
      }

      if ((i % N) == (N - 1)) std::cout << '\n';
    }
  }

  constexpr uint8_t operator[](const Point<size_t> point) const {
    assert((point.x < N) && (point.y < M));
    return m_array[point.y * N + point.x];
  }

  constexpr size_t point_to_index(const Point<size_t> point) const {
    assert((point.x < N) && (point.y < M));
    return point.y * N + point.x;
  }

  std::map<size_t, uint8_t> point_to_index(const std::map<Point<size_t>, uint8_t>& input) const {
    std::map<size_t, uint8_t> output;
    std::ranges::for_each(input, [&](const auto& pair) { output.emplace(point_to_index(pair.first), pair.second); });
    return output;
  }

  constexpr Point<size_t> index_to_point(const size_t ind) const {
    assert(ind < N * M);
    return Point<size_t>(modquot(ind, N));
  }

  std::vector<std::pair<Point<size_t>, uint8_t>> index_to_point(const std::vector<std::pair<size_t, uint8_t>>& input) const {
    std::vector<std::pair<Point<size_t>, uint8_t>> output;
    for (const auto& ball : input) {
      output.emplace_back(index_to_point(ball.first), ball.second);
    }
    return output;
  }

  std::vector<Point<size_t>> index_to_point(const std::vector<std::set<size_t>>& input) const {
    std::vector<Point<size_t>> output;
    for (const auto& chain : input) {
      for (const auto& ind : chain) {
        output.push_back(index_to_point(ind));
      }
    }
    return output;
  }

  std::vector<std::pair<size_t, uint8_t>> init(const size_t balls_count) {
    draw_random(m_drawn);
    std::vector<uint8_t> init_drawn(balls_count, 0);
    draw_random(init_drawn);
    return place_random(init_drawn);
  }

  std::vector<Direction> get_path(const Point<size_t>& from, const Point<size_t>& to) const {
    assert((from.x < N) && (from.y < M));
    assert((to.x < N) && (to.y < M));
    const auto from_ind = point_to_index(from);
    const auto to_ind = point_to_index(to);
    if ((from_ind == to_ind) || (m_array[from_ind] == 0) || (m_array[to_ind] != 0)) return std::vector<Direction>{};

    auto mask = get_mask();
    mask[from_ind] = true;

    std::array<optional_max<size_t>, N * M> trace{};
    trace.fill({});

    std::deque<size_t> bfs_queue{from_ind};
    auto found = false;
    while (!bfs_queue.empty() && !found) {
      const auto next = bfs_queue.front();
      bfs_queue.pop_front();
      auto neighbors = get_neighbor_indicies(next);
      for (const auto neighbor : neighbors) {
        if (!mask[neighbor]) {
          bfs_queue.push_back(neighbor);
          mask[neighbor] = true;
          trace[neighbor] = next;
        }
        if (neighbor == to_ind) {
          found = true;
          break;
        }
      }
    }

    if (!found) return std::vector<Direction>{};

    auto node_curr = to_ind;
    std::vector<Direction> path;
    while (auto node_next = trace[node_curr]) {
      switch (long(node_next.value() - node_curr)) {
        case -long(N):
          path.push_back(Direction::down);
          break;
        case -1:
          path.push_back(Direction::right);
          break;
        case 1:
          path.push_back(Direction::left);
          break;
        case M:
          path.push_back(Direction::up);
          break;
        default:
          Logger::log("Error while backtracing the tree.", LoggerMode::error);
          return std::vector<Direction>{};
      }
      node_curr = node_next.value();
    }
    return path;
  }

  std::vector<std::pair<size_t, uint8_t>> move(const Point<size_t>& from, const Point<size_t>& to) {  // call get_path() before using it - if not empty then move
    const auto from_ind = point_to_index(from);
    const auto to_ind = point_to_index(to);
    m_array[to_ind] = m_array[from_ind];
    m_array[from_ind] = 0;
    return std::vector<std::pair<size_t, uint8_t>>{std::make_pair(to_ind, m_array[to_ind])};
  }

  constexpr std::vector<std::set<size_t>> find_matches(const std::map<size_t, uint8_t>& balls_new) const {
    constexpr std::array dir_pairs = {std::make_pair(Direction::left, Direction::right), std::make_pair(Direction::leftup, Direction::rightdown), std::make_pair(Direction::up, Direction::down), std::make_pair(Direction::rightup, Direction::leftdown)};

    // find possible chains
    std::vector<std::set<std::set<size_t>>> chains(size_t(m_state.colors), std::set<std::set<size_t>>());
    for (const auto& [ball_ind, ball_color] : balls_new) {
      assert(ball_color > 0);
      for (const auto& [dir1, dir2] : dir_pairs) {
        const auto chain = traverse_bi(ball_color, ball_ind, dir1, dir2);
        if (chain.size() >= TMinLineLen) chains[size_t(ball_color - 1)].insert(chain);
      }
    }

    // extract longest chains
    std::vector<std::set<size_t>> output;
    for (auto& chains_color : chains) {
      while (!chains_color.empty()) {
        const auto it_longest = std::max_element(chains_color.cbegin(), chains_color.cend(), [](const auto& s1, const auto& s2) { return s1.size() < s2.size(); });
        auto longest = chains_color.extract(it_longest).value();

        if (longest.size() >= TMinLineLen) {
          output.push_back(longest);

          std::set<std::set<size_t>> chains_color_split;
          split_set_if(chains_color.begin(), chains_color.end(), std::inserter(chains_color_split, chains_color_split.end()), longest.begin(), longest.end(), [](const auto& s) { return s.size() >= TMinLineLen; });

          chains_color = chains_color_split;
        }
      }
    }

    return output;
  }

  void cap_drawn(){
    size_t counter = 0;
    for (const auto& cell : m_array) {
      if (cell == 0) {
        ++counter;
        if(counter >= TDraws){
          return;
        }
      }
    }

    for(; counter < TDraws; counter++){
      m_drawn[counter] = 0;
    }
  }

  std::vector<std::pair<size_t, uint8_t>> add_random() {
    auto output = place_random(m_drawn);
    draw_random(m_drawn);
    cap_drawn();
    return output;
  }

  const std::array<uint8_t, TDraws> get_drawn() const {
    return m_drawn;
  }

  size_t get_score() const {
    return score;
  }

  bool is_full() const {
    for (const auto& cell : m_array) {
      if (cell == 0) {
        return false;
      }
    }
    return true;
  }

  size_t clear_matches(const std::vector<std::set<size_t>> matches) {
    for (const auto& chain : matches) {
      score += (m_state.hint) ? m_points_per_ball * chain.size() * 2 / 3 : m_points_per_ball * chain.size();
      for (const auto& ind : chain) {
        m_array[ind] = 0;
      }
    }
    return score;
  }
};

#endif