#include "searching.hpp"

/***
 * see https://en.wikipedia.org/wiki/Linear_search
*/
std::optional<int> linear_search(std::vector<int> input, int value) {
    // check each element if value matches
    for (size_t i = 0; i < input.size(); ++i) {
        if (input[i] == value) {
            return i;
        }
    }
    return std::nullopt;
}