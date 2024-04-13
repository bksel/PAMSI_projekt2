//
// Created by ksel on 12/04/24.
//

#ifndef MINIPROJEKT2_SRC_ABSTRACT_DATA_TYPE_VECTOR_COPY_H_
#define MINIPROJEKT2_SRC_ABSTRACT_DATA_TYPE_VECTOR_COPY_H_

#include "vector.cpp"
#include <exception>

namespace adt {

class CopyIteratorException : public std::exception {
 public:
  [[nodiscard]] const char *what() const noexcept override {
	return "CopyIteratorException: left iterator is greater than right iterator.";
  }
};

template<typename T>
using Iterator = typename vector<T>::Iterator;

template<typename T>
void copy(Iterator<T> begin, Iterator<T> end, Iterator<T> dest) {

  if (begin.get_raw_pointer() > end.get_raw_pointer()) {
	throw CopyIteratorException();
  }

  while (begin != end) {
	if (dest == end) {
	  break;
	}
	*dest = *begin;
	++begin;
	++dest;
  }

}

template<typename T>
vector<T> get_copy(Iterator<T> begin, Iterator<T> end) {

  if (begin.get_raw_pointer() > end.get_raw_pointer()) {
	throw CopyIteratorException();
  }
  vector<T> v{};
  v.reserve(end - begin + 10);
  for (auto it = begin; it != end; ++it) {
	v.push_back(*it);
  }
  return v;
}

template<typename T>
vector<T> get_copy(vector<T> &v) {
  return get_copy<T>(v.begin(), v.end());
}



} // namespace adt

#endif //MINIPROJEKT2_SRC_ABSTRACT_DATA_TYPE_VECTOR_COPY_H_
