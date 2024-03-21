#include <gtest/gtest.h>
#include "sorting.hpp"
#include "misc.hpp"

#include <algorithm>

// insertion_sort

class InsertionSortTests: public testing::Test {
    void SetUp() override {
        std::srand( static_cast<unsigned>( std::time(0) ) );
    }
};

TEST_F(InsertionSortTests, HandleEmptyInput) {
    std::vector<int> test_vec;
    std::vector<int> original_vec = test_vec;

    insertion_sort(begin(test_vec), end(test_vec));

    EXPECT_TRUE(test_vec.size() == original_vec.size());
    EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
    EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(InsertionSortTests, HandleOneElementInput) {
    std::vector<int> test_vec { 1 };
    std::vector<int> original_vec = test_vec;

    insertion_sort(begin(test_vec), end(test_vec));

    EXPECT_TRUE(test_vec.size() == original_vec.size());
    EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
    EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(InsertionSortTests, SimpleSort) {
    std::vector<int> test_vec { 1, 3, 5, 7, 9, 2, 4, 6, 8, 0 };
    std::vector<int> original_vec = test_vec;

    insertion_sort(begin(test_vec), end(test_vec));

    EXPECT_TRUE(test_vec.size() == original_vec.size());
    EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
    EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(InsertionSortTests, AlreadySorted) {
    std::vector<int> test_vec { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::vector<int> original_vec = test_vec;

    insertion_sort(begin(test_vec), end(test_vec));

    EXPECT_TRUE(test_vec.size() == original_vec.size());
    EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
    EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(InsertionSortTests, SortedInversely) {
    std::vector<int> test_vec { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
    std::vector<int> original_vec = test_vec;

    insertion_sort(begin(test_vec), end(test_vec));

    EXPECT_TRUE(test_vec.size() == original_vec.size());
    EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
    EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(InsertionSortTests, RandomSort) {
    for (int vec_size: {10, 100, 1000}) {
        for( int i = 0; i < 3; ++i ) {
            std::vector<int> test_vec { get_random_vector(vec_size) };
            std::vector<int> original_vec = test_vec;

            selection_sort(begin(test_vec), end(test_vec));

            EXPECT_TRUE(test_vec.size() == original_vec.size());
            EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
            EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
        }
    }
}

// selection sort

class SelectionSortTests: public testing::Test {
    void SetUp() override {
        std::srand( static_cast<unsigned>( std::time(0) ) );
    }
};

TEST_F(SelectionSortTests, HandleEmptyInput) {
    std::vector<int> test_vec;
    std::vector<int> original_vec = test_vec;

    selection_sort(begin(test_vec), end(test_vec));

    EXPECT_TRUE(test_vec.size() == original_vec.size());
    EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
    EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(SelectionSortTests, HandleOneElementInput) {
    std::vector<int> test_vec { 1 };
    std::vector<int> original_vec = test_vec;

    selection_sort(begin(test_vec), end(test_vec));

    EXPECT_TRUE(test_vec.size() == original_vec.size());
    EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
    EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(SelectionSortTests, SimpleSort) {
    std::vector<int> test_vec { 1, 3, 5, 7, 9, 2, 4, 6, 8, 0 };
    std::vector<int> original_vec = test_vec;

    selection_sort(begin(test_vec), end(test_vec));

    EXPECT_TRUE(test_vec.size() == original_vec.size());
    EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
    EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(SelectionSortTests, AlreadySorted) {
    std::vector<int> test_vec { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::vector<int> original_vec = test_vec;

    selection_sort(begin(test_vec), end(test_vec));

    EXPECT_TRUE(test_vec.size() == original_vec.size());
    EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
    EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(SelectionSortTests, SortedInversely) {
    std::vector<int> test_vec { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
    std::vector<int> original_vec = test_vec;

    selection_sort(begin(test_vec), end(test_vec));

    EXPECT_TRUE(test_vec.size() == original_vec.size());
    EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
    EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(SelectionSortTests, RandomSort) {
    for (int vec_size: {10, 100, 1000}) {
        for( int i = 0; i < 3; ++i ) {
            std::vector<int> test_vec { get_random_vector(vec_size) };
            std::vector<int> original_vec = test_vec;

            selection_sort(begin(test_vec), end(test_vec));

            EXPECT_TRUE(test_vec.size() == original_vec.size());
            EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
            EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
        }
    }
}

// merge sort

class MergeSortTests: public testing::Test {
    void SetUp() override {
        std::srand( static_cast<unsigned>( std::time(0) ) );
    }
};

TEST_F(MergeSortTests, HandleEmptyInput) {
    std::vector<int> test_vec;
    std::vector<int> original_vec = test_vec;

    merge_sort(begin(test_vec), end(test_vec));

    EXPECT_TRUE(test_vec.size() == original_vec.size());
    EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
    EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(MergeSortTests, HandleOneElementInput) {
    std::vector<int> test_vec { 1 };
    std::vector<int> original_vec = test_vec;

    merge_sort(begin(test_vec), end(test_vec));

    EXPECT_TRUE(test_vec.size() == original_vec.size());
    EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
    EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(MergeSortTests, SimpleSort) {
    std::vector<int> test_vec { 1, 3, 5, 7, 9, 2, 4, 6, 8, 0 };
    std::vector<int> original_vec = test_vec;

    merge_sort(begin(test_vec), end(test_vec));

    EXPECT_TRUE(test_vec.size() == original_vec.size());
    EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
    EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(MergeSortTests, AlreadySorted) {
    std::vector<int> test_vec { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::vector<int> original_vec = test_vec;

    merge_sort(begin(test_vec), end(test_vec));

    EXPECT_TRUE(test_vec.size() == original_vec.size());
    EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
    EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(MergeSortTests, SortedInversely) {
    std::vector<int> test_vec { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
    std::vector<int> original_vec = test_vec;

    merge_sort(begin(test_vec), end(test_vec));

    EXPECT_TRUE(test_vec.size() == original_vec.size());
    EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
    EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(MergeSortTests, RandomSort) {
    for (int vec_size: {10, 100, 1000}) {
        for( int i = 0; i < 3; ++i ) {
            std::vector<int> test_vec { get_random_vector(vec_size) };
            std::vector<int> original_vec = test_vec;

            merge_sort(begin(test_vec), end(test_vec));

            EXPECT_TRUE(test_vec.size() == original_vec.size());
            EXPECT_TRUE(std::is_permutation(begin(test_vec), end(test_vec), begin(original_vec)));
            EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
        }
    }
}
