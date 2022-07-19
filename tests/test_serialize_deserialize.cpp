#include <string>
#include <utility>

#include "asserts.hpp"
#include "deserializer.hpp"
#include "serializer.hpp"

void serialize_n(const auto& path, const auto& obj, size_t n = 1) {
  Serializer serializer(path);
  for (size_t i = 0; i < n; i++) {
    serializer.serialize(obj);
  }
}

void serialize_deserialize_u16string() {
  using Type = std::u16string;
  const auto path = "serialize_deserialize_u16string.txt";
  const Type input = u"aąbcćdeęfghijklłmnńoópqrsśtuvwxyzżź";

  Serializer serializer(path);
  const auto s = Serializable(input);
  serializer.serialize(s);

  Deserializer deserializer(path);
  const auto output = deserializer.deserialize<Type>();

  ASSERT_EQUAL_VECTORS(input, output);
}

void serialize_deserialize_pair_u16string_int() {
  using Type = std::pair<std::u16string, int>;

  const auto path = "serialize_deserialize_pair_u16string_int.txt";
  const Type input{u"aąbcćdeęfghijklłmnńoópqrsśtuvwxyzżź", 123456};

  serialize_n(path, input);

  Deserializer deserializer(path);
  const auto output = deserializer.deserialize<Type>();

  ASSERT_EQUAL_VECTORS(input.first, output.first);
  ASSERT_EQUAL(input.second, output.second);
}

int main() {
  serialize_deserialize_u16string();
  serialize_deserialize_pair_u16string_int();
  return 0;
}