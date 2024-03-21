#pragma once

#include <vector>
#include <optional>

std::optional<std::size_t> linear_search(const std::vector<int>::iterator, const std::vector<int>::iterator, int value);
std::optional<std::size_t> binary_search(const std::vector<int>::iterator, const std::vector<int>::iterator, int value);