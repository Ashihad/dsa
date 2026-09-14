#pragma once

#include "vector.hpp"

namespace custom {
/***
 * helper method for merge sort
 */
template<typename T>
void merge_sorted(T* begin, T* middle, T* end) {
  // create two vectors, copy half of input vector to the left one, copy the
  // rest to the right one
  vector<int> left(static_cast<std::size_t>(middle - begin));
  vector<int> right(static_cast<std::size_t>(end - middle));
  std::copy(begin, middle, left.begin());
  std::copy(middle, end, right.begin());

  // iterate over input, left and right, if left has lower or equal to item
  // insert it to input and increment iterator, if not do the same to the right
  // one
  auto* left_iter{left.begin()};
  auto* right_iter{right.begin()};
  for (auto iter = begin; iter != end; ++iter) {
    if (right_iter == right.end() ||
        (left_iter != left.end() && *left_iter <= *right_iter)) {
      *iter = *left_iter;
      ++left_iter;
    } else {
      *iter = *right_iter;
      ++right_iter;
    }
  }
}

template<typename T>
void reverse(T* begin, T* end) {
  if (std::distance(begin, end) == 0) return;
  T* middle{begin + ((end - begin + 1) / 2)};
  for (T *f_iter{begin}, *b_iter{end - 1}; f_iter != middle;
       f_iter++, b_iter--) {
    std::swap(*f_iter, *b_iter);
  }
}

}  // namespace custom
