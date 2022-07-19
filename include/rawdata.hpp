#ifndef KULKI_RAWDATA_HPP
#define KULKI_RAWDATA_HPP

#include <array>
#include <utility>
#include <string_view>

#include "ref.hpp"
#include "utils_containers.hpp"

struct RawDataInterface {
  virtual constexpr const char* data() const = 0;
  virtual constexpr size_t size() const = 0;
  virtual constexpr const char* type() const = 0;
};

using RawDataInterfaceR = Ref<const RawDataInterface>;

template <size_t N>
class RawData : public RawDataInterface {
  const std::string_view m_type;
  const std::array<const char, N> m_data;

 public:
  constexpr RawData(const std::string_view t_type, std::array<const char, N>&& t_data) : m_type{t_type}, m_data{std::move(t_data)} {}

  constexpr const char* data() const override {
    return m_data.data();
  }

  constexpr size_t size() const override {
    return m_data.size();
  }

  constexpr const char* type() const override {
    return m_type.data();
  }
};

template <size_t M>
RawData(const char*, std::array<const char, M>&&) -> RawData<M>;

#endif