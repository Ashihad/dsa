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
  // iterate over every element, except for 1st
  for (auto outer_iter{begin + 1}; outer_iter != end; ++outer_iter) {
    // save current element for comparison
    T current_elem{*outer_iter};

    auto inner_iter{outer_iter};
    while (inner_iter != begin && *inner_iter > current_elem) {
      // decrement first, to prevent out of bounds access
      inner_iter--;
      // put current element forward in every iteration of while loop
      *(inner_iter - 1) = *inner_iter;
    }
    // when while loop ends insert current element
    *(inner_iter - 1) = current_elem;
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
    auto smallest{std::min_element(iter, end)};
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
  if (std::distance(begin, end) < 2)
    return;
  // iterate over container, except for end element
  for (auto loop_iter_end= end-1; loop_iter_end != begin;) {
    loop_iter_end--;
    // iterate backwards over container's tail
    for (auto iter = begin; iter != loop_iter_end; ++iter) {
      // if current element is lesser than one-to-the-left one swap them
      if (*iter < *(iter+1)) {
        std::swap(*iter, *(iter+1));
      }
    }
  }
}
