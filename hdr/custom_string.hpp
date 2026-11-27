#pragma once

#include <algorithm>
#include <cstdlib>
#include <utility>

namespace custom {

template<typename T>
class string {
public:
  string() : m_data{new char[1]}, m_capacity{1}, m_size{1} {}

  ~string() {
    m_data = nullptr;
    delete[] m_data;
  }

  string(const string& other) :
      m_data{new char[other.m_capacity]},
  m_capacity{other.m_capacity},
      m_size{other.m_size} {
    std::copy(other.begin(), other.end(), m_data);
  }

  string& operator=(const string& rhs) {
    string tmp(rhs);
    swap(tmp);
    return *this;
  }

  string(string&& other) noexcept :
      m_data{std::exchange(other.m_data, nullptr)},
      m_capacity{std::exchange(other.m_capacity, 0)},
      m_size{std::exchange(other.m_size, 0)} {}

  string& operator=(string&& rhs) noexcept {
    move_from(rhs);
    return *this;
  }

  char* begin() const {
    return m_data;
  }

  char* end() const {
    return m_data+m_size;
  }

private:
  char* m_data;
  std::size_t m_capacity;
  std::size_t m_size;
};

}  // namespace custom
