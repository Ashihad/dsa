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