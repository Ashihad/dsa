// #include "subcontainers.hpp"

// #include <tuple>
// #include <limits>
// #include <iostream>

// static 
// std::tuple<std::vector<int>::const_iterator, std::vector<int>::const_iterator, int> 
// find_max_crossing_subcontainer( std::vector<int>::const_iterator left, 
//                                 std::vector<int>::const_iterator middle, 
//                                 std::vector<int>::const_iterator right) {
//     int left_current_sum {};
//     int max_left_sum { std::numeric_limits<int>::min() };

//     auto left_iter { make_reverse_iterator(middle-1) };
//     auto reverse_left_end { make_reverse_iterator(left) };
//     auto leftmost_iter {left_iter};
//     for (; left_iter != reverse_left_end; ++left_iter) {
//         left_current_sum += *left_iter;
//         if (left_current_sum > max_left_sum) {
//             max_left_sum = left_current_sum;
//             leftmost_iter = left_iter;
//         }
//     }

//     int right_current_sum {};
//     int max_right_sum { std::numeric_limits<int>::min() };
    
//     auto rightmost_iter {middle};
//     for (auto right_iter = middle; right_iter != right; ++right_iter) {
//         right_current_sum += *right_iter;
//         if (right_current_sum > max_right_sum) {
//             max_right_sum = right_current_sum;
//             rightmost_iter = right_iter;
//         }
//     }
//     return std::make_tuple(leftmost_iter.base(), rightmost_iter, max_left_sum+max_right_sum);
// }

// std::tuple<std::vector<int>::const_iterator, std::vector<int>::const_iterator, int> find_max_subcontainer(std::vector<int>::const_iterator first, std::vector<int>::const_iterator last) {
//     if (std::distance(first, last) < 1) { std::cout << "distance less than two" << std::endl; return std::make_tuple(first, last, 0);} 
//     if (std::distance(first, last) <= 2) {std::cout << "distance equals two" << std::endl; return std::make_tuple(first, last, *first);} ;

//     std::vector<int>::const_iterator middle { first };
//     std::advance(middle, std::distance(first, last)/2);

//     auto left_tuple { find_max_subcontainer(first, middle) };
//     auto right_tuple { find_max_subcontainer(middle, last) };
//     auto cross_tuple { find_max_crossing_subcontainer(first, middle, last) };

//     if (std::get<2>(left_tuple) >= std::get<2>(right_tuple) 
//         && std::get<2>(left_tuple) >= std::get<2>(cross_tuple))
//         return left_tuple;
//     else if (std::get<2>(right_tuple) >= std::get<2>(left_tuple) 
//             && std::get<2>(right_tuple) >= std::get<2>(cross_tuple)) 
//             return right_tuple;
//     else return cross_tuple;
// }
