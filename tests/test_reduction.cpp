
#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "searching.hpp"
#include "test_misc.hpp"
#include "vector.hpp"

using namespace ::custom;

class MinMaxAvgTests : public testing::Test {};

TEST_F(MinMaxAvgTests, max_empty_input) {
  vector<int> test_vec{};

  ASSERT_THROW(max(begin(test_vec), end(test_vec)), std::out_of_range);
}

TEST_F(MinMaxAvgTests, max_basic) {
  vector<int> test_vec{1, 3, 5, 7, 9, 2, 4, 6, 8};

  int* ret{max(begin(test_vec), end(test_vec))};

  ASSERT_EQ(*ret, 9);
}

TEST_F(MinMaxAvgTests, max_multiple_max) {
  vector<int> test_vec{0, 0, 0, 0, 0};

  int* ret{max(begin(test_vec), end(test_vec))};

  ASSERT_EQ(*ret, 0);
}

TEST_F(MinMaxAvgTests, min_empty_input) {
  vector<int> test_vec{};

  ASSERT_THROW(min(begin(test_vec), end(test_vec)), std::out_of_range);
}

TEST_F(MinMaxAvgTests, min_basic) {
  vector<int> test_vec{1, 3, 5, 7, 9, 2, 4, 6, 8};

  int* ret{min(begin(test_vec), end(test_vec))};

  ASSERT_EQ(*ret, 1);
}

TEST_F(MinMaxAvgTests, min_multiple_min) {
  vector<int> test_vec{0, 0, 0, 0, 0};

  int* ret{min(begin(test_vec), end(test_vec))};

  ASSERT_EQ(*ret, 0);
}

TEST_F(MinMaxAvgTests, avg_empty_input) {
  vector<int> test_vec{};

  ASSERT_THROW(avg(begin(test_vec), end(test_vec)), std::out_of_range);
}

TEST_F(MinMaxAvgTests, avg_basic) {
  vector<int> test_vec{1, 3, 5, 7, 9, 2, 4, 6, 8, 69};

  double ret{avg(begin(test_vec), end(test_vec))};

  ASSERT_DOUBLE_EQ(ret, 11.4);
}

