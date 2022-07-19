#include <stdexcept>
#include <string>

#define STRING_HELPER(x) #x
#define STRING(x) STRING_HELPER(x)

template <typename T>
concept Container = requires(T t) {
  std::begin(t);
  std::end(t);
};

#define ASSERT_TRUE(condition)                                                                                                                                                                                                                            \
  {                                                                                                                                                                                                                                                       \
    if (!(condition)) {                                                                                                                                                                                                                                   \
      throw std::runtime_error(std::string("[ASSERT_BOOL] ") + std::string(STRING(condition)) + std::string(" is not true\n\t") + std::string(__FILE__) + std::string(":") + std::to_string(__LINE__) + std::string(" in ") + std::string(__FUNCTION__)); \
    }                                                                                                                                                                                                                                                     \
  }

#define ASSERT_FALSE(condition)                                                                                                                                                                                                                           \
  {                                                                                                                                                                                                                                                       \
    if ((condition)) {                                                                                                                                                                                                                                    \
      throw std::runtime_error(std::string("[ASSERT_BOOL] ") + std::string(STRING(condition)) + std::string(" is not true\n\t") + std::string(__FILE__) + std::string(":") + std::to_string(__LINE__) + std::string(" in ") + std::string(__FUNCTION__)); \
    }                                                                                                                                                                                                                                                     \
  }

#define ASSERT_EQUAL(x, y)                                                                                                                                                                                                                                                                   \
  {                                                                                                                                                                                                                                                                                          \
    if ((x) != (y)) {                                                                                                                                                                                                                                                                        \
      throw std::runtime_error(std::string("[ASSERT_EQUAL] lhs: ") + std::string(STRING(x)) + std::string(" rhs: ") + std::string(STRING(y)) + std::string("\n\t") + std::string(__FILE__) + std::string(":") + std::to_string(__LINE__) + std::string(" in ") + std::string(__FUNCTION__)); \
    }                                                                                                                                                                                                                                                                                        \
  }

#define ASSERT_EQUAL_AT(x, y, file, line, function)                                                                                                                                                                                                                              \
  {                                                                                                                                                                                                                                                                              \
    if ((x) != (y)) {                                                                                                                                                                                                                                                            \
      throw std::runtime_error(std::string("[ASSERT_EQUAL] lhs: ") + std::string(STRING(x)) + std::string(" rhs: ") + std::string(STRING(y)) + std::string("\n\t") + std::string(file) + std::string(":") + std::to_string(line) + std::string(" in ") + std::string(function)); \
    }                                                                                                                                                                                                                                                                            \
  }

#define ASSERT_NOT_EQUAL(x, y)                                                                                                                                                                                                                                                               \
  {                                                                                                                                                                                                                                                                                          \
    if ((x) == (y)) {                                                                                                                                                                                                                                                                        \
      throw std::runtime_error(std::string("[ASSERT_EQUAL] lhs: ") + std::string(STRING(x)) + std::string(" rhs: ") + std::string(STRING(y)) + std::string("\n\t") + std::string(__FILE__) + std::string(":") + std::to_string(__LINE__) + std::string(" in ") + std::string(__FUNCTION__)); \
    }                                                                                                                                                                                                                                                                                        \
  }

template <Container C>
void traverse_containers(const C& c1, const C& c2, const char* file, int line, const char* function) {
  ASSERT_EQUAL_AT(c1.size(), c2.size(), file, line, function);
  if constexpr (Container<typename C::value_type>) {
    for (size_t i = 0; i < c1.size(); i++) {
      traverse_containers(c1[i], c2[i], file, line, function);
    }
  } else {
    for (size_t i = 0; i < c1.size(); i++) {
      ASSERT_EQUAL_AT(c1[i], c2[i], file, line, function);
    }
  }
}

#define ASSERT_EQUAL_VECTORS(x, y)                                   \
  {                                                                  \
    traverse_containers((x), (y), __FILE__, __LINE__, __FUNCTION__); \
  }
