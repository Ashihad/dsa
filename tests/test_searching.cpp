#include <gtest/gtest.h>
#include "searching.hpp"
#include "misc.hpp"
#include "vector.hpp"

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>

using namespace ::custom;

template<typename T>
T* insert_value_randomly(T* first, T* last, T value)
{
  std::size_t random_index { static_cast<std::size_t>(std::rand()) % static_cast<std::size_t>(std::distance(first, last)) };
  first[random_index] = value;
  return first + random_index;
}

class LinearSearchTests: public testing::Test
{
  void SetUp() override
  {
    std::srand( static_cast<unsigned>( std::time(0) ) );
  }
};

TEST_F(LinearSearchTests, empty_input) {
  vector<int> test_vec(0);

  auto ret { linear_search(begin(test_vec), end(test_vec), 0) };
  ASSERT_EQ(ret, end(test_vec));
}

TEST_F(LinearSearchTests, basic_search_value_inserted) {
  vector<int> test_vec { 1, 3, 5, 7, 9, 2, 4, 6, 8 };

  auto ret { linear_search(begin(test_vec), end(test_vec), 3) };
  ASSERT_EQ(std::distance(begin(test_vec), ret), 1);
}

TEST_F(LinearSearchTests, basic_search_value_not_inserted) {
  vector<int> test_vec { 1, 3, 5, 7, 9, 2, 4, 6, 8 };

  auto ret { linear_search(begin(test_vec), end(test_vec), 10) };
  ASSERT_EQ(ret, end(test_vec));
}

TEST_F(LinearSearchTests, random_test_value_inserted)
{
  vector<int> vec_sizes{10, 100, 1000};
  for (const int& vec_size: vec_sizes)
  {
    for (int i = 0; i < 10; ++i)
    {
      vector<int> test_vec{get_random_vector<int>(static_cast<std::size_t>(vec_size))};
      int random_value { std::rand() % 10*vec_size };
      // remove random values from vector, replace with value impossible to get randomly
      std::replace(begin(test_vec), end(test_vec), random_value, 10*vec_size+1);
      auto correct_index { insert_value_randomly(begin(test_vec), end(test_vec), random_value) };

      auto ret { linear_search(begin(test_vec), end(test_vec), random_value) };
      ASSERT_EQ(std::distance(begin(test_vec), ret), std::distance(begin(test_vec), correct_index));
    }
  }
}

TEST_F(LinearSearchTests, random_test_value_not_inserted)
{
  vector<int> vec_sizes{10, 100, 1000};
  for (int vec_size: vec_sizes)
  {
    for (int i = 0; i < 10; ++i)
    {
      vector<int> test_vec {get_random_vector<int>(static_cast<std::size_t>(vec_size))};
      int random_value { std::rand() % 10*vec_size };
      // remove random values from vector, replace with value impossible to get randomly
      std::replace(begin(test_vec), end(test_vec), random_value, 10*vec_size+1);

      auto ret { linear_search(begin(test_vec), end(test_vec), random_value) };
      ASSERT_EQ(ret, end(test_vec));
    }
  }
}

// binary_search

class BinarySearchTests: public testing::Test
{
  void SetUp() override
  {
    std::srand( static_cast<unsigned>( std::time(0) ) );
  }
};

TEST_F(BinarySearchTests, HandleEmptyInput) {
  vector<int> test_vec;

  auto ret { binary_search(begin(test_vec), end(test_vec), 0) };
  ASSERT_EQ(ret, end(test_vec));
}

TEST_F(BinarySearchTests, basic_search_value_inserted)
{
  vector<int> test_vec { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

  auto ret { binary_search(begin(test_vec), end(test_vec), 3) };
  ASSERT_EQ(std::distance(begin(test_vec), ret), 2);
}

TEST_F(BinarySearchTests, basic_search_value_not_inserted)
{
    vector<int> test_vec { 1, 2, 4, 5, 6, 7, 8, 9 };

    auto ret { binary_search(begin(test_vec), end(test_vec), 3) };
    ASSERT_EQ(ret, end(test_vec));
}

TEST_F(BinarySearchTests, random_search_value_inserted)
{
  vector<int> vec_sizes{10, 100, 1000};
  for (int vec_size: vec_sizes)
  {
    for( int i = 0; i < 10; ++i )
    {
      vector<int> test_vec { get_random_vector<int>(static_cast<std::size_t>(vec_size)) };
      int random_value { std::rand() % 10*vec_size };
      // remove random values from vector, replace with value impossible to get randomly
      std::replace(begin(test_vec), end(test_vec), random_value, 10*vec_size+1);
      insert_value_randomly(begin(test_vec), end(test_vec), random_value);
      // vector must be sorted for this algo
      std::sort(begin(test_vec), end(test_vec));

      auto ret { binary_search(begin(test_vec), end(test_vec), random_value) };
      ASSERT_NE(ret, end(test_vec));
      ASSERT_EQ(*ret, random_value);
    }
  }
}

TEST_F(BinarySearchTests, random_search_value_not_inserted)
{
  vector<int> vec_sizes{10, 100, 1000};
  for (int vec_size: vec_sizes)
  {
    for( int i = 0; i < 10; ++i )
    {
      vector<int> test_vec { get_random_vector<int>(static_cast<std::size_t>(vec_size)) };
      int random_value { std::rand() % 10*vec_size };
      // remove random values from vector, replace with value impossible to get randomly
      std::replace(begin(test_vec), end(test_vec), random_value, 10*vec_size+1);
      // vector must be sorted for this algo
      std::sort(begin(test_vec), end(test_vec));

      auto ret { binary_search(begin(test_vec), end(test_vec), random_value) };
      ASSERT_EQ(ret, end(test_vec));
    }
  }
}
