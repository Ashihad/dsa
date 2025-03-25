// #include <gtest/gtest.h>
// #include "subcontainers.hpp"
// #include "misc.hpp"

// #include <algorithm>

// // find_max_subcontainer

// class FindMaxSubcontainerTests: public testing::Test {};

// TEST_F(FindMaxSubcontainerTests, HandleEmptyInput) {
//     std::vector<int> test_vec;

//     auto result { find_max_subcontainer(cbegin(test_vec), cend(test_vec)) };

//     EXPECT_TRUE(std::distance(cbegin(test_vec), std::get<0>(result)) == 0);
//     EXPECT_TRUE(std::distance(std::get<0>(result), cend(test_vec)) == 0);
//     EXPECT_TRUE(std::get<2>(result) == 0);
// }

// TEST_F(FindMaxSubcontainerTests, HandleOneElementInput) {
//     std::vector<int> test_vec { 42 };

//     auto result { find_max_subcontainer(cbegin(test_vec), cend(test_vec)) };

//     std::cout << std::get<2>(result) << std::endl;

//     EXPECT_TRUE(std::distance(cbegin(test_vec), std::get<0>(result)) == 0);
//     EXPECT_TRUE(std::distance(std::get<0>(result), cend(test_vec)) == 1);
//     EXPECT_TRUE(std::get<2>(result) == 42);
// }

// TEST_F(FindMaxSubcontainerTests, BasicTest) {
//     std::vector<int> test_vec { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };

//     auto result { find_max_subcontainer(cbegin(test_vec), cend(test_vec)) };

//     std::cout << std::distance(cbegin(test_vec), std::get<0>(result)) << std::endl;
//     EXPECT_TRUE(std::distance(cbegin(test_vec), std::get<0>(result)) == 7);
//     std::cout << std::distance(std::get<0>(result), cend(test_vec)) << std::endl;
//     EXPECT_TRUE(std::distance(std::get<0>(result), cend(test_vec)) == 5);
//     std::cout << std::get<2>(result) << std::endl;
//     EXPECT_TRUE(std::get<2>(result) == 43);
// }
