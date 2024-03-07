#include "sorting.hpp"

#include <iostream>
#include <iterator>
#include <optional>
#include <climits>
#include <algorithm>

/***
 * see https://en.wikipedia.org/wiki/Insertion_sort
*/
void insertion_sort(std::vector<int>& input) {
    if (input.empty()) return;
    // iterate over every element, except for first
    for (auto outer_iter = std::next(begin(input)); outer_iter != end(input); ++outer_iter) {
        // save current element for comparison
        int key { *outer_iter };
        // iterate over previous elements backwards, until bigger element is found
        // note: reverse iterator stores an iterator to the next element rather than the one it actually refers to, fsfr
        auto inner_iter { make_reverse_iterator(outer_iter) };
        while (inner_iter != rend(input) && *inner_iter > key) {
            // put current element forward in every iteration
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
void selection_sort(std::vector<int>& input) {
    if (input.empty()) return;
    // iterate over every element
    for (auto outer_iter = begin(input); outer_iter != end(input); ++outer_iter) {
        // find smallest element in the (outer_iter, end) range
        auto smallest { std::min_element(outer_iter, end(input)) };
        // swap smallest element with current element from outer_iter
        std::swap(*outer_iter, *smallest);
    }
}
