#pragma once

#include <utility>
#include <iterator>

using std::swap;

namespace custom
{

template<typename T>
void reverse(T* begin, T* end)
{
  if (std::distance(begin, end) <= 1) return;
  end--;
  while (begin < end)
  {
    std::swap(*(begin++), *(end--));
  }
}

}