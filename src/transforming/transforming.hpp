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
  T* middle{begin + ((end)-begin)/2};
  for (T* iter{begin}; iter != middle; ++iter)
  {
    swap(*iter, *(end - (iter - begin) - 1));
  }
}

}