#include <gtest/gtest.h>

#include "vector.hpp"
#include "misc.hpp"

using namespace ::custom;

class ReverseTests : public testing::Test {};

TEST_F(ReverseTests, empty_input) {
  vector<int> test_vec{};

  ASSERT_NO_THROW(reverse(test_vec.begin(), test_vec.end()));
  ASSERT_EQ(test_vec.size(), 0);
}

TEST_F(ReverseTests, basic_even) {
  vector<int> test_vec{1, 2, 3, 4, 5, 6};
  vector<int> expected_vec{6, 5, 4, 3, 2, 1};

  ASSERT_NO_THROW(reverse(test_vec.begin(), test_vec.end()));
  ASSERT_EQ(test_vec.size(), expected_vec.size());
  for (size_t i{}; i < test_vec.size(); i++) {
    ASSERT_EQ(test_vec[i], expected_vec[i]);
  }
}

TEST_F(ReverseTests, basic_odd) {
  vector<int> test_vec{1, 2, 3, 4, 5, 6, 7};
  vector<int> expected_vec{7, 6, 5, 4, 3, 2, 1};

  ASSERT_NO_THROW(reverse(test_vec.begin(), test_vec.end()));
  ASSERT_EQ(test_vec.size(), expected_vec.size());
  for (size_t i{}; i < test_vec.size(); i++) {
    ASSERT_EQ(test_vec[i], expected_vec[i]);
  }
}
