#include "misc.hpp"

#include <iostream>
#include <iomanip>

namespace custom
{
  std::string format(const char* fmt, ...)
  {
    constexpr size_t BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];

    va_list args;
    va_start(args, fmt);
    std::vsnprintf(buffer, BUFFER_SIZE, fmt, args);
    va_end(args);

    return std::string(buffer);
  }
}
