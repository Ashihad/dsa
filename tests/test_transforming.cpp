#include <gtest/gtest.h>
#include "transforming.hpp"
#include "misc.hpp"
#include "vector.hpp"

using namespace ::custom;

class TransformingTests: public testing::Test {};

TEST_F(TransformingTests, reverse_empty_input)
{
  vector<int> vec(0);
  reverse(begin(vec), end(vec));
  ASSERT_EQ(vec.size(), 0);
}

TEST_F(TransformingTests, reverse_basic_even)
{
  vector<int> vec = {1, 2, 3, 4};
  reverse(begin(vec), end(vec));
  ASSERT_EQ(vec[0], 4);
  ASSERT_EQ(vec[1], 3);
  ASSERT_EQ(vec[2], 2);
  ASSERT_EQ(vec[3], 1);
}

TEST_F(TransformingTests, reverse_basic_odd)
{
  vector<int> vec = {1, 2, 3, 4, 5};
  reverse(begin(vec), end(vec));
  ASSERT_EQ(vec[0], 5);
  ASSERT_EQ(vec[1], 4);
  ASSERT_EQ(vec[2], 3);
  ASSERT_EQ(vec[3], 2);
  ASSERT_EQ(vec[4], 1);
}

TEST_F(TransformingTests, reverse_twice_even)
{
  vector<int> old_vec = {1, 2, 3, 4};
  vector<int> vec(old_vec);
  reverse(begin(vec), end(vec));
  reverse(begin(vec), end(vec));
  ASSERT_EQ(vec, old_vec);
}

TEST_F(TransformingTests, reverse_twice_odd)
{
  vector<int> old_vec = {1, 2, 3, 4, 5};
  vector<int> vec(old_vec);
  reverse(begin(vec), end(vec));
  reverse(begin(vec), end(vec));
  ASSERT_EQ(vec, old_vec);
}
