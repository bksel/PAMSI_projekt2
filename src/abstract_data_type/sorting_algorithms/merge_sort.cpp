//
// Created by ksel on 12/04/24.
//

#ifndef MINIPROJEKT2_SRC_SORTING_ALGORITHMS_MERGE_SORT_CPP_
#define MINIPROJEKT2_SRC_SORTING_ALGORITHMS_MERGE_SORT_CPP_

#include "../vector/vector.cpp"
#include "sorting_utils.h"

namespace adt {



template<typename T>
void merge_sort(typename vector<T>::Iterator begin, typename vector<T>::Iterator end, comparator<T> compare) {

  u_int length = end - begin;

  if (length <= 2) {

	if (*end < *begin) {
	  std::swap(*end, *begin);
	}
	return;
  }

  u_int middle = length / 2;

  Iterator<T> middle_left {begin.get_raw_pointer()+middle};
  Iterator<T> middle_right {begin.get_raw_pointer()+middle+1};

  merge_sort(begin, middle_left, compare);
  merge_sort(middle_right, end, compare);


  while (begin != middle_left) {

	if (compare(*begin, *middle_right)) {
	  
	}




  }






}
}

#endif