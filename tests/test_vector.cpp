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

TEST_F(VectorTests, constructor_fill)
{
  vector<int> vec(4, 3);
  ASSERT_EQ(vec.size(), 4);
  ASSERT_TRUE(vec.capacity() >= vec.size());
  ASSERT_NO_THROW(vec.at(3));
  ASSERT_ANY_THROW(vec.at(4));
  for (const auto& elem : vec)
  {
    ASSERT_EQ(elem, 3);
  }
}

TEST_F(VectorTests, get_throws)
{
  vector<int> vec{};
  ASSERT_ANY_THROW(vec.at(1));
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

TEST_F(VectorTests, self_assignment)
{
  vector<int> vec(4);
  vec.iota();
  vec = vec;
  ASSERT_EQ(vec.size(), 4);
  ASSERT_GE(vec.capacity(), vec.size());

  ASSERT_EQ(vec[0], 0);
  ASSERT_EQ(vec[1], 1);
  ASSERT_EQ(vec[2], 2);
  ASSERT_EQ(vec[3], 3);
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

TEST_F(VectorTests, reserve_increases_capacity)
{
  vector<int> vec{};
  vec.reserve(10);
  ASSERT_EQ(vec.capacity(), 10);
}

TEST_F(VectorTests, resize_increases_capacity)
{
  vector<int> vec{};
  vec.resize(10);
  ASSERT_EQ(vec.size(), 10);
  ASSERT_GE(vec.capacity(), 10);
  ASSERT_NO_THROW(vec[9]);
  ASSERT_ANY_THROW(vec[10]);
}

TEST_F(VectorTests, resize_shrink)
{
  vector<int> vec(10);
  vec.resize(2);
  ASSERT_EQ(vec.size(), 2);
  ASSERT_GE(vec.capacity(), 10);
  ASSERT_NO_THROW(vec[1]);
  ASSERT_ANY_THROW(vec[2]);
}

TEST_F(VectorTests, resize_shrink_to_zero)
{
  vector<int> vec(10);
  vec.resize(0);
  ASSERT_EQ(vec.size(), 0);
  ASSERT_GE(vec.capacity(), 10);
  ASSERT_ANY_THROW(vec[0]);
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

TEST_F(VectorTests, set_basic)
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

TEST_F(VectorTests, max_last)
{
  vector<int> vec = {1, 2, 3, 4};
  int max{vec.max()};
  ASSERT_EQ(max, 4);
}

TEST_F(VectorTests, max_first)
{
  vector<int> vec = {4, 2, 3, 1};
  int max{vec.max()};
  ASSERT_EQ(max, 4);
}

TEST_F(VectorTests, max_middle)
{
  vector<int> vec = {3, 2, 4, 1};
  int max{vec.max()};
  ASSERT_EQ(max, 4);
}

TEST_F(VectorTests, max_empty_vector)
{
  vector<int> vec{};
  ASSERT_ANY_THROW(vec.max());
}

TEST_F(VectorTests, min_last)
{
  vector<int> vec = {4, 3, 2, 1};
  int min{vec.min()};
  ASSERT_EQ(min, 1);
}

TEST_F(VectorTests, min_first)
{
  vector<int> vec = {1, 2, 3, 4};
  int min{vec.min()};
  ASSERT_EQ(min, 1);
}

TEST_F(VectorTests, min_middle)
{
  vector<int> vec = {3, 1, 4, 2};
  int min{vec.min()};
  ASSERT_EQ(min, 1);
}

TEST_F(VectorTests, min_empty_vector)
{
  vector<int> vec{};
  ASSERT_ANY_THROW(vec.min());
}

TEST_F(VectorTests, sum_basic)
{
  vector<int> vec = {1, 2, 3, 4};
  int sum{vec.sum()};
  ASSERT_EQ(sum, 10);
}

TEST_F(VectorTests, sum_empty_vector)
{
  vector<int> vec{};
  ASSERT_ANY_THROW(vec.sum());
}

TEST_F(VectorTests, avg_basic)
{
  vector<int> vec = {1, 2, 3, 4};
  double avg{vec.avg()};
  ASSERT_DOUBLE_EQ(avg, 2.5);
}

TEST_F(VectorTests, avg_empty_vector)
{
  vector<int> vec{};
  ASSERT_ANY_THROW(vec.avg());
}

TEST_F(VectorTests, reverse_even)
{
  vector<int> vec{1, 2, 3, 4};
  vec.reverse();
  ASSERT_EQ(vec.size(), 4);
  ASSERT_EQ(vec[0], 4);
  ASSERT_EQ(vec[1], 3);
  ASSERT_EQ(vec[2], 2);
  ASSERT_EQ(vec[3], 1);
}

TEST_F(VectorTests, reverse_odd)
{
  vector<int> vec{1, 2, 3, 4, 5};
  vec.reverse();
  ASSERT_EQ(vec.size(), 5);
  ASSERT_EQ(vec[0], 5);
  ASSERT_EQ(vec[1], 4);
  ASSERT_EQ(vec[2], 3);
  ASSERT_EQ(vec[3], 2);
  ASSERT_EQ(vec[4], 1);
}

TEST_F(VectorTests, reverse_empty_vector)
{
  vector<int> vec{};
  ASSERT_ANY_THROW(vec.reverse());
}

TEST_F(VectorTests, shift_left_basic)
{
  vector<int> vec{1, 2, 3, 4};
  vec.shift_left();
  ASSERT_EQ(vec[0], 2);
  ASSERT_EQ(vec[1], 3);
  ASSERT_EQ(vec[2], 4);
  ASSERT_EQ(vec[3], 0);
}

TEST_F(VectorTests, shift_left_index_out_of_range)
{
  vector<int> vec{1, 2, 3, 4};
  ASSERT_ANY_THROW(vec.shift_left(5));
}

TEST_F(VectorTests, shift_left_offset_out_of_range)
{
  vector<int> vec{1, 2, 3, 4};
  ASSERT_ANY_THROW(vec.shift_left(0, 5));
}

TEST_F(VectorTests, shift_right_basic)
{
  vector<int> vec{1, 2, 3, 4};
  vec.shift_right();
  ASSERT_EQ(vec[0], 0);
  ASSERT_EQ(vec[1], 1);
  ASSERT_EQ(vec[2], 2);
  ASSERT_EQ(vec[3], 3);
}

TEST_F(VectorTests, shift_right_index_out_of_range)
{
  vector<int> vec{1, 2, 3, 4};
  ASSERT_ANY_THROW(vec.shift_right(5));
}

TEST_F(VectorTests, shift_right_offset_out_of_range)
{
  vector<int> vec{1, 2, 3, 4};
  ASSERT_ANY_THROW(vec.shift_right(0, 5));
}

TEST_F(VectorTests, rotate_left)
{
  vector<int> vec{1, 2, 3, 4};
  vec.rotate_left();
  ASSERT_EQ(vec[0], 2);
  ASSERT_EQ(vec[1], 3);
  ASSERT_EQ(vec[2], 4);
  ASSERT_EQ(vec[3], 1);
}

TEST_F(VectorTests, rotate_right)
{
  vector<int> vec{1, 2, 3, 4};
  vec.rotate_right();
  ASSERT_EQ(vec[0], 4);
  ASSERT_EQ(vec[1], 1);
  ASSERT_EQ(vec[2], 2);
  ASSERT_EQ(vec[3], 3);
}

TEST_F(VectorTests, is_sorted_true)
{
  vector<int> vec{1, 2, 3, 4};
  ASSERT_TRUE(vec.is_sorted());
}

TEST_F(VectorTests, is_sorted_false)
{
  vector<int> vec{1, 3, 2, 4};
  ASSERT_FALSE(vec.is_sorted());
}

TEST_F(VectorTests, insert_sorted_basic)
{
  vector<int> vec{1, 2, 4, 5};
  vec.insert_sorted(3);
  ASSERT_EQ(vec.size(), 5);
  ASSERT_EQ(vec[2], 3);
}

TEST_F(VectorTests, insert_sorted_begin)
{
  vector<int> vec{1, 2, 3, 4};
  vec.insert_sorted(-1);
  ASSERT_EQ(vec.size(), 5);
  ASSERT_EQ(vec[0], -1);
}

TEST_F(VectorTests, insert_sorted_end)
{
  vector<int> vec{1, 2, 3, 4};
  vec.insert_sorted(5);
  ASSERT_EQ(vec.size(), 5);
  ASSERT_EQ(vec[4], 5);
}

TEST_F(VectorTests, partition_even)
{
  vector<int> vec{1, -2, 3, -4};
  vec.partition();
  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 3);
  ASSERT_EQ(vec[2], -2);
  ASSERT_EQ(vec[3], -4);
}

TEST_F(VectorTests, partition_odd)
{
  vector<int> vec{1, -2, 3, -4, 5};
  vec.partition();
  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 5);
  ASSERT_EQ(vec[2], 3);
  ASSERT_EQ(vec[3], -4);
  ASSERT_EQ(vec[4], -2);
}

TEST_F(VectorTests, partition_already_partitioned)
{
  vector<int> vec{1, 2, 3, -4, -5};
  vec.partition();
  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 2);
  ASSERT_EQ(vec[2], 3);
  ASSERT_EQ(vec[3], -4);
  ASSERT_EQ(vec[4], -5);
}
