//
// Created by ksel on 13/04/24.
//

#ifndef MINIPROJEKT2_SRC_ABSTRACT_DATA_TYPE_SORTING_ALGORITHMS_MERGE_SORT_H_
#define MINIPROJEKT2_SRC_ABSTRACT_DATA_TYPE_SORTING_ALGORITHMS_MERGE_SORT_H_

#include <memory>

#include "../vector/vector.h"
#include "sorting_utils.h"

namespace adt {

/*
 * Function that sorts a vector using merge sort.
 * */
template<typename T>
void
merge_sort(typename vector<T>::Iterator begin,
           typename vector<T>::Iterator end,
           comparator<T> compare);

template<typename T>
void
merge_sort_parallel(typename vector<T>::Iterator begin,
           typename vector<T>::Iterator end,
           comparator<T> compare);

namespace _merge_sort {

/*
 * In this implementation, the sorting isn't done in place, but rather a new
 * vector is created and returned.
 * */
template<typename T>
std::unique_ptr<vector<T>>
split_and_sort(std::unique_ptr<vector<T>>& v, comparator<T> compare);

template<typename T>
void
merge(Iterator<T> target_begin,
      Iterator<T> target_end,
      std::unique_ptr<vector<T>>& left,
      std::unique_ptr<vector<T>>& right,
      comparator<T> compare);

} // namespace __merge_sort

} // namespace adt

#endif // MINIPROJEKT2_SRC_ABSTRACT_DATA_TYPE_SORTING_ALGORITHMS_MERGE_SORT_H_
