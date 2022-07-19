#ifndef KULKI_DESERIALIZER_HPP
#define KULKI_DESERIALIZER_HPP

#include <codecvt>
#include <filesystem>
#include <fstream>
#include <locale>
#include <stdexcept>
#include <string>
#include <vector>
#include <type_traits>

#include "conceptual.hpp"
#include "logger.hpp"

#if defined(_WIN32) || defined(WIN32)
#define FUN_INFO __FUNCSIG__
#else
#define FUN_INFO __PRETTY_FUNCTION__
#endif

using IStream = std::ifstream;

/*
template<class T>
struct DeserializableInterface {
  virtual T deserialize(IStream&) = 0;
  virtual ~DeserializableInterface() = default;
};
*/

template <class T>
struct Deserializable;

class Deserializer {
  const std::filesystem::path m_path;

 public:
  Deserializer(const std::filesystem::path& t_path) : m_path{t_path} {};

  template <class T>
  T deserialize() const {
    IStream stream{m_path};
    return Deserializable<T>().deserialize(stream);
  }
};

template <class T>
struct Deserializable {
  inline T deserialize(IStream&) const {
    throw std::runtime_error(std::string{"Serialization not implemented for "} + FUN_INFO);
  }
};

template <>
inline std::string Deserializable<std::string>::deserialize(IStream& stream) const {
  Logger::log("D string");
  size_t length;
  stream >> length;

  std::string data;
  if (stream && length) {
    stream.ignore();
    std::vector<char> tmp(length);
    stream.read(tmp.data(), int(length));
    data.assign(tmp.data(), length);
  }

  return data;
}

template <>
inline std::u16string Deserializable<std::u16string>::deserialize(IStream& stream) const {
  Logger::log("D u16string");
  return std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t>().from_bytes(Deserializable<std::string>().deserialize(stream));
}

template <class T>
requires std::integral<T> || std::floating_point<T>
struct Deserializable<T> {
  inline T deserialize(IStream& stream) const {
    Logger::log("D number");
    T data{};
    stream >> data;
    return data;
  }
};

template <Pair T>
struct Deserializable<T> {
  inline T deserialize(IStream& stream) const {
    Logger::log("D pair");
    auto first = Deserializable<typename T::first_type>().deserialize(stream);
    return T{std::move(first), Deserializable<typename T::second_type>().deserialize(stream)};
  }
};

template <Map T>
struct Deserializable<T> {
  inline T deserialize(IStream& stream) const {
    Logger::log("D map");
    auto size = Deserializable<typename T::size_type>().deserialize(stream);
    T data{};
    for (size_t i = 0; i < size; i++) {
      data.insert(Deserializable<std::pair<typename T::key_type, typename T::mapped_type>>().deserialize(stream));
    }
    return data;
  }
};

/*
template <>
int Deserializable<int>::deserialize(IStream& stream) const {
  Logger::log("D int");
  int data;
  stream >> data;
  return data;
}
*/

/*
static constexpr auto DELIMETER = ' ';

struct DeserializableInterface {
  virtual void deserialize(IStream&) = 0;
  virtual ~DeserializableInterface() = default;
};

class Deserializer {
  const std::filesystem::path m_path;

 public:
  Deserializer(const std::filesystem::path& t_path) : m_path{t_path} {};

  void deserialize(DeserializableInterface& deserializable) {
    IStream stream{m_path};
    deserializable.deserialize(stream);
  }
};

template <class T>
class Deserializable : DeserializableInterface {
  T& m_data;

 public:
  Deserializable(T& t_data) : m_data{t_data} {};
  auto to_serializable() const {
    return Serializable<T>(m_data);
  }
  void deserialize(IStream&) override {
    throw std::runtime_error("Deserialization not implemented for this type.");
  }
};

template<>
void Deserializable<int>::deserialize(IStream& stream) {
  char delimeter;
  stream >> m_data >> delimeter;
  if(delimeter != DELIMETER){
    throw std::runtime_error("Wrong delimeter in Deserializable<int>");
  }
}
*/

#endif