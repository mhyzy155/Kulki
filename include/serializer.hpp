#ifndef KULKI_SERIALIZER_HPP
#define KULKI_SERIALIZER_HPP

#include <codecvt>
#include <concepts>
#include <filesystem>
#include <fstream>
#include <locale>
#include <stdexcept>
#include <string>
#include <utility>
#include <type_traits>

#include "conceptual.hpp"
#include "logger.hpp"

#if defined(_WIN32) || defined(WIN32)
#define FUN_INFO __FUNCSIG__
#else
#define FUN_INFO __PRETTY_FUNCTION__
#endif

static constexpr auto DELIMETER = ' ';

using OStream = std::ofstream;

struct SerializableInterface {
  virtual inline void serialize(OStream&) const = 0;
  virtual ~SerializableInterface() = default;
};

// template <class T>
// class Deserializable;

template <class T>
class SerializableBase : public SerializableInterface {
 protected:
  const T& m_data;

 public:
  explicit SerializableBase(const T& t_data) : m_data{t_data} {};
  // explicit SerializableBase(const Deserializable<T>& d) : m_data{d.to_serializable().m_data} {};
  virtual inline void serialize(OStream&) const override {
    throw std::runtime_error("Serialization not implemented for SerializableBase.");
  }
};

template <class T>
class Serializable : public SerializableBase<T> {
 public:
  using SerializableBase<T>::SerializableBase;
  inline void serialize(OStream&) const override {
    throw std::runtime_error(std::string{"Serialization not implemented for "} + FUN_INFO);
  }
};

template <class T>
Serializable(const T&) -> Serializable<T>;

class Serializer {
  const std::filesystem::path m_path;

 public:
  Serializer(const std::filesystem::path& t_path) : m_path{t_path} {
    OStream stream{m_path};
  };

  template <class T>
  void serialize(const Serializable<T>& serializable) const {
    OStream stream{m_path, std::ios::app};
    serializable.serialize(stream);
  }

  template <class T> requires (!std::is_base_of_v<SerializableInterface, T>)
  void serialize(const T& value) const {
    serialize(Serializable<T>(value));
  }
};

template <class T>
requires std::integral<T> || std::floating_point<T>
class Serializable<T> : public SerializableBase<T> {
 public:
  using SerializableBase<T>::SerializableBase;
  inline void serialize(OStream& stream) const override {
    Logger::log("S number");
    stream << this->m_data << DELIMETER;
  }
};


template <Pair T>
class Serializable<T> : public SerializableBase<T> {
 public:
  using SerializableBase<T>::SerializableBase;
  inline void serialize(OStream& stream) const override {
    Logger::log("S pair");
    Serializable<decltype(this->m_data.first)>(this->m_data.first).serialize(stream);
    Serializable<decltype(this->m_data.second)>(this->m_data.second).serialize(stream);
  }
};

template <Map T>
class Serializable<T> : public SerializableBase<T> {
 public:
  using SerializableBase<T>::SerializableBase;
  inline void serialize(OStream& stream) const override {
    Logger::log("S map");
    Serializable<size_t>(this->m_data.size()).serialize(stream);
    for(const auto& pair : this->m_data){
      Serializable<typename T::value_type>(pair).serialize(stream);
    }
  }
};

/*
template <>
inline void Serializable<int>::serialize(OStream& stream) const {
  Logger::log("S int");
  stream << m_data << DELIMETER;
}
*/

template <>
inline void Serializable<std::string>::serialize(OStream& stream) const {
  Logger::log("S string");
  stream << m_data.size() << DELIMETER << m_data << DELIMETER;
}

template <>
inline void Serializable<std::u16string>::serialize(OStream& stream) const {
  Logger::log("S u16string");
  Serializable<std::string>(std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t>().to_bytes(m_data)).serialize(stream);
}

#endif