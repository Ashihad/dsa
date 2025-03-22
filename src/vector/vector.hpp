#pragma once

#include <iostream>
#include <cstdarg>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <initializer_list>

#include "misc.hpp"

namespace custom
{

template<typename T>
class vector
{
public:
  // constructors/destructor
  vector() : m_ptr{new T[1]}, m_size{}, m_capacity{1} {}
  vector(std::size_t size)
  : m_ptr{new T[size]}, m_size{size}, m_capacity{1}
  {
    fit_capacity();
  }
  vector(std::size_t size, const T& fill_value)
  : m_ptr{new T[size]}, m_size{size}, m_capacity{1}
  {
    fit_capacity();
    std::fill(this->begin(), this->end(), fill_value);
  }
  vector(std::initializer_list<T> init)
  : m_ptr{}, m_size(init.size()), m_capacity{1} {
    fit_capacity();
    std::copy(init.begin(), init.end(), m_ptr);
  }
  vector(const vector& other)
  : m_ptr{new T[other.m_capacity]}, m_size{other.m_size}, m_capacity{other.m_capacity}
  {
    std::memcpy(m_ptr, other.m_ptr, m_size*sizeof(T));
  }
  vector& operator=(const vector& rhs)
  {
    vector tmp(rhs);
    swap(tmp);
    return *this;
  }
  vector(vector&& other) noexcept
  : m_ptr{std::exchange(other.m_ptr, nullptr)},
    m_size{std::exchange(other.m_size, 0)},
    m_capacity{std::exchange(other.m_capacity, 0)}
  {}
  vector& operator=(vector&& rhs) noexcept
  {
    move_from(rhs);
    return *this;
  }
  virtual ~vector()
  {
    delete[] m_ptr;
    m_ptr = nullptr;
  }

  // copy-and-swap idiom, for strong exception safety
  void swap(vector& other) noexcept
  {
    std::swap(m_ptr, other.m_ptr);
    std::swap(m_size, other.m_size);
    std::swap(m_capacity, other.m_capacity);
  }
  // move-and-destroy idiom, for strong exception safety
  void move_from(vector& other) noexcept
  {
    m_ptr = std::exchange(other.m_ptr, nullptr);
    m_size = std::exchange(other.m_size, 0);
    m_capacity = std::exchange(other.m_capacity, 0);
  }

  // iterators
  T* begin()
  {
    return m_ptr;
  }
  T* end()
  {
    return m_ptr + m_size;
  }

  // getters
  std::size_t size() const { return m_size; }
  std::size_t capacity() const { return m_capacity; }
  std::size_t get() const { return m_ptr; }

  // reallocate m_ptr if vector runs out of memory
  void reserve(const std::size_t new_capacity)
  {
    T* new_ptr{new T[new_capacity]};
    if (m_ptr != nullptr)
      std::memcpy(new_ptr, m_ptr, m_size*sizeof(T));
    delete[] m_ptr;

    m_ptr = new_ptr;
    m_capacity = new_capacity;
  }

  // increase size of array, reallocate if necessary
  void resize(const std::size_t new_size)
  {
    if (new_size <= m_size)
    {
      m_size = new_size;
      return;
    }
    m_size = new_size;
    fit_capacity();
  }

  // bound-checking access
  T& at(const std::size_t index)
  {
    // Scott Meyer const pattern
    return const_cast<T&>(std::as_const(*this).at(index));
  }
  const T& at(const std::size_t index) const
  {
    if (index >= m_size) throw std::out_of_range(format("out of bounds access, index = %zu, size = %zu", index, m_size));
    return m_ptr[index];
  }

  // fill vector with 0..m_size-1
  void iota()
  {
    for(std::size_t i{}; i < m_size; ++i)
    {
      m_ptr[i] = static_cast<T>(i);
    }
  }

  // subscript operators, bound check is performed
  const T& operator[] (std::size_t index) const
  {
    return at(index);
  }
  T& operator[] (std::size_t index)
  {
    // Scott Meyer const pattern
    return const_cast<T&>(std::as_const(*this).at(index));
  }

  // add element to the back of an array, reallocate if necessary
  void push_back(const T& value)
  {
    m_size++;
    if (m_size >= m_capacity)
    {
      fit_capacity();
    }
    m_ptr[m_size-1] = value;
  }

  // insert element at given index, shift all values at bigger indexes one index to the right
  void insert(std::size_t pos, const T& value)
  {
    if (pos > m_size) throw std::out_of_range(format("insert, pos=%d, m_size=%d", pos, m_size));
    else if (pos == m_size)
    {
      // edge case, treat it like end() iterator in std::vector
      push_back(value);
      return;
    }
    else
    {
      m_size++;
      shift_elements_right(pos, 1);
      m_ptr[pos] = value;
    }
  }

  void erase(const std::size_t pos)
  {
    if (pos >= m_size) throw std::out_of_range(format("erase, pos=%d, m_size=%d", pos, m_size));
    m_size--;
    shift_elements_left(pos, 1);
  }
  T* search(const T& value)
  {
    for (auto iter = this->begin(); iter != this->end(); ++iter)
    {
      if (*iter == value) return iter;
    }
    return this->end();
  }
private:
  // check if size exceeds capacity, if so reallocate m_ptr
  void fit_capacity()
  {
    if (m_capacity >= m_size) return;

    std::size_t new_capacity{m_capacity};
    while (new_capacity < m_size)
    {
      new_capacity = 2 * new_capacity;
    }
    reserve(new_capacity);
  }

  // move all index starting from index "offset" indexes to the right
  void shift_elements_right(const std::size_t index, const std::size_t offset)
  {
    for (std::size_t i = (m_size-1)-offset; i >= index; --i)
    {
      m_ptr[i+offset] = m_ptr[i];
    }
  }

  // move all index starting from index "offset" indexes to the left
  void shift_elements_left(const std::size_t index, const std::size_t offset)
  {
    for (std::size_t i = index; i <= m_size-offset; ++i)
    {
      m_ptr[index] = m_ptr[i+offset];
    }
  }

  T* m_ptr;
  std::size_t m_size;
  std::size_t m_capacity;
};

}

template<typename T>
std::ostream& operator<<(std::ostream& os, const custom::vector<T>& vec)
{
  for(std::size_t i{}; i < vec.length(); ++i)
  {
    os << vec[i] << ' ';
  }
  return os;
}

template<typename T>
void swap(custom::vector<T>& first, custom::vector<T>& second) noexcept
{
  first.swap(second);
}

template<typename T>
T* begin(const custom::vector<T>& vec)
{
  return vec.begin();
}

template<typename T>
T* end(const custom::vector<T>& vec)
{
  return vec.end();
}
