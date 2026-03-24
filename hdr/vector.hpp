#pragma once

#include <algorithm>
#include <cstdarg>
#include <cstdlib>
#include <cstring>
#include <initializer_list>
#include <iostream>
#include <utility>

#include "utils.hpp"

namespace custom {

template <typename T>
class vector {
 public:
  // constructors/destructor
  vector() : m_ptr{new T[1]{}}, m_size{}, m_capacity{1} {}

  vector(std::size_t size) : vector() { resize(size); }

  vector(std::size_t size, const T& fill_value) : vector(size) { std::fill(this->begin(), this->end(), fill_value); }

  vector(std::initializer_list<T> init) : vector(init.size()) { std::copy(init.begin(), init.end(), m_ptr); }

  vector(const vector& other) : m_ptr{new T[other.m_capacity]}, m_size{other.m_size}, m_capacity{other.m_capacity} {
    std::copy(other.begin(), other.end(), m_ptr);
  }

  vector& operator=(const vector& rhs) {
    vector tmp(rhs);
    swap(tmp);
    return *this;
  }

  vector(vector&& other) noexcept
      : m_ptr{std::exchange(other.m_ptr, nullptr)},
        m_size{std::exchange(other.m_size, 0)},
        m_capacity{std::exchange(other.m_capacity, 0)} {}

  vector& operator=(vector&& rhs) noexcept {
    move_from(rhs);
    return *this;
  }

  virtual ~vector() {
    delete[] m_ptr;
    m_ptr = nullptr;
  }

  // iterators
  T* begin() const { return m_ptr; }
  T* end() const { return m_ptr + m_size; }

  // getters
  std::size_t size() const { return m_size; }
  std::size_t capacity() const { return m_capacity; }
  std::size_t get() const { return m_ptr; }

  // reallocate m_ptr if vector runs out of memory
  void reserve(const std::size_t new_capacity) {
    if (new_capacity < m_size) {
      throw std::out_of_range("cannot reserve less memory than m_size");
    }
    T* new_ptr{new T[new_capacity]};
    if (m_ptr != nullptr)
      std::memcpy(new_ptr, m_ptr, m_size * sizeof(T));
    delete[] m_ptr;

    m_ptr = new_ptr;
    m_capacity = new_capacity;
  }

  // increase size of array, reallocate if necessary
  void resize(const std::size_t new_size) {
    if (new_size <= m_size) {
      m_size = new_size;
      return;
    }
    fit_new_size(new_size);
  }

  // bound-checking access
  const T& at(const std::size_t index) const {
    if (index >= m_size)
      throw std::out_of_range(format("out of bounds access, index = %zu, size = %zu", index, m_size));
    return m_ptr[index];
  }

  T& at(const std::size_t index) {
    // Scott Meyer const pattern
    return const_cast<T&>(std::as_const(*this).at(index));
  }

  // subscript operators, bound check is performed
  const T& operator[](std::size_t index) const { return at(index); }
  // Scott Meyer const pattern
  T& operator[](std::size_t index) { return const_cast<T&>(std::as_const(*this).at(index)); }

  // add element to the back of an array, reallocate if necessary
  void push_back(const T& value) {
    std::size_t new_size{m_size + 1};
    if (new_size >= m_capacity) {
      fit_new_size(new_size);
    }
    m_ptr[m_size - 1] = value;
  }

  // insert element at given index, shift all values at bigger indexes one index to the right
  void insert(std::size_t pos, const T& value) {
    if (pos > m_size)
      throw std::out_of_range(format("insert, pos=%d, m_size=%d", pos, m_size));
    else if (pos == m_size) {
      // edge case, treat it like end() iterator in std::vector
      push_back(value);
      return;
    } else {
			std::size_t new_size{m_size+1};
			fit_new_size(new_size);
      shift_right(pos, 1);
      m_ptr[pos] = value;
    }
  }

  void erase(const std::size_t pos) {
    if (pos >= m_size)
      throw std::out_of_range(format("erase, pos=%u, m_size=%u", pos, m_size));
    shift_left(pos, 1);
    m_size--;
  }

  T* find(const T& value) {
    for (auto iter = this->begin(); iter != this->end(); iter++) {
      if (*iter == value)
        return iter;
    }
    return this->end();
  }

 private:
  // copy-and-swap idiom, for strong exception safety
  void swap(vector& other) noexcept {
    std::swap(m_ptr, other.m_ptr);
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
  }

  // move-and-destroy idiom, for strong exception safety
  void move_from(vector& other) noexcept {
		delete[] m_ptr;
    m_ptr = std::exchange(other.m_ptr, nullptr);
    m_size = std::exchange(other.m_size, 0);
    m_capacity = std::exchange(other.m_capacity, 0);
  }

  // check if new size exceeds capacity, if so reallocate m_ptr,
  // new capacity is calculated by doubling old one until it fits
  void fit_new_size(std::size_t new_size) {
    if (m_capacity > new_size)
      return;
    std::size_t new_capacity{m_capacity};
    while (new_capacity < new_size) {
      new_capacity = 2 * new_capacity;
    }
    reserve(new_capacity);
    m_size = new_size;
  }

  // move all index starting from index "offset" indexes to the right
  void shift_right(const std::size_t index, const std::size_t offset) {
    // if index concerns value bigger than size, it's a clear misuse of API
    if (index > m_size - 1) {
      throw std::out_of_range(format("shift_right, index bigger than size, index=%u, m_size=%u", index, m_size));
    }
    if (index + offset > m_size - 1) {
      // need to reallocate first in this case
      fit_new_size(index + offset);
    }
    // shift values one by one
		// the +1 in `i` init and -1 in subscripts prevents unsigned int overflow
    for (std::size_t i = (m_size - 1) - offset + 1; i > index; i--) {
      m_ptr[i + offset - 1] = m_ptr[i - 1];
    }
    // fill created space with zeros, just to be nice
    std::memset(m_ptr + index, T{}, offset * sizeof(T));
  }

  // move all index starting from index "offset" indexes to the left
  void shift_left(const std::size_t index, const std::size_t offset) {
    // if index concerns value bigger than size, it's a clear misuse of API
    if (index > m_size - 1) {
      throw std::out_of_range("shift_left, index bigger than size");
    }
		// if (offset > index) {
			// throw std::out_of_range(format("shift_left, offset > index, offset=%u, index=%u", offset, index));
		// }
		// shift values one by one
    for (std::size_t i = index; i < m_size - offset; i++) {
      m_ptr[i] = m_ptr[i + offset];
    }
    // fill created space with zeros, just to be nice
    std::memset(m_ptr + m_size - offset, T{}, offset * sizeof(T));
  }

  T* m_ptr;
  std::size_t m_size;
  std::size_t m_capacity;
};

constexpr std::size_t VECTOR_ELEMS_PER_LINE{10};

template<typename T>
std::string toString(const custom::vector<T>& vec) {
  std::string out("[ ");
  for (std::size_t i{}; i < vec.size(); i++) {
    out.append(std::to_string(vec[i]));
    out.append(" ");
    if ((i + 1) % VECTOR_ELEMS_PER_LINE == 0 && i != vec.size() - 1)
      out.append("\n");
  }
  out.append("]");
  return out;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const custom::vector<T>& vec) {
  os << toString(vec);
  return os;
}

template <typename T>
void swap(custom::vector<T>& first, custom::vector<T>& second) noexcept {
  first.swap(second);
}

template <typename T>
T* begin(const custom::vector<T>& vec) {
  return vec.begin();
}

template <typename T>
T* end(const custom::vector<T>& vec) {
  return vec.end();
}

}  // namespace custom
