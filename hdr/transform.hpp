#pragma once

#include "misc.hpp"

namespace custom {

template<typename T>
void reverse(T* begin, T* end) {
  for (auto f_iter = begin, b_iter = end - 1; f_iter != b_iter;
       f_iter++, b_iter--) {
    swap(*f_iter, *b_iter);
  }
}

}  // namespace custom
