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
    std::vector<int> empty_vec;

    EXPECT_NO_THROW(insertion_sort(empty_vec));
    EXPECT_EQ(empty_vec.size(), 0);
}

TEST_F(InsertionSortTests, SimpleSort) {
    std::vector<int> test_vec { 1, 3, 5, 7, 9, 2, 4, 6, 8 };

    insertion_sort(test_vec); 

    EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(InsertionSortTests, AlreadySorted) {
    std::vector<int> test_vec { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    insertion_sort(test_vec); 

    EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(InsertionSortTests, SortedInversely) {
    std::vector<int> test_vec { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

    insertion_sort(test_vec); 

    EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(InsertionSortTests, RandomSort) {
    for (int vec_size: {10, 100, 1000}) {
        for( int i = 0; i < 10; ++i ) {
            std::vector<int> test_vec { get_random_vector(vec_size) };
              insertion_sort(test_vec); 
              EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
        }
    }
}

// seelction sort

class SelectionSortTests: public testing::Test {
    void SetUp() override {
        std::srand( static_cast<unsigned>( std::time(0) ) );
    }
};

TEST_F(SelectionSortTests, HandleEmptyInput) {
    std::vector<int> empty_vec;

    EXPECT_NO_THROW(selection_sort(empty_vec));
    EXPECT_EQ(empty_vec.size(), 0);
}

TEST_F(SelectionSortTests, SimpleSort) {
    std::vector<int> test_vec { 1, 3, 5, 7, 9, 2, 4, 6, 8 };

    selection_sort(test_vec); 

    EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(SelectionSortTests, AlreadySorted) {
    std::vector<int> test_vec { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    selection_sort(test_vec); 

    EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(SelectionSortTests, SortedInversely) {
    std::vector<int> test_vec { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

    selection_sort(test_vec); 

    EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
}

TEST_F(SelectionSortTests, RandomSort) {
    for (int vec_size: {10, 100, 1000}) {
        for( int i = 0; i < 10; ++i ) {
            std::vector<int> test_vec { get_random_vector(vec_size) };
              selection_sort(test_vec); 
              EXPECT_TRUE(std::is_sorted(begin(test_vec), end(test_vec)));
        }
    }
}
