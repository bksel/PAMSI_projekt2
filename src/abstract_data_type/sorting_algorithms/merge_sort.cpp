//
// Created by ksel on 12/04/24.
//

#ifndef MINIPROJEKT2_SRC_ABSTRACT_DATA_TYPE_SORTING_ALGORITHMS_MERGE_SORT_C_
#define MINIPROJEKT2_SRC_ABSTRACT_DATA_TYPE_SORTING_ALGORITHMS_MERGE_SORT_C_

#include "merge_sort.h"

#include <future>
#include <thread>

#include "bubble_sort.cpp"

namespace adt {

template<typename T>
void
merge_sort(typename vector<T>::Iterator begin,
           typename vector<T>::Iterator end,
           comparator<T> compare)
{
  u_int length = end - begin;

  if (length <= 4) {
    // trivial case
    bubble_sort(begin, end, compare);
    return;
  }

  u_int middle_index = length / 2;

  Iterator<T> middle{ begin.get_raw_pointer() + middle_index };

  std::unique_ptr<vector<T>> left = std::make_unique<vector<T>>();
  copy<T>(begin, middle, *left);
  std::unique_ptr<vector<T>> right = std::make_unique<vector<T>>();
  copy<T>(middle, end, *right);

  left = _merge_sort::split_and_sort(left, compare);
  right = _merge_sort::split_and_sort(right, compare);

  _merge_sort::merge(begin, end, left, right, compare);
}

template<typename T>
void
merge_sort_parallel(typename vector<T>::Iterator begin,
                    typename vector<T>::Iterator end,
                    comparator<T> compare)
{
  u_int threads = std::thread::hardware_concurrency();

  if (threads < 2) {
    merge_sort(begin, end, compare);
    return;
  }

  u_int length = end - begin;

  if (length <= 4) {
    // trivial case
    bubble_sort(begin, end, compare);
    return;
  }

  u_int available_threads_left = threads / 2;
  u_int available_threads_right = threads - available_threads_left;

  u_int middle_index = length / 2;

  Iterator<T> middle{ begin.get_raw_pointer() + middle_index };

  std::unique_ptr<vector<T>> left = std::make_unique<vector<T>>();
  copy<T>(begin, middle, *left);
  std::unique_ptr<vector<T>> right = std::make_unique<vector<T>>();
  copy<T>(middle, end, *right);

  left = _merge_sort::go_one_deeper(left, compare, available_threads_left);
  right = _merge_sort::go_one_deeper(right, compare, available_threads_right);

  _merge_sort::merge(begin, end, left, right, compare);
}

namespace _merge_sort {

class ZeroSizeVectorException : public std::exception
{
public:
  [[nodiscard]] const char* what() const noexcept override
  {
    return "ZeroSizeVectorException: The vector has size 0.";
  }
};

template<typename T>
std::unique_ptr<vector<T>>
split_and_sort(std::unique_ptr<vector<T>>& v, comparator<T> compare)
{
  if (v->size() == 3) {
    bubble_sort<T>(v->begin(), v->end(), compare);
    return std::move(v);
  }

  if (v->size() == 2) {
    if (compare(v->at(1), v->at(0))) {
      std::swap(v->at(0), v->at(1));
    }
    return std::move(v);
  }

  if (v->size() == 1) {
    return std::move(v);
  }

  if (v->size() == 0) {
    throw ZeroSizeVectorException();
  }

  u_int middle_index = v->size() / 2;
  Iterator<T> middle{ v->begin().get_raw_pointer() + middle_index };

  std::unique_ptr<vector<T>> left = std::make_unique<vector<T>>();
  copy<T>(v->begin(), middle, *left);
  std::unique_ptr<vector<T>> right = std::make_unique<vector<T>>();
  copy<T>(middle, v->end(), *right);

  left = split_and_sort(left, compare);
  right = split_and_sort(right, compare);

  merge(v->begin(), v->end(), left, right, compare);
  // left and right are lost

  return std::move(v);
}

template<typename T>
void
merge(Iterator<T> target_begin,
      Iterator<T> target_end,
      std::unique_ptr<vector<T>>& left,
      std::unique_ptr<vector<T>>& right,
      comparator<T> compare)
{
  auto l = left->begin();
  auto r = right->begin();

  auto l_end = left->end();
  auto r_end = right->end();

  for (auto it = target_begin; it != target_end; ++it) {
    if (l == l_end) {
      *it = *r;
      ++r;
      continue;
    } else if (r == r_end) {
      *it = *l;
      ++l;
      continue;
    }

    if (compare(*l, *r)) {
      *it = *l;
      ++l;
    } else {
      *it = *r;
      ++r;
    }
  }
}

template<typename T>
std::unique_ptr<vector<T>>
go_one_deeper(std::unique_ptr<vector<T>>& v,
              comparator<T> compare,
              u_int allowed_threads)
{
  if (allowed_threads < 2) {
    return split_and_sort(v, compare);
  }

  u_int threads_left = allowed_threads / 2;
  u_int threads_right = allowed_threads - threads_left;

  u_int middle_index = v->size() / 2;
  Iterator<T> middle{ v->begin().get_raw_pointer() + middle_index };

  std::unique_ptr<vector<T>> left = std::make_unique<vector<T>>();
  copy<T>(v->begin(), middle, *left);
  std::unique_ptr<vector<T>> right = std::make_unique<vector<T>>();
  copy<T>(middle, v->end(), *right);

  std::future<std::unique_ptr<vector<T>>> left_future =
    std::async(std::launch::async,
               go_one_deeper<T>,
               std::ref(left),
               compare,
               threads_left);
  std::future<std::unique_ptr<vector<T>>> right_future =
    std::async(std::launch::async,
               go_one_deeper<T>,
               std::ref(right),
               compare,
               threads_right);
  left = left_future.get();
  right = right_future.get();

  merge(v->begin(), v->end(), left, right, compare);

  return std::move(v);

}

} // namespace _merge_sort

} // namespace adt

#endif