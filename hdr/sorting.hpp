#pragma once

#include <algorithm>

#include "misc.hpp"

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
  for (auto iter = begin + 1; iter != end; iter++) {
    // iterate backwards, and swap concurrent elements if they are in bad order
    for (auto r_iter = iter; r_iter != begin; r_iter--) {
      if (*(r_iter - 1) > *r_iter) {
        std::swap(*(r_iter - 1), *(r_iter));
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
 * see https://en.wikipedia.org/wiki/Merge_sort
 */
using ::custom::merge_sorted;
template<typename T>
void merge_sort(T* first, T* last) {
  if (std::distance(first, last) < 2) {
    // can't sort empty nor one-elem vector
    return;
  }
  // create iterator pointing to the middle of container
  T* middle = first + ((last - first) / 2);
  // split vector in half and do recursion
  merge_sort(first, middle);
  merge_sort(middle, last);
  // merge two halves
  merge_sorted(first, middle, last);
}

template<typename T>
void bubble_sort(T* begin, T* end) {
  if (std::distance(begin, end) < 2) {
    // can't sort empty nor one-elem vector
    return;
  }
  // we are stopping at last elem, decrementing into begin
  for (auto stop = end - 1; stop != begin; stop--) {
    // iterate from begin until stop
    for (auto iter = begin; iter != stop; iter++) {
      // if next elem is smaller, swap
      if (*(iter + 1) < *iter) {
        std::swap(*(iter + 1), *iter);
      }
    }
  }
}
