//
// Created by ksel on 12/04/24.
//

#ifndef MINIPROJEKT2_SRC_ABSTRACT_DATA_TYPE_SORTING_ALGORITHMS_SORTING_UTILS_H_
#define MINIPROJEKT2_SRC_ABSTRACT_DATA_TYPE_SORTING_ALGORITHMS_SORTING_UTILS_H_

#include "../vector/vector.cpp"

namespace adt {

template<typename T>
using comparator = bool (*)(const T&, const T&);

template<typename T>
using Iterator = typename vector<T>::Iterator;

template<typename T>
using hasher = u_int (*)(const T&);

template<typename T>
bool
is_sorted(vector<T> v, comparator<T> compare)
{
  for (auto it = v.begin(); it != v.end() - 1; ++it) {
    // since comparator might be <, then if elements next to each other are equal, it is still sorted
    // so it must be checked if element before is greater than element after
    if (compare(*(it+1), *(it))) {
      fmt::print("Element at id {} is greater than element at id {}.\n", it - v.begin(), it + 1 - v.begin());
      return false;
    }
  }
  return true;
}

} // namespace adt

#endif // MINIPROJEKT2_SRC_ABSTRACT_DATA_TYPE_SORTING_ALGORITHMS_SORTING_UTILS_H_
