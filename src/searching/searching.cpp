#include "searching.hpp"

/***
 * see https://en.wikipedia.org/wiki/Linear_search
*/
std::optional<std::size_t> linear_search(const std::vector<int>::iterator first, const std::vector<int>::iterator last, int value) {
    // check each element if value matches
    for (auto iter = first; iter != last; ++iter) {
        if (*iter == value) {
            return static_cast<std::size_t>(std::distance(first, iter));
        }
    }
    return std::nullopt;
}

/***
 * see https://en.wikipedia.org/wiki/Binary_search_algorithm
*/
std::optional<std::size_t> binary_search(const std::vector<int>::iterator first, const std::vector<int>::iterator last, int value) {
    while (std::distance(first, last) > 2) {
        auto middle { first };
        std::advance(middle, std::distance(first, last)/2);
        if (*middle ==  value) {
            return static_cast<std::size_t>(std::distance(first, middle));
        }
        else if (*middle < value) {
            return binary_search(first, middle, value);
        }
        else if (*middle > value) {
            return binary_search(middle, last, value);
        }
    }
    return std::nullopt;
}