//
// Created by ksel on 17/04/24.
//

#ifndef MINIPROJEKT2_SRC_ABSTRACT_DATA_TYPE_SORTING_ALGORITHMS_BUCKET_SORT_BUCKETSORT_H_
#define MINIPROJEKT2_SRC_ABSTRACT_DATA_TYPE_SORTING_ALGORITHMS_BUCKET_SORT_BUCKETSORT_H_

#include "../../list/UnilateralList.h"
#include "../../vector/vector.h"
#include "../sorting_utils.h"
#include <cassert>

namespace adt {

template<typename T>
void
bucket_sort(vector<T>& sequence, u_int max, hasher<T> hash);

namespace _bucket_sort {

template<typename T>
vector<UnilateralList<T>>
generate_buckets(u_int N);

} // _bucket_sort
} // adt

namespace adt {

template<typename T>
void
bucket_sort(const vector<T>& sequence, u_int max, hasher<T> hash)
{
  vector<UnilateralList<T>> buckets = _bucket_sort::generate_buckets<T>(max);

  for (auto it = sequence.begin(); it != sequence.end(); ++it) {
    u_int classification = hash(*it);


    buckets[classification].push(*it);
  }

  u_int index = 0;
  for (auto bucket : buckets) {
    while(not bucket.empty()) {
      T elem = bucket.pop();
      sequence[index] = std::move(elem);
      ++index;
    }
  }

//  u_int vlen = sequence.size();


}

namespace _bucket_sort {

template<typename T>
vector<UnilateralList<T>>
generate_buckets(u_int N)
{
  vector<UnilateralList<T>> v;
  v.reserve(N+5);

  for (u_int i = 0; i < N+1; ++i) {
    v.push_back(UnilateralList<T>{});
  }

  return v;
}

} // bucket_sort

} // adt

#endif // MINIPROJEKT2_SRC_ABSTRACT_DATA_TYPE_SORTING_ALGORITHMS_BUCKET_SORT_BUCKETSORT_H_
