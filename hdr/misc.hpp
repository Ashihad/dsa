#pragma once

namespace custom {

template<typename T>
void swap(T& first, T& second) noexcept {
  T tmp = first;
  first = second;
  second = tmp;
}

}  // namespace custom
