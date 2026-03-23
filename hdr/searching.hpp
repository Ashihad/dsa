#pragma once

#include "vector.hpp"
#include <optional>

namespace custom {

/***
 * see https://en.wikipedia.org/wiki/Linear_search
 */
template <typename T>
std::optional<T*> linear_search(T* begin, T* end, T value) {
  for (T* iter = begin; iter != end; ++iter) {
    if (*iter == value)
      return iter;
  }
  return std::nullopt;
}
template <typename T>
std::optional<T*> linear_search(custom::vector<T> vec, T value) {
  return linear_search(vec.begin(), vec.end(), value);
}

/***
 * NOTE: Works only for sorted containers
 * see https://en.wikipedia.org/wiki/Binary_search_algorithm
 */
#include <iostream>
template <typename T>
std::optional<T*> binary_search(T* begin, T* end, T value) {
  if (std::distance(end, begin) > 1) {
    // create iterator pointing to middle element
    auto middle{begin + ((end - 1) - begin) / 2};
    // check if middle points to searched value
    if (value == *middle) {
      std::cout << "ending in middle, *middle=" << *middle << "\n";
      return middle;
    }
    // if its lower than searched value check left subrange
    else if (value < *middle) {
      std::cout << "choosing left, *middle=" << *middle << "\n";
      return binary_search(begin, middle, value);
    }
    // if its higher than searched value check right subcontainer
    else if (value > *middle) {
      std::cout << "choosing right, *middle=" << *middle << "\n";
      return binary_search(middle + 1, end, value);
    }
  }
  else {
    std::cout << "exiting recursion\n";
  }
  // check if we didnt end on searched one
  // if (*begin == value) {
  //   std::cout << "ended at searched value, *begin=" << *begin << '\n';
  //   return begin;
  // }
  // if loop fails value is not there
  std::cout << "value not found\n";
  return std::nullopt;
}

using custom::vector;
template <typename T>
std::optional<T*> binary_search(custom::vector<T> vec, T value) {
  return binary_search(vec.begin(), vec.end(), value);
}

}  // namespace custom
