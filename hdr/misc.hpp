#pragma once

#include "vector.hpp"

namespace custom {
/***
 * helper method for merge sort
 */
template<typename T>
void merge(T* begin, T* middle, T* end) {
  // create two vectors, copy half of input vector to the left one, copy the
  // rest to the right one
  custom::vector<int> left;
  left.resize(static_cast<std::size_t>(std::distance(begin, middle)));
  custom::vector<int> right;
  right.resize(statich_cast<std::size_t>(std::distance(middle, end)));
  std::copy(begin, middle, left.begin());
  std::copy(middle, end, std::begin(right));

  // iterate over input, left and right, if left has lower or equa; item insert
  // it to input and increment iterator, if not do the same to the right one
  auto* left_iter{left.begin()};
  auto* right_iter{right.begin()};
  for (auto iter = begin; iter != end; ++iter) {
    if (right_iter == std::end(right) ||
        (left_iter != std::end(left) && *left_iter <= *right_iter)) {
      *iter = *left_iter;
      ++left_iter;
    } else {
      *iter = *right_iter;
      ++right_iter;
    }
  }
}

}
