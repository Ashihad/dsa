#pragma once

#include "vector.hpp"

namespace custom
{

/***
 * see https://en.wikipedia.org/wiki/Linear_search
*/
template<typename T>
T* linear_search(T* begin, T* end, T value)
{
  for (T* iter = begin; iter != end; ++iter)
  {
    if (*iter == value) return iter;
  }
  return end;
}
template<typename T>
T* linear_search(custom::vector<T> vec, T value)
{
  return linear_search(vec.begin(), vec.end(), value);
}

/***
 * NOTE: Works only for sorted containers
 * see https://en.wikipedia.org/wiki/Binary_search_algorithm
*/
template<typename T>
int binary_search_impl(T* arr, std::size_t begin, std::size_t end, T value)
{
  if (end-begin > 1)
  {
    // create iterator pointing to middle element
    auto middle { begin + ((end-1)-begin)/2};
    // check if middle points to searched value
    if (value == arr[middle]) { return static_cast<int>(middle); }
    // if its lower than searched value check left subrange
    else if (value < arr[middle]) { return binary_search_impl(arr, begin, middle, value); }
    // if its higher than searched value check right subcontainer
    else if (value > arr[middle]) { return binary_search_impl(arr, middle+1, end, value); }
  }
  // check if we didnt end on searched one
  if (arr[begin] == value)
  {
      return static_cast<int>(begin);
  }
  // if loop fails value is not there
  return -1;
}
template<typename T>
T* binary_search(T* begin, T* end, T value)
{
  int ret{binary_search_impl(begin, 0, static_cast<std::size_t>(end-begin), value)};
  if (ret == -1) return end;
  return begin + ret;
}
template<typename T>
T* binary_search(custom::vector<T> vec, T value)
{
  return binary_search(vec.begin(), vec.end(), value);
}

// find maximum element
template<typename T>
T max(T* begin, T* end)
{
  T ret{std::numeric_limits<T>::min()};
  for (T* iter{begin}; iter != end; ++iter)
  {
    if (*iter > ret) ret = *iter;
  }
  return ret;
}

// find minimum element
template<typename T>
T min(T* begin, T* end)
{
  T ret{std::numeric_limits<T>::max()};
  for (T* iter{begin}; iter != end; ++iter)
  {
    if (*iter < ret) ret = *iter;
  }
  return ret;
}

}
