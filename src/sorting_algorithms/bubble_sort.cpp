//
// Created by ksel on 09/04/24.
//

#ifndef MINIPROJEKT1_SRC_SORTING_ALGORITHMS_BUBBLE_SORT_CPP_
#define MINIPROJEKT1_SRC_SORTING_ALGORITHMS_BUBBLE_SORT_CPP_

#include "../abstract_data_type/vector/vector.cpp"

namespace adt {

template<typename T>
void bubble_sort(vector<T> &v, bool (*compare)(const T &a, const T &b)) {
  for (u_int i = 0; i < v.size(); i++) {
	for (u_int j = 0; j < v.size() - i - 1; j++) {
	  if (compare(v[j + 1], v[j])) {
		std::swap(v[j], v[j + 1]);
	  }
	}
  }
}

template<typename T>
void bubble_sort(typename vector<T>::Iterator begin,
				 typename vector<T>::Iterator end,
				 bool (*compare)(const T &a, const T &b)) {
  for (auto i = begin; i != end; ++i) {
	for (auto j = begin; j != end - 1; ++j) {
	  if (compare(*(j + 1), *j)) {
		std::swap(*j, *(j + 1));
	  }
	}
  }
}

}

#endif