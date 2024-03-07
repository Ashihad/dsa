#include "sorting.hpp"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <functional>
#include <iomanip>

std::vector<int> get_random_vector(const int size) {
    std::vector<int> output;
    for (int i = 0; i < size; ++i) {
        output.push_back(static_cast<int>(std::rand() % (100)));
    }
    return output;
}

void print_vector(const std::vector<int>& vec) {
    for (auto iter = begin(vec); iter != end(vec); ++iter) {
        std::cout << std::setfill(' ') << std::setw(2) << *iter << ' ';
    }
    std::cout << std::endl;
}

void b_and_a(std::function<void(std::vector<int>&)> algo) {
    std::vector<int> tested {get_random_vector(10)};
    std::cout << "Before: " << std::endl;
    print_vector(tested);
    algo(tested);
    std::cout << "After: " << std::endl;
    print_vector(tested);
    std::cout << std::endl;
}

int main() {
    std::srand( static_cast<unsigned>(std::time(0)) );
    std::function<void(std::vector<int>&)> func { insertion_sort };
    b_and_a(func);
    return 0;
}
