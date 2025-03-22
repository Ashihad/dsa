#include <gtest/gtest.h>
#include "vector.hpp"
#include "misc.hpp"

#include <algorithm>

using namespace ::custom;

class VectorTests: public testing::Test {};

TEST_F(VectorTests, constructor_default)
{
  vector<int> vec{};
  ASSERT_EQ(vec.size(), 0);
}

TEST_F(VectorTests, constructor_one_arg)
{
  vector<int> vec(4);
  ASSERT_EQ(vec.size(), 4);
  ASSERT_TRUE(vec.capacity() >= vec.size());
  ASSERT_NO_THROW(vec.at(3));
  ASSERT_ANY_THROW(vec.at(4));
}

TEST_F(VectorTests, get_throws)
{
  vector<int> vec{};
  ASSERT_ANY_THROW(vec.at(0));
}

TEST_F(VectorTests, copy_constructor)
{
  vector<int> vec(4);
  vec.iota();
  vector<int> vec2(vec);
  ASSERT_EQ(vec.size(), vec2.size());
  ASSERT_EQ(vec.capacity(), vec2.capacity());

  ASSERT_EQ(vec[0], vec2[0]);
  ASSERT_EQ(vec[1], vec2[1]);
  ASSERT_EQ(vec[2], vec2[2]);
  ASSERT_EQ(vec[3], vec2[3]);
}

TEST_F(VectorTests, copy_assignment_operator)
{
  vector<int> vec(4);
  vec.iota();
  vector<int> vec2(2);
  vec2 = vec;
  ASSERT_EQ(vec.size(), vec2.size());
  ASSERT_EQ(vec.capacity(), vec2.capacity());

  ASSERT_EQ(vec[0], vec2[0]);
  ASSERT_EQ(vec[1], vec2[1]);
  ASSERT_EQ(vec[2], vec2[2]);
  ASSERT_EQ(vec[3], vec2[3]);
}

TEST_F(VectorTests, move_constructor)
{
  vector<int> vec(4);
  vec.iota();
  std::size_t old_vec_size{vec.size()};
  std::size_t old_vec_capacity{vec.capacity()};

  vector<int> vec2{std::move(vec)};
  ASSERT_EQ(vec2.size(), old_vec_size);
  ASSERT_EQ(vec2.capacity(), old_vec_capacity);
  ASSERT_EQ(vec2[0], 0);
  ASSERT_EQ(vec2[1], 1);
  ASSERT_EQ(vec2[2], 2);
  ASSERT_EQ(vec2[3], 3);

  ASSERT_EQ(vec.size(), 0);
  ASSERT_EQ(vec.capacity(), 0);
  ASSERT_ANY_THROW(vec.at(0));
}

TEST_F(VectorTests, move_assignment_operator)
{
  vector<int> vec(4);
  vec.iota();
  std::size_t old_vec_size{vec.size()};
  std::size_t old_vec_capacity{vec.capacity()};

  vector<int> vec2(2);
  vec2 = std::move(vec);
  ASSERT_EQ(vec2.size(), old_vec_size);
  ASSERT_EQ(vec2.capacity(), old_vec_capacity);
  ASSERT_EQ(vec2[0], 0);
  ASSERT_EQ(vec2[1], 1);
  ASSERT_EQ(vec2[2], 2);
  ASSERT_EQ(vec2[3], 3);

  ASSERT_EQ(vec.size(), 0);
  ASSERT_EQ(vec.capacity(), 0);
  ASSERT_ANY_THROW(vec.at(0));
}

TEST_F(VectorTests, initializer_list_constructor)
{
  vector<int> vec = {1, 2, 3, 4};
  ASSERT_EQ(vec.size(), 4);
  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 2);
  ASSERT_EQ(vec[2], 3);
  ASSERT_EQ(vec[3], 4);
}

TEST_F(VectorTests, filling_constructor)
{
  vector<int> vec(3, 2);
  ASSERT_EQ(vec.size(), 3);
  for (const auto& elem : vec) ASSERT_EQ(elem, 2);
}

TEST_F(VectorTests, push_back_basic)
{
  vector<int> vec = {1, 2, 3, 4};
  vec.push_back(5);
  ASSERT_EQ(vec.size(), 5);
  ASSERT_EQ(vec[4], 5);
  ASSERT_GE(vec.capacity(), vec.size());
}

TEST_F(VectorTests, push_back_size_zero)
{
  vector<int> vec(0);
  vec.push_back(1);
  ASSERT_EQ(vec.size(), 1);
  ASSERT_EQ(vec[0], 1);
  ASSERT_GE(vec.capacity(), vec.size());
}

TEST_F(VectorTests, resize_to_smaller)
{
  vector<int> vec = {1, 2, 3, 4};
  vec.resize(2);
  ASSERT_EQ(vec.size(), 2);
  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 2);
  ASSERT_ANY_THROW(vec[2]);
}

TEST_F(VectorTests, resize_to_bigger)
{
  vector<int> vec = {1, 2};
  vec.resize(4);
  ASSERT_EQ(vec.size(), 4);
  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 2);
  ASSERT_ANY_THROW(vec[4]);
}

TEST_F(VectorTests, inserting_basic)
{
  vector<int> vec = {1, 2, 3, 4};
  vec[2] = 4;
  ASSERT_EQ(vec.size(), 4);
  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 2);
  ASSERT_EQ(vec[2], 4);
  ASSERT_EQ(vec[3], 4);
}

TEST_F(VectorTests, insert_basic)
{
  vector<int> vec = {1, 2, 3, 4};
  vec.insert(2, 5);
  ASSERT_EQ(vec.size(), 5);
  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 2);
  ASSERT_EQ(vec[2], 5);
  ASSERT_EQ(vec[3], 3);
  ASSERT_EQ(vec[4], 4);
}

TEST_F(VectorTests, insert_back)
{
  vector<int> vec = {1, 2, 3, 4};
  vec.insert(4, 5);
  ASSERT_EQ(vec.size(), 5);
  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 2);
  ASSERT_EQ(vec[2], 3);
  ASSERT_EQ(vec[3], 4);
  ASSERT_EQ(vec[4], 5);
}

TEST_F(VectorTests, insert_out_of_range)
{
  vector<int> vec = {1, 2, 3, 4};
  ASSERT_ANY_THROW(vec.insert(5, 5));
}

TEST_F(VectorTests, erase_basic)
{
  vector<int> vec = {1, 2, 3, 4};
  vec.erase(2);
  ASSERT_EQ(vec.size(), 3);
  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 2);
  ASSERT_EQ(vec[2], 4);
}

TEST_F(VectorTests, erase_last)
{
  vector<int> vec = {1, 2, 3, 4};
  vec.erase(3);
  ASSERT_EQ(vec.size(), 3);
  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 2);
  ASSERT_EQ(vec[2], 3);
}

TEST_F(VectorTests, erase_out_of_range)
{
  vector<int> vec = {1, 2, 3, 4};
  ASSERT_ANY_THROW(vec.erase(4));
}

TEST_F(VectorTests, search_found)
{
  vector<int> vec = {1, 2, 3, 4};
  auto pos{vec.search(3)};
  ASSERT_EQ(*pos, 3);
  ASSERT_EQ(std::distance(vec.begin(), pos), 2);
}

TEST_F(VectorTests, search_not_found)
{
  vector<int> vec = {1, 2, 3, 4};
  auto pos{vec.search(5)};
  ASSERT_EQ(pos, vec.end());
}
