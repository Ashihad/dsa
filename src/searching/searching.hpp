#pragma once

#include <vector>
#include <optional>

std::optional<std::vector<int>::iterator> linear_search(const std::vector<int>::iterator, const std::vector<int>::iterator, int value);
std::optional<std::vector<int>::iterator> binary_search(const std::vector<int>::iterator, const std::vector<int>::iterator, int value);