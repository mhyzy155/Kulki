#ifndef KULKI_MACROS_HPP
#define KULKI_MACROS_HPP

#if defined(_WIN32) || defined(WIN32)
#define EXTENSION(x) x
#else
#define EXTENSION __extension__
#endif

// used with smart pointers, execute method if not nullptr
#define CHECK_THEN(ptr, fn) \
  EXTENSION({               \
    if (ptr) {              \
      ptr->fn;              \
    }                       \
  })

// used with smart pointers, execute method if not nullptr
template <class SPtr, class Op, class... Args>
void check_then(SPtr&& ptr, Op&& oper, Args... args) {
  if (ptr) {
    (*ptr.*oper)(args...);
  }
}

#endif