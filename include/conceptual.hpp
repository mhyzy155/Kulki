#ifndef KULKI_CONCEPTUAL_HPP
#define KULKI_CONCEPTUAL_HPP

template <class P>
concept Pair = requires(P p) {
  p.first;
  p.second;
};

template <class M>
concept Map = Pair<typename M::value_type>;

#endif