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

template<typename T>
void
put_data_in_buckets(vector<T>& sequence,
                    vector<UnilateralList<T>>& buckets,
                    hasher<T> hash);

template<typename T>
void
load_sequence_from_buckets(vector<T>& sequence,
                           vector<UnilateralList<T>>& buckets);

} // _bucket_sort
} // adt

namespace adt {


/*
 * In order for the bucket sort to work, the hash function must return a value
 * between 0 and max. Hashing function also must be monotonous, meaning that
 * if a < b, then hash(a) < hash(b). This algorithm doesn't handle hashed values
 * out of [0, max] range.
 *
 * The implementation of the hash function
 * based on generic type T is left to the user. Possible hash functions are
 * extractions of some kind of rating from the object. For instance for a movie
 * review, the hash function could be the rating of the movie.
 *
 * This algorithm is not in place, but uses O(n) extra space.
 *
 * */
template<typename T>
void
bucket_sort(const vector<T>& sequence, u_int max, hasher<T> hash)
{
  using namespace _bucket_sort;
  using list = UnilateralList<T>;

  vector<list> buckets = generate_buckets<T>(max);
  put_data_in_buckets(sequence, buckets, hash);
  load_sequence_from_buckets(sequence, buckets); // sequence is now sorted
}

namespace _bucket_sort {

template<typename T>
vector<UnilateralList<T>>
generate_buckets(u_int N)
{
  vector<UnilateralList<T>> v;
  v.reserve(N + 5);

  for (u_int i = 0; i < N + 1; ++i) {
    v.push_back(UnilateralList<T>{});
  }

  return v;
}

template<typename T>
void
put_data_in_buckets(vector<T>& sequence,
                    vector<UnilateralList<T>>& buckets,
                    hasher<T> hash)
{
  for (auto it = sequence.begin(); it != sequence.end(); ++it) {
    u_int classification = hash(*it);
    buckets[classification].push(*it);
  }
}

template<typename T>
void
load_sequence_from_buckets(vector<T>& sequence,
                           vector<UnilateralList<T>>& buckets)
{
  u_int index = 0;
  for (auto bucket : buckets) {
    while (not bucket.empty()) {
      T elem = bucket.pop();
      sequence[index] = std::move(elem);
      ++index;
    }
  }
}

} // bucket_sort

} // adt

#endif // MINIPROJEKT2_SRC_ABSTRACT_DATA_TYPE_SORTING_ALGORITHMS_BUCKET_SORT_BUCKETSORT_H_
