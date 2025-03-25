#pragma once

#include <utility>

using std::swap;

namespace custom
{

template<typename T>
void reverse(T* begin, T* end)
{
  T* middle{begin + ((end-1)-begin)/2};
  for (T* iter{begin}; iter != middle; ++iter)
  {
    T tmp{*iter};
    *iter = *(end-iter-1);
    *(end-iter-1) = tmp;
    // swap(*iter, *static_cast<T*>(end-iter-1));
  }
}

}