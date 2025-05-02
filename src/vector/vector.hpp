#pragma once

#include <iostream>
#include <cstdarg>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <initializer_list>
#include <limits>
#include <numeric>

#include "misc.hpp"

namespace custom
{
template<typename T>
class vector
{
static_assert(std::is_trivially_default_constructible_v<T>);
public:
  // constructors/destructor
  vector() : m_size{0}, m_capacity{1}, m_ptr{new T[1]} {}
  vector(std::size_t size)
  : m_size{size}, m_capacity{}, m_ptr{}
  {
    std::size_t new_capacity = recalculate_capacity();
    reserve(new_capacity);
  }
  vector(std::size_t size, const T& fill_value)
  : vector(size)
  {
    std::fill(this->begin(), this->end(), fill_value);
  }
  vector(std::initializer_list<T> init)
  : vector(init.size()) {
    std::copy(init.begin(), init.end(), m_ptr);
  }
  vector(const vector& other)
  : m_size{other.m_size}, m_capacity{other.m_capacity}, m_ptr{new T[other.m_capacity]}
  {
    std::copy(other.begin(), other.end(), m_ptr);
  }
  vector& operator=(const vector& rhs)
  {
    vector tmp(rhs);
    swap(tmp);
    return *this;
  }
  vector(vector&& other) noexcept
  : m_size{std::exchange(other.m_size, 0)},
    m_capacity{std::exchange(other.m_capacity, 0)},
    m_ptr{std::exchange(other.m_ptr, nullptr)}
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
  T* begin() const
  {
    return m_ptr;
  }
  T* end() const
  {
    return m_ptr + m_size;
  }

  // getters
  std::size_t size() const { return m_size; }
  std::size_t capacity() const { return m_capacity; }
  T* get() const { return m_ptr; }

  // reallocate m_ptr if vector runs out of memory
  void reserve(const std::size_t new_capacity)
  {
    if (new_capacity == m_capacity) return;
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
    m_capacity = recalculate_capacity();
    reserve(m_capacity);
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
  bool operator==(const vector<T>& other) const
  {
    if (m_size != other.m_size) return false;
    for (T* iter1{this->begin()}, *iter2{other.begin()}; iter1 != this->end(); ++iter1, ++iter2)
    {
      if (*iter1 != *iter2) return false;
    }
    return true;
  }

  // add element to the back of an array, reallocate if necessary
  void push_back(const T& value)
  {
    m_size++;
    if (m_size >= m_capacity)
    {
      std::size_t new_capacity = recalculate_capacity();
      reserve(new_capacity);
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
      shift_right(pos, 1);
      m_ptr[pos] = value;
    }
  }

  void erase(const std::size_t pos)
  {
    if (pos >= m_size) throw std::out_of_range(format("erase, pos=%d, m_size=%d", pos, m_size));
    shift_left(pos, 1);
    m_size--;
  }

  T* search(const T& value)
  {
    for (auto iter = this->begin(); iter != this->end(); ++iter)
    {
      if (*iter == value) return iter;
    }
    return this->end();
  }

  T max()
  {
    if (m_size == 0) throw std::out_of_range("max(), size is 0");
    T ret{m_ptr[0]};
    for (const auto& elem : *this)
    {
      if (elem > ret) ret = elem;
    }
    return ret;
  }

  T min()
  {
    if (m_size == 0) throw std::out_of_range("min(), size is 0");
    T ret{m_ptr[0]};
    for (const auto& elem : *this)
    {
      if (elem < ret) ret = elem;
    }
    return ret;
  }

  T sum()
  {
    if (m_size == 0) throw std::out_of_range("sum(), size is 0");
    return std::accumulate(begin(), end(), T{});
  }

  double avg()
  {
    if (m_size == 0) throw std::out_of_range("avg(), size is 0");
    return std::accumulate(begin(), end(), 0.)/static_cast<double>(m_size);
  }

  void reverse()
  {
    if (m_size == 0) throw std::out_of_range("reverse(), size is 0");
    for(std::size_t i{}; i < m_size/2; i++)
    {
      std::swap(m_ptr[i], m_ptr[m_size-i-1]);
    }
  }

  void shift_right(const std::size_t index = 0, const std::size_t offset = 1)
  {
    if (m_size == 0) throw std::out_of_range("shift_right(), size is 0");
    if (index > m_size-1) throw std::out_of_range(format("shift_right, index = %zu, size = %zu", index, m_size));
    if (index+offset > m_size-1) throw std::out_of_range(format("shift_right, index = %zu, offset = %zu, size = %zu", index, offset, m_size));
    for (std::size_t i = m_size-1; i >= index+offset; i--)
    {
      m_ptr[i] = m_ptr[i-offset];
    }
    for(std::size_t i{index}; i < index+offset; i++)
    {
      m_ptr[i] = 0;
    }
  }

  void shift_left(const std::size_t index = 0, const std::size_t offset = 1)
  {
    if (m_size == 0) throw std::out_of_range("shift_left(), size is 0");
    if (index > m_size-1) throw std::out_of_range(format("shift_left, index = %zu, size = %zu", index, m_size));
    if (m_size < offset) throw std::out_of_range(format("shift_left, offset = %zu, size = %zu", offset, m_size));
    for (std::size_t i = index; i <= m_size-offset; ++i)
    {
      m_ptr[i] = m_ptr[i+offset];
    }
    for(std::size_t i{m_size-1}; i > m_size-offset-1; i--)
    {
      m_ptr[i] = 0;
    }
  }

  void rotate_left()
  {
    T elem{m_ptr[0]};
    shift_left(0, 1);
    m_ptr[m_size-1] = elem;
  }

  void rotate_right()
  {
    T elem{m_ptr[m_size-1]};
    shift_right(0, 1);
    m_ptr[0] = elem;
  }

  bool is_sorted()
  {
    T last{m_ptr[0]};
    for (auto iter{begin()+1}; iter != end(); iter++)
    {
      if (last > *iter) return false;
      last = *iter;
    }
    return true;
  }

  void insert_sorted(const T& val)
  {
    for (std::size_t i{}; i < m_size; i++)
    {
      if (val < m_ptr[i])
      {
        insert(i, val);
        return;
      }
    }
    push_back(val);
  }

  void partition()
  {
    auto pred = [](T x)
    {
      return x > 0;
    };
    T* i{begin()};
    T* j{end()-1};
    while(i < j)
    {
      while(pred(*i)) i++;
      while(!pred(*j)) j--;
      if (i < j) std::swap(*i, *j);
    }
  }

private:
  // increase capacity if needes based on m_size, does not relocate anything
  std::size_t recalculate_capacity()
  {
    if (m_capacity >= m_size) return m_capacity;

    std::size_t new_capacity{m_capacity};
    if (new_capacity == 0) new_capacity = 1;
    while (new_capacity < m_size)
    {
      new_capacity = 2 * new_capacity;
    }
    return new_capacity;
  }

  std::size_t m_size;
  std::size_t m_capacity;
  T* m_ptr;
};

}

template<typename T>
std::ostream& operator<<(std::ostream& os, const custom::vector<T>& vec)
{
  os << "[ ";
  for(std::size_t i{}; i < vec.size(); ++i)
  {
    os << vec[i] << ' ';
    if ( (i+1) % 10 == 0  && i != vec.size()-1) os << '\n';
  }
  os << "]";
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
