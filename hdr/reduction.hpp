#pragma once

#include <stdexcept>

namespace custom {

template<typename T>
T* max(T* begin, T* end) {
  if (end - begin == 0) {
    throw std::out_of_range("custom::max, vector empty");
  }
  T* max_pos = begin;
  for(auto iter = begin+1; iter != end; iter++) {
    if (*iter > *max_pos) {
      max_pos = iter;
    }
  }
  return max_pos;
}

template<typename T>
T* min(T* begin, T* end) {
  if (end - begin == 0) {
    throw std::out_of_range("custom::max, vector empty");
  }
  T* min_pos = begin;
  for(auto iter = begin+1; iter != end; iter++) {
    if (*iter < *min_pos) {
      min_pos = iter;
    }
  }
  return min_pos;
}

template<typename T>
double avg(T* begin, T* end) {
  if (end - begin == 0) {
    throw std::out_of_range("custom::max, vector empty");
  }
  double sum{};
  std::size_t elem_no{};
  for(auto iter = begin; iter != end; iter++) {
    elem_no++;
    sum += *iter;
  }
  return sum/static_cast<double>(elem_no);
}

} // namespace custom
