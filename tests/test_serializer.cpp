#include <sstream>
#include <string>

#include "serializer.hpp"
#include "asserts.hpp"

using namespace std::string_literals;

auto string_n(const std::string& str, size_t n){
  std::string output{""};
  for (size_t i = 0; i < n; i++) {
    output += str;
  }
  return output;
}

void serialize_n(const auto& path, const auto& obj, size_t n = 1) {
  Serializer serializer(path);
  //const auto s = Serializable(obj);
  for (size_t i = 0; i < n; i++) {
    //serializer.serialize(s);
    serializer.serialize(obj);
  }
}

auto get_file_content(const auto& path){
  std::ifstream file(path);
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

void serializer_override() {
  const auto path = "serializer_override.txt";
  serialize_n(path, 10);

  Serializer serializer(path);
  
  ASSERT_EQUAL(get_file_content(path), "");
}

void serialize_ints() {
  const auto path = "serialize_ints.txt";
  const int input = 12345;
  const size_t n = 10;
  serialize_n(path, input, n);
  const auto str_expected = string_n(std::to_string(input) + DELIMETER, n);

  ASSERT_EQUAL(get_file_content(path), str_expected);
}

void serialize_floats() {
  const auto path = "serialize_floats.txt";
  const float input = -123.456f;
  const size_t n = 10;
  serialize_n(path, input, n);
  std::stringstream buf;
  buf << input;
  const auto str_expected = string_n(buf.str() + DELIMETER, n);
  
  ASSERT_EQUAL(get_file_content(path), str_expected);
}

void serialize_pair_string_int() {
  const auto path = "serialize_pair_string_int.txt";
  serialize_n(path, std::make_pair<std::string, int>("elo", 420));
  const auto str_expected = "3"s + DELIMETER + "elo"s + DELIMETER + "420"s + DELIMETER;

  ASSERT_EQUAL(get_file_content(path), str_expected);
}

void serialize_pairs_string_int() {
  const auto path = "serialize_pairs_string_int.txt";
  const size_t n = 3;
  serialize_n(path, std::make_pair<std::string, int>("elo", 420), n);
  const auto str_expected = string_n("3"s + DELIMETER + "elo"s + DELIMETER + "420"s + DELIMETER, n);

  ASSERT_EQUAL(get_file_content(path), str_expected);
}

int main() {
  serializer_override();
  serialize_ints();
  serialize_floats();
  serialize_pair_string_int();
  serialize_pairs_string_int();
  return 0;
}