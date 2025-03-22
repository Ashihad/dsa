#pragma once

#include <vector>
#include <functional>
#include <string>

std::vector<int> get_random_vector(const int);
void print_vector(const std::vector<int>&);
void print_vector(const std::vector<int>::iterator, const std::vector<int>::iterator);
void b_and_a(std::function<void(std::vector<int>&)>);

namespace custom
{
  std::string format(const char*, ...);
}