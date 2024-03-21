#include "searching.hpp"

#include <iostream>

/***
 * see https://en.wikipedia.org/wiki/Linear_search
*/
std::optional<std::vector<int>::iterator> linear_search(const std::vector<int>::iterator first, const std::vector<int>::iterator last, int value) {
    // check each element if value matches
    for (auto iter = first; iter != last; ++iter) {
        if (*iter == value) {
            return iter;
        }
    }
    return std::nullopt;
}

/***
 * NOTE: Works only for sorted containers
 * see https://en.wikipedia.org/wiki/Binary_search_algorithm
*/
std::optional<std::vector<int>::iterator> binary_search(const std::vector<int>::iterator first, const std::vector<int>::iterator last, int value) {
    while (std::distance(first, last) > 1) {
        // create iterator pointing to middle element
        auto middle { first };
        std::advance(middle, std::distance(first, last)/2);
        // check if middle points to searched value
        if (*middle ==  value) {
            return middle;
        }
        // if its lower than searched value check left subcontainer
        else if (*middle > value) {
            return binary_search(first, middle, value);
        }
        // if its higher than searched value check right subcontainer
        else if (*middle < value) {
            return binary_search(middle, last, value);
        }
    }
    // check if we didnt end on searched one
    if (*first ==  value) {
        return first;
    }
    // if loop fails value is not there
    return std::nullopt;
}