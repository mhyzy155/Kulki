#ifndef KULKI_ALGORITHM_HPP
#define KULKI_ALGORITHM_HPP

template <class ForwardIt1, class OutputIt, class ForwardIt2, class UnaryPredicate>
constexpr void split_set_if(ForwardIt1 first, ForwardIt1 last, OutputIt d_first, const ForwardIt2 comp_first, const ForwardIt2 comp_last, UnaryPredicate p) {
  using T = ForwardIt1::value_type;
  for (; first != last; first++) {
    const auto set_last = first->cend();
    auto subset_first = first->begin();
    auto comp_it = comp_first;
    for (auto subset_last = subset_first; subset_last != set_last; subset_last++) {
      while ((*subset_last > *comp_it) && (comp_it != comp_last)) {
        ++comp_it;
      }

      if (*subset_last == *comp_it) {
        T subset = T(subset_first, subset_last);
        if (p(subset)) {
          *d_first++ = subset;
        }
        subset_first = subset_last;
        ++subset_first;
      }
    }
    if (subset_first != set_last) {
      T subset = T(subset_first, set_last);
      if (p(subset)) {
        *d_first++ = subset;
      }
    }
  }
}

#endif