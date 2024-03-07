#include <gtest/gtest.h>
#include "searching.hpp"
#include "misc.hpp"

#include <cstdlib>
#include <ctime>
#include <cmath>

class LinearSearchTests: public testing::Test {
    void SetUp() override {
        std::srand( static_cast<unsigned>( std::time(0) ) );
    }
};

std::size_t insert_value_randomly(std::vector<int>& vec, int value) {
    std::replace(begin(vec), end(vec), value, 69);
    std::size_t random_index { static_cast<std::size_t>(std::rand()) % vec.size() };
    vec[random_index] = value;
    return random_index;
}

TEST_F(LinearSearchTests, HandleEmptyInput) {
    std::vector<int> empty_vec;

    EXPECT_NO_THROW(linear_search(empty_vec, 0));
    EXPECT_EQ(empty_vec.size(), 0);
}

TEST_F(LinearSearchTests, SimpleSearch) {
    std::vector<int> test_vec { 1, 3, 5, 7, 9, 2, 4, 6, 8 };

    std::optional<int> ret { linear_search(test_vec, 3) }; 

    EXPECT_EQ(ret.has_value(), true);
    EXPECT_EQ(ret.value(), 1);
}

TEST_F(LinearSearchTests, RandomSearchValueInserted) {
    for (int vec_size: {10, 100, 1000, 10000, 100000}) {
        for( int i = 0; i < 10; ++i ) {
            std::vector<int> test_vec { get_random_vector(vec_size) };
            int random_value { std::rand() % 10*vec_size };
            // remove random values from vector, replace with value impossible to get randomly
            std::replace(begin(test_vec), end(test_vec), random_value, 10*vec_size+1);
            std::size_t correct_index { insert_value_randomly(test_vec, random_value) };
            std::optional<int> ret { linear_search(test_vec, random_value) }; 
            EXPECT_EQ(ret.has_value(), true);
            if (ret.has_value()) {
                EXPECT_EQ(ret.value(), correct_index);
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
            std::optional<int> ret { linear_search(test_vec, random_value) };
            EXPECT_EQ(ret.has_value(), false);
        }
    }
}
