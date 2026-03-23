#include "vector.hpp"

using ::custom::vector;

template<typename T>
vector<T> get_random_vector(const std::size_t size) {
  vector<T> output(0);
  for (std::size_t i = 0; i < size; ++i) {
    output.push_back(static_cast<T>(std::rand()) % static_cast<T>((10 * size)));
  }
  return output;
}

template<typename T>
T* insert_value_randomly(T* first, T* last, T value) {
  std::size_t random_index{
      static_cast<std::size_t>(std::rand()) %
      static_cast<std::size_t>(std::distance(first, last))};
  first[random_index] = value;
  return first + random_index;
}

template<typename T>
void find_and_replace(T* begin, T* end, T searched, T replaced) {
  for (auto iter = begin; iter != end; ++iter) {
    if (*iter == searched) *iter = replaced;
  }
}
