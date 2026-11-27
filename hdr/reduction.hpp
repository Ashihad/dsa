#pragma once

#include <stdexcept>

namespace custom {

template<typename T>
inline T* max(T* begin, T* end) {
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
inline T* min(T* begin, T* end) {
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
inline double avg(T* begin, T* end) {
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

template<typename T>
inline bool is_sorted(T* begin, T* end) {
  if (std::distance(begin, end) == 0 || std::distance(begin, end) == 1) return true;
  T prev_elem{*begin};
  for (auto iter{begin+1}; iter != end; iter++) {
    if (*iter < prev_elem) return false;
    prev_elem = *iter;
  }
  return true;
}

} // namespace custom
