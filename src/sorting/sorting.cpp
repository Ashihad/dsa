#include "sorting.hpp"

#include <iostream>

void insertion_sort(std::vector<int>& input) {
    // iterate over every element,e xcept for first
    for (auto outer_iter = std::next(begin(input)); outer_iter != end(input); ++outer_iter) {
        // save current element for comparison
        int key { *outer_iter };
        // iterate over previous elements backwards, until bigger element is found
        auto inner_iter { std::prev(outer_iter) };
        while (inner_iter >= begin(input) && *inner_iter > key) {
            // put current element forward in every iteration
            *std::next(inner_iter) = *inner_iter;
            inner_iter--;
        }
        // when while loop ends insert current element 
        *std::next(inner_iter) = key;
    }
}
