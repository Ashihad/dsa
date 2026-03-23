#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "misc.hpp"
#include "searching.hpp"
#include "vector.hpp"

using namespace ::custom;

class LinearSearchTests : public testing::Test {
  void SetUp() override { std::srand(static_cast<unsigned>(std::time(0))); }
};

TEST_F(LinearSearchTests, empty_input) {
  vector<int> test_vec{};

  std::optional<int*> ret{linear_search(begin(test_vec), end(test_vec), 0)};

  ASSERT_FALSE(ret.has_value());
}

TEST_F(LinearSearchTests, basic_search_value_inserted) {
  vector<int> test_vec{1, 3, 5, 7, 9, 2, 4, 6, 8};

  std::optional<int*> ret{linear_search(begin(test_vec), end(test_vec), 3)};

  ASSERT_TRUE(ret.has_value());
  ASSERT_EQ(std::distance(begin(test_vec), *ret), 1);
}

TEST_F(LinearSearchTests, basic_search_value_not_inserted) {
  vector<int> test_vec{1, 3, 5, 7, 9, 2, 4, 6, 8};

  std::optional<int*> ret{linear_search(begin(test_vec), end(test_vec), 10)};

  ASSERT_FALSE(ret.has_value());
}

TEST_F(LinearSearchTests, random_test_value_inserted) {
  vector<int> vec_sizes{10, 100, 1000};
  for (int vec_size : vec_sizes) {
    for (int i = 0; i < 10; ++i) {
      vector<int> test_vec{
          get_random_vector<int>(static_cast<std::size_t>(vec_size))};
      int random_value{std::rand() % 10 * vec_size};
      // remove random values from vector, replace with value impossible to get
      // randomly
      std::replace(
          begin(test_vec), end(test_vec), random_value, 10 * vec_size + 1);
      auto correct_index{
          insert_value_randomly(begin(test_vec), end(test_vec), random_value)};

      std::optional<int*> ret{
          linear_search(begin(test_vec), end(test_vec), random_value)};

      ASSERT_TRUE(ret.has_value());
      ASSERT_EQ(std::distance(begin(test_vec), *ret),
                std::distance(begin(test_vec), correct_index));
    }
  }
}

TEST_F(LinearSearchTests, random_test_value_not_inserted) {
  vector<int> vec_sizes{10, 100, 1000};
  for (int vec_size : vec_sizes) {
    for (int i = 0; i < 10; ++i) {
      vector<int> test_vec{
          get_random_vector<int>(static_cast<std::size_t>(vec_size))};
      int random_value{std::rand() % 10 * vec_size};
      // remove random values from vector, replace with value impossible to get
      // randomly
      std::replace(
          begin(test_vec), end(test_vec), random_value, 10 * vec_size + 1);

      std::optional<int*> ret{
          linear_search(begin(test_vec), end(test_vec), random_value)};

      ASSERT_FALSE(ret.has_value());
    }
  }
}

// binary_search

class BinarySearchTests : public testing::Test {
  void SetUp() override { std::srand(static_cast<unsigned>(std::time(0))); }
};

TEST_F(BinarySearchTests, HandleEmptyInput) {
  vector<int> test_vec;

  std::optional<int*> ret{binary_search(begin(test_vec), end(test_vec), 0)};

  ASSERT_FALSE(ret.has_value());
}

TEST_F(BinarySearchTests, basic_search_value_inserted) {
  vector<int> test_vec{1, 2, 3, 4, 5, 6, 7, 8, 9};

  std::optional<int*> ret{binary_search(begin(test_vec), end(test_vec), 3)};

  ASSERT_TRUE(ret.has_value()) << std::distance(begin(test_vec), end(test_vec));
  ASSERT_EQ(std::distance(begin(test_vec), *ret), 2);
}

TEST_F(BinarySearchTests, basic_search_value_not_inserted) {
  vector<int> test_vec{1, 2, 4, 5, 6, 7, 8, 9};

  std::optional<int*> ret{binary_search(begin(test_vec), end(test_vec), 3)};

  ASSERT_FALSE(ret.has_value());
}

TEST_F(BinarySearchTests, random_search_value_inserted) {
  vector<int> vec_sizes{10, 100, 1000};
  for (int vec_size : vec_sizes) {
    for (int i = 0; i < 10; ++i) {
      vector<int> test_vec{
          get_random_vector<int>(static_cast<std::size_t>(vec_size))};
      int random_value{std::rand() % 10 * vec_size};
      // remove random values from vector, replace with value impossible to get
      // randomly
      std::replace(
          begin(test_vec), end(test_vec), random_value, 10 * vec_size + 1);
      insert_value_randomly(begin(test_vec), end(test_vec), random_value);
      // vector must be sorted for this algo
      std::sort(begin(test_vec), end(test_vec));

      std::optional<int*> ret{
          binary_search(begin(test_vec), end(test_vec), random_value)};

      ASSERT_TRUE(ret.has_value());
      ASSERT_EQ(*(ret.value()), random_value);
    }
  }
}

TEST_F(BinarySearchTests, random_search_value_not_inserted) {
  vector<int> vec_sizes{10, 100, 1000};
  for (int vec_size : vec_sizes) {
    for (int i = 0; i < 10; ++i) {
      vector<int> test_vec{
          get_random_vector<int>(static_cast<std::size_t>(vec_size))};
      int random_value{std::rand() % 10 * vec_size};
      // remove random values from vector, replace with value impossible to get
      // randomly
      std::replace(
          begin(test_vec), end(test_vec), random_value, 10 * vec_size + 1);
      // vector must be sorted for this algo
      std::sort(begin(test_vec), end(test_vec));

      std::optional<int*> ret{
          binary_search(begin(test_vec), end(test_vec), random_value)};

      ASSERT_FALSE(ret.has_value());
    }
  }
}
