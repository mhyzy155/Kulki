#include <iostream>
#include <sstream>
#include <vector>

#include "asserts.hpp"
#include "deserializer.hpp"

// HELPER FUNCTIONS
void write_to_file_n(const std::string& path, const std::string& input, size_t n = 1) {
  std::ofstream stream{path};
  for (size_t i = 0; i < n; i++) {
    stream << input << ' ';
  }
}

template <class T>
auto deserialize(const std::string& path) {
  Deserializer deserializer{path};
  return deserializer.deserialize<T>();
}

template <class T>
auto deserialize_n(const std::string& path, size_t n = 1) {
  std::vector<T> vector_output{};
  Deserializer deserializer{path};
  for (size_t i = 0; i < n; i++) {
    vector_output.push_back(deserializer.deserialize<T>());
  }
  return vector_output;
}

// TESTS
void deserialize_int() {
  using Type = int;
  const auto path = "deserialize_int.txt";
  const Type input = 12345;

  write_to_file_n(path, std::to_string(input));

  auto output = deserialize<Type>(path);

  ASSERT_EQUAL(output, input);
}

void deserialize_ints() {
  using Type = int;
  const auto path = "deserialize_ints.txt";
  const Type input = 12345;
  size_t n = 10;

  write_to_file_n(path, std::to_string(input), n);

  auto vector_output = deserialize_n<Type>(path, n);
  auto vector_input = std::vector<Type>(n, input);

  ASSERT_EQUAL_VECTORS(vector_input, vector_output);
}

void deserialize_float() {
  using Type = float;
  const auto path = "deserialize_float.txt";
  const Type input = -123.456f;

  std::stringstream buf;
  buf << input;
  write_to_file_n(path, buf.str());

  auto output = deserialize<Type>(path);

  ASSERT_EQUAL(output, input);
}

void deserialize_string() {
  using Type = std::string;
  const auto path = "deserialize_string.txt";
  const Type input{"really nice string"};

  write_to_file_n(path, std::to_string(input.size()) + ' ' + input);

  auto output = deserialize<Type>(path);

  ASSERT_EQUAL_VECTORS(input, output);
}

void deserialize_strings() {
  using Type = std::string;
  const auto path = "deserialize_strings.txt";
  const Type input{"really nice string"};
  size_t n = 10;

  write_to_file_n(path, std::to_string(input.size()) + ' ' + input, n);

  auto vector_output = deserialize_n<Type>(path, n);
  auto vector_input = std::vector<Type>(n, input);

  ASSERT_EQUAL_VECTORS(vector_input, vector_output);
}

void deserialize_string_newline() {
  using Type = std::string;
  const auto path = "deserialize_string_newline.txt";
  const Type input{"really nice string\nbottom text"};

  write_to_file_n(path, std::to_string(input.size()) + ' ' + input);

  auto output = deserialize<Type>(path);

  ASSERT_EQUAL_VECTORS(input, output);
}

void deserialize_strings_newlines() {
  using Type = std::string;
  const auto path = "deserialize_strings_newlines.txt";
  const Type input{"really nice string\nbottom text"};
  size_t n = 10;

  write_to_file_n(path, std::to_string(input.size()) + ' ' + input, n);

  auto vector_output = deserialize_n<Type>(path, n);
  auto vector_input = std::vector<Type>(n, input);

  ASSERT_EQUAL_VECTORS(vector_input, vector_output);
}

void deserialize_pair_string_int() {
  using Type = std::pair<std::string, int>;
  const auto path = "deserialize_pair_string_int.txt";
  const Type input{"elo", 420};

  write_to_file_n(path, std::to_string(input.first.size()) + ' ' + input.first + std::to_string(input.second));

  auto output = deserialize<Type>(path);

  ASSERT_EQUAL_VECTORS(input.first, output.first);
  ASSERT_EQUAL(input.second, output.second);
}

int main() {
  deserialize_int();
  deserialize_ints();
  deserialize_float();
  deserialize_string();
  deserialize_strings();
  deserialize_string_newline();
  deserialize_strings_newlines();
  deserialize_pair_string_int();
  return 0;
}