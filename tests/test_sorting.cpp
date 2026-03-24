#include <gtest/gtest.h>
#include "test_misc.hpp"
#include "sorting.hpp"
#include "vector.hpp"

#include <algorithm>

using namespace ::custom;

// insertion_sort
class InsertionSortTests : public testing::Test {
  void SetUp() override { std::srand(static_cast<unsigned>(std::time(0))); }
};

TEST_F(InsertionSortTests, HandleEmptyInput) {
  vector<int> test_vec;
  vector<int> original_vec = test_vec;

  insertion_sort(begin(test_vec), end(test_vec));

  EXPECT_TRUE(test_vec.size() == original_vec.size());
  EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
  EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(InsertionSortTests, HandleOneElementInput) {
  vector<int> test_vec{1};
  vector<int> original_vec = test_vec;

  insertion_sort(begin(test_vec), end(test_vec));

  EXPECT_TRUE(test_vec.size() == original_vec.size());
  EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
  EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(InsertionSortTests, SimpleSort) {
  vector<int> test_vec{1, 3, 5, 7, 9, 2, 4, 6, 8, 0};
  vector<int> original_vec = test_vec;

  insertion_sort(begin(test_vec), end(test_vec));

  EXPECT_TRUE(test_vec.size() == original_vec.size());
  EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
  EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(InsertionSortTests, AlreadySorted) {
  vector<int> test_vec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  vector<int> original_vec = test_vec;

  insertion_sort(begin(test_vec), end(test_vec));

  EXPECT_TRUE(test_vec.size() == original_vec.size());
  EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
  EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(InsertionSortTests, SortedInversely) {
  vector<int> test_vec{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  vector<int> original_vec = test_vec;

  insertion_sort(begin(test_vec), end(test_vec));

  EXPECT_TRUE(test_vec.size() == original_vec.size());
  EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
  EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(InsertionSortTests, RandomSort) {
  vector<std::size_t> vec_sizes = {10, 100, 1000};
  for (auto vec_size : vec_sizes) {
    for (int i = 0; i < 3; ++i) {
      vector<int> test_vec{get_random_vector<int>(vec_size)};
      vector<int> original_vec = test_vec;

      selection_sort(begin(test_vec), end(test_vec));

      EXPECT_TRUE(test_vec.size() == original_vec.size());
      EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
      EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
    }
  }
}

// selection sort

class SelectionSortTests : public testing::Test {
  void SetUp() override { std::srand(static_cast<unsigned>(std::time(0))); }
};

TEST_F(SelectionSortTests, HandleEmptyInput) {
  vector<int> test_vec;
  vector<int> original_vec = test_vec;

  selection_sort(begin(test_vec), end(test_vec));

  EXPECT_TRUE(test_vec.size() == original_vec.size());
  EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
  EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(SelectionSortTests, HandleOneElementInput) {
  vector<int> test_vec{1};
  vector<int> original_vec = test_vec;

  selection_sort(begin(test_vec), end(test_vec));

  EXPECT_TRUE(test_vec.size() == original_vec.size());
  EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
  EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(SelectionSortTests, SimpleSort) {
  vector<int> test_vec{1, 3, 5, 7, 9, 2, 4, 6, 8, 0};
  vector<int> original_vec = test_vec;

  selection_sort(begin(test_vec), end(test_vec));

  EXPECT_TRUE(test_vec.size() == original_vec.size());
  EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
  EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(SelectionSortTests, AlreadySorted) {
  vector<int> test_vec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  vector<int> original_vec = test_vec;

  selection_sort(begin(test_vec), end(test_vec));

  EXPECT_TRUE(test_vec.size() == original_vec.size());
  EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
  EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(SelectionSortTests, SortedInversely) {
  vector<int> test_vec{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  vector<int> original_vec = test_vec;

  selection_sort(begin(test_vec), end(test_vec));

  EXPECT_TRUE(test_vec.size() == original_vec.size());
  EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
  EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(SelectionSortTests, RandomSort) {
  vector<std::size_t> vec_sizes = {10, 100, 1000};
  for (auto vec_size : vec_sizes) {
    for (int i = 0; i < 3; ++i) {
      vector<int> test_vec{get_random_vector<int>(vec_size)};
      vector<int> original_vec = test_vec;

      selection_sort(begin(test_vec), end(test_vec));

      EXPECT_TRUE(test_vec.size() == original_vec.size());
      EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
      EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
    }
  }
}

// merge sort

class MergeSortTests : public testing::Test {
  void SetUp() override { std::srand(static_cast<unsigned>(std::time(0))); }
};

TEST_F(MergeSortTests, HandleEmptyInput) {
  vector<int> test_vec;
  vector<int> original_vec = test_vec;

  merge_sort(begin(test_vec), end(test_vec));

  EXPECT_TRUE(test_vec.size() == original_vec.size());
  EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
  EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(MergeSortTests, HandleOneElementInput) {
  vector<int> test_vec{1};
  vector<int> original_vec = test_vec;

  merge_sort(begin(test_vec), end(test_vec));

  EXPECT_TRUE(test_vec.size() == original_vec.size());
  EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
  EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(MergeSortTests, SimpleSort) {
  vector<int> test_vec{1, 3, 5, 7, 9, 2, 4, 6, 8, 0};
  vector<int> original_vec = test_vec;

  merge_sort(begin(test_vec), end(test_vec));

  EXPECT_TRUE(test_vec.size() == original_vec.size());
  EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
  EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(MergeSortTests, AlreadySorted) {
  vector<int> test_vec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  vector<int> original_vec = test_vec;

  merge_sort(begin(test_vec), end(test_vec));

  EXPECT_TRUE(test_vec.size() == original_vec.size());
  EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
  EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(MergeSortTests, SortedInversely) {
  vector<int> test_vec{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  vector<int> original_vec = test_vec;

  merge_sort(begin(test_vec), end(test_vec));

  EXPECT_TRUE(test_vec.size() == original_vec.size());
  EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
  EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(MergeSortTests, RandomSort) {
  vector<std::size_t> vec_sizes = {10, 100, 1000};
  for (auto vec_size : vec_sizes) {
    for (int i = 0; i < 3; ++i) {
      vector<int> test_vec{get_random_vector<int>(vec_size)};
      vector<int> original_vec = test_vec;

      merge_sort(begin(test_vec), end(test_vec));

      EXPECT_TRUE(test_vec.size() == original_vec.size());
      EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
      EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
    }
  }
}

// bubble sort

class BubbleSortTests : public testing::Test {
  void SetUp() override { std::srand(static_cast<unsigned>(std::time(0))); }
};

TEST_F(BubbleSortTests, HandleEmptyInput) {
  vector<int> test_vec;
  vector<int> original_vec = test_vec;

  bubble_sort(begin(test_vec), end(test_vec));

  EXPECT_TRUE(test_vec.size() == original_vec.size());
  EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
  EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(BubbleSortTests, HandleOneElementInput) {
  vector<int> test_vec{1};
  vector<int> original_vec = test_vec;

  bubble_sort(begin(test_vec), end(test_vec));

  EXPECT_TRUE(test_vec.size() == original_vec.size());
  EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
  EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(BubbleSortTests, SimpleSort) {
  vector<int> test_vec{1, 3, 5, 7, 9, 2, 4, 6, 8, 0};
  vector<int> original_vec = test_vec;

  bubble_sort(begin(test_vec), end(test_vec));

  EXPECT_TRUE(test_vec.size() == original_vec.size());
  EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
  EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(BubbleSortTests, AlreadySorted) {
  vector<int> test_vec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  vector<int> original_vec = test_vec;

  bubble_sort(begin(test_vec), end(test_vec));

  EXPECT_TRUE(test_vec.size() == original_vec.size());
  EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
  EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(BubbleSortTests, SortedInversely) {
  vector<int> test_vec{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  vector<int> original_vec = test_vec;

  bubble_sort(begin(test_vec), end(test_vec));

  EXPECT_TRUE(test_vec.size() == original_vec.size());
  EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
  EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(BubbleSortTests, RandomSort) {
  vector<std::size_t> vec_sizes = {10, 100, 1000};
  for (auto vec_size : vec_sizes) {
    for (int i = 0; i < 3; ++i) {
      vector<int> test_vec{get_random_vector<int>(vec_size)};
      vector<int> original_vec = test_vec;

      bubble_sort(begin(test_vec), end(test_vec));

      EXPECT_TRUE(test_vec.size() == original_vec.size());
      EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
      EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
    }
  }
}
