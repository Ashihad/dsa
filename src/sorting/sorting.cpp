#include "sorting.hpp"

#include <iostream>
#include <iterator>
#include <optional>
#include <climits>
#include <cmath>
#include <algorithm>

/***
 * see https://en.wikipedia.org/wiki/Insertion_sort
*/
void insertion_sort(std::vector<int>::iterator first, std::vector<int>::iterator last) {
    if (std::distance(first, last) < 2) return;
    // iterate over every element, except for first
    for (auto outer_iter = std::next(first); outer_iter != last; ++outer_iter) {
        // save current element for comparison
        int key { *outer_iter };
        // iterate over previous elements backwards, until bigger element is found
        // note: reverse iterator points to the previous element rather than the one source iterator actually refers to, fsfr
        auto inner_iter { make_reverse_iterator(outer_iter) };  // points at outer_iter-1
        auto reverse_end { make_reverse_iterator(first) };
        while (inner_iter != reverse_end && *inner_iter > key) {
            // put current element forward in every iteration of while loop
            *std::prev(inner_iter) = *inner_iter;
            inner_iter++;
        }
        // when while loop ends insert current element 
        *std::prev(inner_iter) = key;
    }
}

/***
 * see https://en.wikipedia.org/wiki/Selection_sort
*/
void selection_sort(std::vector<int>::iterator first, std::vector<int>::iterator last) {
    if (std::distance(first, last) < 2) return;
    // iterate over every element
    for (auto outer_iter = first; outer_iter != last; ++outer_iter) {
        // find smallest element in the (outer_iter, end) range
        auto smallest { std::min_element(outer_iter, last) };
        // swap smallest element with current element from outer_iter
        std::swap(*outer_iter, *smallest);
    }
}

/***
 * helper method for merge sort
*/
static void merge(std::vector<int>::iterator first, std::vector<int>::iterator middle, std::vector<int>::iterator last) {
    // create two vectors, copy half of input vector to the left one, copy the rest to the right one
    std::vector<int> left, right; 
    left.resize(static_cast<std::size_t>(std::distance(first, middle)));
    right.resize(static_cast<std::size_t>(std::distance(middle, last)));
    std::copy(first, middle, begin(left));
    std::copy(middle, last, begin(right));

    // iterate over input, left and right, if left has lower or equa; item insert it to input and increment iterator, if not do the same to the right one
    auto left_iter { begin(left) };
    auto right_iter { begin(right) };
    for (auto iter = first; iter != last; ++iter) {
        if (right_iter == end(right) || (left_iter != end(left) && *left_iter <= *right_iter)) {
            *iter = *left_iter;
            ++left_iter;
        }
        else {
            *iter = *right_iter;
            ++right_iter;
        }
    }
}

/***
 * see https://en.wikipedia.org/wiki/Merge_sort
*/
void merge_sort(std::vector<int>::iterator first, std::vector<int>::iterator last) {
    if (std::distance(first, last) < 2) return;
    // create iterator pointing to the middle of container
    std::vector<int>::iterator middle { first };
    std::advance(middle, std::distance(first, last)/2);
    // split vector in half and do recursion
    merge_sort(first, middle);
    merge_sort(middle, last);
    // merge two halves
    merge(first, middle, last);
}

#include <iomanip>
/***
 * see https://en.wikipedia.org/wiki/Bubble_sort
*/
void bubble_sort(std::vector<int>::iterator first, std::vector<int>::iterator last) {
    if (std::distance(first, last) < 2) return;
    // iterate over container, except for last element
    for (auto outer_iter = first; outer_iter != std::prev(last); ++outer_iter) {
        // construct reverse iterator to current element (+1 bcs reverse iterator offset)
        auto reverse_end { make_reverse_iterator(outer_iter+1) };
        // iterate backwards over container's tail
        for(auto inner_iter = make_reverse_iterator(last); inner_iter != reverse_end; ++inner_iter) {
            // if current element is lesser than one-to-the-left one swap them
            if (*inner_iter < *std::next(inner_iter)) std::swap(*inner_iter, *std::next(inner_iter));
        }
    }
}
