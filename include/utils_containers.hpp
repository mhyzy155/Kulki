#ifndef KULKI_UTILS_CONTAINERS_HPP
#define KULKI_UTILS_CONTAINERS_HPP

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <utility>

namespace {

template <size_t S, class T, class Op, size_t... I>
constexpr std::array<T, S> array_incr(Op&& op, std::index_sequence<I...>) {
  return {{op(I)...}};
}

template <class T, std::size_t N, std::size_t... I>
constexpr std::array<std::remove_volatile_t<T>, N>
to_array_const_impl(T (&a)[N], std::index_sequence<I...>) {
  return {{a[I]...}};
}

}  // namespace

template <size_t S, class T = uint8_t>
constexpr auto filled_array(const T value = T(0)) {
  std::array<T, S> a{};
  a.fill(value);
  return a;
}

template <size_t S, class Op>
constexpr auto filled_array_incr(Op&& op) {
  return array_incr<S, std::invoke_result_t<Op, size_t>>(std::forward<Op>(op), std::make_index_sequence<S>{});
}

template <size_t S, class Op>
constexpr auto generated_array(const Op&& fun) {
  std::array<decltype(fun()), S> a{};
  std::generate(a.begin(), a.end(), fun);
  return a;
}

template <class T, class... Args>
constexpr auto make_array(Args&&... args) {
  return std::array<T, sizeof...(args)>{{std::forward<Args>(args)...}};
}

template <class T, std::size_t N>
constexpr std::array<std::remove_volatile_t<T>, N> to_array_const(T (&a)[N]) {
  return to_array_const_impl(a, std::make_index_sequence<N>{});
}

#endif