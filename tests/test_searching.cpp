#include <gtest/gtest.h>
#include "searching.hpp"
#include "misc.hpp"

#include <cstdlib>
#include <ctime>
#include <cmath>

static std::vector<int>::iterator insert_value_randomly(std::vector<int>::iterator first, std::vector<int>::iterator last, int value) {
    std::size_t random_index { static_cast<std::size_t>(std::rand()) % static_cast<std::size_t>(std::distance(first, last)) };
    std::advance(first, random_index);
    *first = value;
    return first;
}

class LinearSearchTests: public testing::Test {
    void SetUp() override {
        std::srand( static_cast<unsigned>( std::time(0) ) );
    }
};

TEST_F(LinearSearchTests, HandleEmptyInput) {
    std::vector<int> test_vec;

    std::optional<std::vector<int>::iterator> ret { linear_search(begin(test_vec), end(test_vec), 0) };
    EXPECT_EQ(ret.has_value(), false);
}

TEST_F(LinearSearchTests, SimpleSearch) {
    std::vector<int> test_vec { 1, 3, 5, 7, 9, 2, 4, 6, 8 };

    std::optional<std::vector<int>::iterator> ret { linear_search(begin(test_vec), end(test_vec), 3) };

    EXPECT_EQ(ret.has_value(), true);
    if (ret.has_value()) {
        EXPECT_EQ(std::distance(begin(test_vec), ret.value()), std::distance(begin(test_vec), std::next(begin(test_vec))));
    }
}

TEST_F(LinearSearchTests, RandomSearchValueInserted) {
    for (int vec_size: {10, 100, 1000, 10000, 100000}) {
        for( int i = 0; i < 10; ++i ) {
            std::vector<int> test_vec { get_random_vector(vec_size) };
            int random_value { std::rand() % 10*vec_size };
            // remove random values from vector, replace with value impossible to get randomly
            std::replace(begin(test_vec), end(test_vec), random_value, 10*vec_size+1);
            auto correct_index { insert_value_randomly(begin(test_vec), end(test_vec), random_value) };

            std::optional<std::vector<int>::iterator> ret { linear_search(begin(test_vec), end(test_vec), random_value) };
            EXPECT_EQ(ret.has_value(), true);
            if (ret.has_value()) {
                EXPECT_EQ(std::distance(begin(test_vec), ret.value()), std::distance(begin(test_vec), correct_index));
            }
        }
    }
}

TEST_F(LinearSearchTests, RandomSearchValueNotInserted) {
    for (int vec_size: {10, 100, 1000, 10000, 100000}) {
        for( int i = 0; i < 10; ++i ) {
            std::vector<int> test_vec { get_random_vector(vec_size) };
            int random_value { std::rand() % 10*vec_size };
            // remove random values from vector, replace with value impossible to get randomly
            std::replace(begin(test_vec), end(test_vec), random_value, 10*vec_size+1);

            std::optional<std::vector<int>::iterator> ret { linear_search(begin(test_vec), end(test_vec), random_value) };
            EXPECT_EQ(ret.has_value(), false);
        }
    }
}

// binary_search

class BinarySearchtests: public testing::Test {
    void SetUp() override {
        std::srand( static_cast<unsigned>( std::time(0) ) );
    }
};

TEST_F(BinarySearchtests, HandleEmptyInput) {
    std::vector<int> test_vec;

    std::optional<std::vector<int>::iterator> ret { linear_search(begin(test_vec), end(test_vec), 0) };
    EXPECT_EQ(ret.has_value(), false);
}

TEST_F(BinarySearchtests, SimpleSearchValueExists) {
    std::vector<int> test_vec { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    std::optional<std::vector<int>::iterator> ret { linear_search(begin(test_vec), end(test_vec), 3) };

    EXPECT_EQ(ret.has_value(), true);
    if (ret.has_value()) {
        EXPECT_EQ(std::distance(begin(test_vec), ret.value()), std::distance(begin(test_vec), std::find(begin(test_vec), end(test_vec), 3)));
    }
}

TEST_F(BinarySearchtests, SimpleSearchValueNotExists) {
    std::vector<int> test_vec { 1, 2, 4, 5, 6, 7, 8, 9 };

    std::optional<std::vector<int>::iterator> ret { linear_search(begin(test_vec), end(test_vec), 3) };

    EXPECT_EQ(ret.has_value(), false);
}

TEST_F(BinarySearchtests, RandomSearchValueInserted) {
    for (int vec_size: {10, 100, 1000, 10000}) {
        for( int i = 0; i < 10; ++i ) {
            std::vector<int> test_vec { get_random_vector(vec_size) };
            int random_value { std::rand() % 10*vec_size };
            // remove random values from vector, replace with value impossible to get randomly
            std::replace(begin(test_vec), end(test_vec), random_value, 10*vec_size+1);
            insert_value_randomly(begin(test_vec), end(test_vec), random_value);
            // vector must be sorted for this algo
            std::sort(begin(test_vec), end(test_vec));

            std::optional<std::vector<int>::iterator> ret { binary_search(begin(test_vec), end(test_vec), random_value) };
            EXPECT_EQ(ret.has_value(), true);
            if (ret.has_value()) {
                EXPECT_EQ(std::distance(begin(test_vec), ret.value()), std::distance(begin(test_vec), std::find(begin(test_vec), end(test_vec), random_value)));
            }
        }
    }
}

TEST_F(BinarySearchtests, RandomSearchValueNotInserted) {
    for (int vec_size: {10, 100, 1000, 10000}) {
        for( int i = 0; i < 10; ++i ) {
            std::vector<int> test_vec { get_random_vector(vec_size) };
            int random_value { std::rand() % 10*vec_size };
            // remove random values from vector, replace with value impossible to get randomly
            std::replace(begin(test_vec), end(test_vec), random_value, 10*vec_size+1);
            // vector must be sorted for this algo
            std::sort(begin(test_vec), end(test_vec));

            std::optional<std::vector<int>::iterator> ret { binary_search(begin(test_vec), end(test_vec), random_value) };
            EXPECT_EQ(ret.has_value(), false);
        }
    }
}
