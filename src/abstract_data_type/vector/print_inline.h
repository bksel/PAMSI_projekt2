//
// Created by ksel on 12/04/24.
//

#ifndef MINIPROJEKT2_SRC_ABSTRACT_DATA_TYPE_VECTOR_PRINT_INLINE_H_
#define MINIPROJEKT2_SRC_ABSTRACT_DATA_TYPE_VECTOR_PRINT_INLINE_H_

#include "vector.cpp"
#include <iostream>

namespace adt {

// Print the vector

template<typename T>
void
print_inline(vector<T>& v)
{
  std::cout << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    std::cout << *it << ", ";
  }
  std::cout << "]\n";
}

}

#endif // MINIPROJEKT2_SRC_ABSTRACT_DATA_TYPE_VECTOR_PRINT_INLINE_H_
