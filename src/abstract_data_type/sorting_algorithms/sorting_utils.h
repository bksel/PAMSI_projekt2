//
// Created by ksel on 12/04/24.
//

#ifndef MINIPROJEKT2_SRC_ABSTRACT_DATA_TYPE_SORTING_ALGORITHMS_SORTING_UTILS_H_
#define MINIPROJEKT2_SRC_ABSTRACT_DATA_TYPE_SORTING_ALGORITHMS_SORTING_UTILS_H_

#include "../vector/vector.cpp"

namespace adt {

template<typename T>
using comparator = bool (*)(const T &, const T &);

template<typename T>
using Iterator = typename vector<T>::Iterator;


} // namespace adt

#endif //MINIPROJEKT2_SRC_ABSTRACT_DATA_TYPE_SORTING_ALGORITHMS_SORTING_UTILS_H_
