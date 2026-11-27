
#include <gtest/gtest.h>

#include <cmath>
#include <cstdlib>
#include <ctime>

#include "custom_vector.hpp"
#include "reduction.hpp"
#include "test_misc.hpp"

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

TEST_F(MinMaxAvgTests, avg_basic_member) {
  vector<int> test_vec{1, 3, 5, 7, 9, 2, 4, 6, 8, 69};

  double ret{test_vec.avg()};

  ASSERT_DOUBLE_EQ(ret, 11.4);
}

class IsSortedTests : public testing::Test {};

TEST_F(IsSortedTests, empty_input) {
  vector<int> test_vec{};

  ASSERT_TRUE(is_sorted(test_vec.begin(), test_vec.end()));
}

TEST_F(IsSortedTests, one_elem_input) {
  vector<int> test_vec{};
  test_vec.push_back(1);

  ASSERT_TRUE(is_sorted(test_vec.begin(), test_vec.end()));
}

TEST_F(IsSortedTests, sorted) {
  vector<int> test_vec{1, 2, 3, 4, 5};

  ASSERT_TRUE(is_sorted(test_vec.begin(), test_vec.end()));
}

TEST_F(IsSortedTests, not_sorted) {
  vector<int> test_vec{1, 2, 8, 4, 5};

  ASSERT_FALSE(is_sorted(test_vec.begin(), test_vec.end()));
}

TEST_F(IsSortedTests, sorted_repeating_values) {
  vector<int> test_vec{1, 2, 2, 3, 4};

  ASSERT_TRUE(is_sorted(test_vec.begin(), test_vec.end()));
}

TEST_F(IsSortedTests, not_sorted_repeating_values) {
  vector<int> test_vec{1, 2, 2, 4, 3};

  ASSERT_FALSE(is_sorted(test_vec.begin(), test_vec.end()));
}
