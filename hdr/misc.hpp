#pragma once

namespace custom {

template<typename T>
void swap(T& first, T& second) noexcept {
  T tmp = first;
  first = second;
  second = tmp;
}

template<typename T>
void reverse(T* begin, T* end) {
  if (std::distance(begin, end) == 0) return;
  T* middle{begin + ((end - begin + 1) / 2)};
  for (T *f_iter{begin}, *b_iter{end - 1}; f_iter != middle;
       f_iter++, b_iter--) {
    std::swap(*f_iter, *b_iter);
  }
}

}  // namespace custom
