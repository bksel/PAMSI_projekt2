//
// Created by ksel on 09/04/24.
//

#ifndef MINIPROJEKT1_SRC_SORTING_ALGORITHMS_BUBBLE_SORT_CPP_
#define MINIPROJEKT1_SRC_SORTING_ALGORITHMS_BUBBLE_SORT_CPP_

#include "../vector/vector.cpp"
#include "sorting_utils.h"

namespace adt {

template<typename T>
void bubble_sort(Iterator<T> begin,
				 Iterator<T> end,
				 comparator<T> compare) {

  for (auto i = begin; i != end; ++i) {
	for (auto j = begin; j != end - 1; ++j) {
	  if (compare(*(j + 1), *j)) {
		std::swap(*j, *(j + 1));
	  }
	}
  }
}

template<typename T>
void bubble_sort(vector<T> &v,
				 comparator<T> compare) {
  bubble_sort(v.begin(), v.end(), compare);
}

}

#endif