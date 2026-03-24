#pragma once

#include <algorithm>
#include <vector>

/***
 * see https://en.wikipedia.org/wiki/Insertion_sort
 */
template<typename T>
void insertion_sort(T* begin, T* end) {
  if (std::distance(begin, end) < 2) {
    // can't sort empty nor one-elem vector
    return;
  }
  // for each element starting from 2nd
  for(auto iter = begin + 1; iter != end; iter++) {
    // iterate backwards, and swap concurrent elements if they are in bad order
    for(auto r_iter = iter; r_iter != begin; r_iter--) {
      if (*(r_iter - 1) > *r_iter) {
        std::swap(*(r_iter-1), *(r_iter));
      }
    }
  }
}

/***
 * see https://en.wikipedia.org/wiki/Selection_sort
 */
template<typename T>
void selection_sort(T* begin, T* end) {
  if (std::distance(begin, end) < 2) {
    // can't sort empty nor one-elem vector
    return;
  }
  // iterate over every element
  for (auto iter = begin; iter != end; ++iter) {
    // find smallest element in the (iter, end) range
    T* smallest = iter;
    for (auto inner_iter = iter + 1; inner_iter != end; inner_iter++) {
      if (*inner_iter < *smallest) {
        smallest = inner_iter;
      }
    }
    // swap smallest element with current element pointed to by iter
    std::swap(*iter, *smallest);
  }
}

/***
 * helper method for merge sort
 */
template<typename T>
static void merge(T* begin, T* middle, T* end) {
  // create two vectors, copy half of input vector to the left one, copy the
  // rest to the right one
  std::vector<int> left, right;
  left.resize(static_cast<std::size_t>(std::distance(begin, middle)));
  right.resize(static_cast<std::size_t>(std::distance(middle, end)));
  std::copy(begin, middle, std::begin(left));
  std::copy(middle, end, std::begin(right));

  // iterate over input, left and right, if left has lower or equa; item insert
  // it to input and increment iterator, if not do the same to the right one
  auto left_iter{std::begin(left)};
  auto right_iter{std::begin(right)};
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

/***
 * see https://en.wikipedia.org/wiki/Merge_sort
 */
template<typename T>
void merge_sort(T* first, T* last) {
  if (std::distance(first, last) < 2) return;
  // create iterator pointing to the middle of container
  T* middle{first};
  std::advance(middle, std::distance(first, last) / 2);
  // split vector in half and do recursion
  merge_sort(first, middle);
  merge_sort(middle, last);
  // merge two halves
  merge(first, middle, last);
}

template<typename T>
void bubble_sort(T* begin, T* end) {
  if (std::distance(begin, end) < 2) {
    // can't sort empty nor one-elem vector
    return;
  }
  // we are stopping at last elem, decrementing into begin
  for(auto stop = end - 1; stop != begin; stop--) {
    // iterate from begin until stop
    for(auto iter = begin; iter != stop; iter++) {
      // if next elem is smaller, swap
      if (*(iter + 1) < *iter) {
        std::swap(*(iter + 1), *iter);
      }
    }
  }
}
