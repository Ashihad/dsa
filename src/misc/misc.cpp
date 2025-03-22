#include "misc.hpp"

#include <iostream>
#include <iomanip>
#include <cstdarg>

std::vector<int> get_random_vector(const int size) {
    std::vector<int> output;
    for (int i = 0; i < size; ++i) {
        output.push_back(static_cast<int>(std::rand() % (10*size)));
    }
    return output;
}

void print_vector(const std::vector<int>& vec) {
    for (auto iter = begin(vec); iter != end(vec); ++iter) {
        std::cout << std::setfill(' ') << std::setw(2) << *iter << ' ';
    }
    std::cout << std::endl;
}

void print_vector(const std::vector<int>::iterator first, const std::vector<int>::iterator last) {
    for (auto iter = first; iter != last; ++iter) {
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

namespace custom
{
  std::string format(const char* fmt, ...) {
    constexpr size_t BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];

    va_list args;
    va_start(args, fmt);
    std::vsnprintf(buffer, BUFFER_SIZE, fmt, args);
    va_end(args);

    return std::string(buffer);
}
}
