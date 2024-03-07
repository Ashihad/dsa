#include "misc.hpp"
#include "sorting.hpp"
#include "searching.hpp"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <functional>

int main() {
    std::srand( static_cast<unsigned>( std::time(0)) );

    std::function<void(std::vector<int>&)> func { insertion_sort };
    b_and_a(func);

    std::vector<int> searched { get_random_vector(10) };
    // searched[8] = 123;
    std::optional<int> ret { linear_search(searched, 123) };
    if (ret.has_value()) std::cout << "Found 123 at index " << ret.value() << std::endl;
    else std::cout << "Value not found" << std::endl;
    return 0;
}
