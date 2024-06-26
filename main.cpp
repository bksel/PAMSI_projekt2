#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>

#include "src/abstract_data_type/lib.h"
#include "src/data_reader/DataReader.h"

void
test_loading()
{
  std::cout << "Hello, World!" << std::endl;

  mdb::DataReader reader;
  reader.read_data("../projekt2_dane.csv");
  //  reader.read_data("projekt2_dane.csv");

  const adt::vector<mdb::MovieEntry>& entries = reader.get_entries();

  fmt::println("Loaded {} entries", entries.size());
  std::this_thread::sleep_for(std::chrono::seconds(10));

  adt::vector<mdb::MovieEntry> testing{};
  testing.reserve(1000 + 50);
  for (auto it = entries.begin(); it != entries.begin() + 1000; ++it) {
    testing.push_back(*it);
  }

  fmt::println("Before sorting:");
  auto start = std::chrono::high_resolution_clock::now();
  adt::merge_sort_parallel<mdb::MovieEntry>(
    entries.begin(),
    entries.end(),
    [](const mdb::MovieEntry& a, const mdb::MovieEntry& b) {
      return a.rating < b.rating;
    });

//    adt::bucket_sort<mdb::MovieEntry>(
//      entries, 10, [](const mdb::MovieEntry& entry) { return entry.rating; });
  auto end = std::chrono::high_resolution_clock::now();
  fmt::println("After sorting:");
  fmt::println(
    "Time: {}ms",
    std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
  //  for (auto &it : entries) {
  //	fmt::println("{}: {}", it.name, it.rating);
  //  }

  bool status = adt::is_sorted<mdb::MovieEntry>(
    entries, [](const mdb::MovieEntry& a, const mdb::MovieEntry& b) {
      return a.rating < b.rating;
    });

  fmt::println("Sorted: {}", status);
  adt::print_inline<mdb::MovieEntry>(entries.begin(), entries.begin() + 15);
}

void
test_sorting()
{

  using adt::print_inline;

  //  adt::vector<int> v{89,23, 45, 56, 454, 1, 4, -4, 8, 15, 91, -50, 0, 0, 0,
  //  11, 23, 11, 45};
  adt::vector<int> v{ 89, 23, 45, 56, -10 };
  void (*sort)(adt::Iterator<int> begin,
               adt::Iterator<int> end,
               adt::comparator<int> compare) = adt::merge_sort<int>;

  print_inline(v);
  sort(v.begin(), v.end(), [](const int& a, const int& b) { return a < b; });
  print_inline(v);

  adt::vector<int> nv = adt::get_copy<int>(v.begin() + 6, v.begin() + 9);
  //  nv[0] = 1000;
  print_inline(nv);
  print_inline(v);

  bool status =
    adt::is_sorted<int>(v, [](const int& a, const int& b) { return a < b; });
  fmt::println("Sorted: {}", status);

}

void
test_list()
{

  adt::UnilateralList<int> list;

  list.push(1);
  list.push(2);
  list.push(3);

  while (not list.empty()) {

    fmt::println("Popped: {}", list.pop());
  }
}

int
main()
{
  test_loading();
//    test_sorting();
  //  test_list();
  return 0;
}