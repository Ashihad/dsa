

#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "test_misc.hpp"
#include "transform.hpp"
#include "vector.hpp"

using namespace ::custom;

class ReverseTests : public testing::Test {};

TEST_F(ReverseTests, empty_input) {
  vector<int> test_vec{};

  ASSERT_NO_THROW(reverse(begin(test_vec), end(test_vec)));
}

TEST_F(ReverseTests, basic_even) {
  vector<int> test_vec{1, 3, 5, 7, 2, 4, 6, 8};
  vector<int> original_vec = test_vec;

  test_vec.reverse();

  ASSERT_TRUE(test_vec.size() == original_vec.size());
  ASSERT_TRUE(
      std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
  for (std::size_t i{}; i != test_vec.size(); i++) {
    ASSERT_EQ(test_vec[i], original_vec[original_vec.size() - 1 - i]);
  }
}

TEST_F(ReverseTests, basic_odd) {
  vector<int> test_vec{1, 3, 5, 7, 9, 2, 4, 6, 8};
  vector<int> original_vec = test_vec;

  test_vec.reverse();

  ASSERT_TRUE(test_vec.size() == original_vec.size());
  ASSERT_TRUE(
      std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
  for (std::size_t i{}; i != test_vec.size(); i++) {
    ASSERT_EQ(test_vec[i], original_vec[original_vec.size() - 1 - i]);
  }
}

TEST_F(ReverseTests, copy_empty_input) {
  vector<int> test_vec{};

  auto reversed_vec = test_vec.make_reverse();

  ASSERT_EQ(reversed_vec.size(), 0);
}

TEST_F(ReverseTests, copy_even) {
  vector<int> test_vec{1, 3, 5, 7, 2, 4, 6, 8};

  auto reversed_vec = test_vec.make_reverse();

  ASSERT_TRUE(test_vec.size() == reversed_vec.size());
  ASSERT_TRUE(
      std::is_permutation(begin(test_vec), end(test_vec), begin(reversed_vec)));
  for (std::size_t i{}; i != test_vec.size(); i++) {
    ASSERT_EQ(test_vec[i], reversed_vec[reversed_vec.size() - 1 - i]);
  }
}

TEST_F(ReverseTests, copy_odd) {
  vector<int> test_vec{1, 3, 5, 7, 9, 2, 4, 6, 8};

  auto reversed_vec = test_vec.make_reverse();

  ASSERT_TRUE(test_vec.size() == reversed_vec.size());
  ASSERT_TRUE(
      std::is_permutation(begin(test_vec), end(test_vec), begin(reversed_vec)));
  for (std::size_t i{}; i != test_vec.size(); i++) {
    ASSERT_EQ(test_vec[i], reversed_vec[reversed_vec.size() - 1 - i]);
  }
}
