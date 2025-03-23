#pragma once

#include <string>
#include <cstdarg>

namespace custom
{
  template<typename T>
  class vector;

  std::string format(const char*, ...);
}

#include <vector>
#include <functional>
#include "vector.hpp"
namespace custom
{
  template<typename T>
  vector<T> get_random_vector(const std::size_t size)
  {
    vector<T> output(0);
    for (std::size_t i = 0; i < size; ++i) {
      output.push_back(static_cast<T>(std::rand()) % static_cast<T>((10*size)));
    }
    return output;
  }

  template<typename T>
  void find_and_replace(T* begin, T* end, T searched, T replaced)
  {
    for (auto iter = begin; iter != end; ++iter)
    {
      if (*iter == searched) *iter = replaced;
    }
  }
}

std::vector<int> get_random_vector(const int);
void print_vector(const std::vector<int>&);
void print_vector(const std::vector<int>::iterator, const std::vector<int>::iterator);
void b_and_a(std::function<void(std::vector<int>&)>);
