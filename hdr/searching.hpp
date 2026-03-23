#pragma once

#include <optional>

#include "vector.hpp"

namespace custom {

/***
 * see https://en.wikipedia.org/wiki/Linear_search
 */
template<typename T>
std::optional<T*> linear_search(T* begin, T* end, T value) {
  // if (std::distance(begin, end) == 0) {
  //   // vector empty
  //   return std::nullopt;
  // }
  for (T* iter = begin; iter != end; ++iter) {
    if (*iter == value) return iter;
  }
  return std::nullopt;
}
template<typename T>
std::optional<T*> linear_search(custom::vector<T> vec, T value) {
  return linear_search(vec.begin(), vec.end(), value);
}

/***
 * NOTE: Works only for sorted containers
 * see https://en.wikipedia.org/wiki/Binary_search_algorithm
 */
template<typename T>
std::optional<T*> binary_search(T* begin, T* end, T value) {
  if (std::distance(begin, end) == 0) {
    return std::nullopt;  // vector empty
  }
  // create iterator pointing to middle element
  auto middle_distance{(end - 1 - begin) / 2};
  auto middle{begin + middle_distance};
  // check if middle points to searched value
  if (value == *middle) {
    return middle;
  }
  // if its lower than searched value check left subrange
  else if (value < *middle) {
    return binary_search(begin, middle, value);
  }
  // if its higher than searched value check right subcontainer
  else if (value > *middle) {
    return binary_search(middle + 1, end, value);
  }
  // check if we didnt end on searched one
  if (*begin == value) {
    return begin;
  }
  // if loop fails value is not there
  return std::nullopt;
}

using custom::vector;
template<typename T>
std::optional<T*> binary_search(custom::vector<T> vec, T value) {
  return binary_search(vec.begin(), vec.end(), value);
}

}  // namespace custom
