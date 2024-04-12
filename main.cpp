#include <iostream>
#include <algorithm>
#include <vector>

#include "src/data_reader/DataReader.h"
#include "src/abstract_data_type/lib.h"

void test_loading() {
  std::cout << "Hello, World!" << std::endl;

  mdb::DataReader reader;
  reader.read_data("../projekt2_dane.csv");
//  reader.read_data("projekt2_dane.csv");

  const adt::vector<mdb::MovieEntry> &entries = reader.get_entries();

  adt::vector<mdb::MovieEntry> testing{};
  testing.reserve(1000 + 50);
  for (auto it = entries.begin(); it != entries.begin() + 1000; ++it) {
	testing.push_back(*it);
  }

  adt::bubble_sort<mdb::MovieEntry>(testing.begin(),
									testing.end(),
									[](const mdb::MovieEntry &a, const mdb::MovieEntry &b) {
									  return a.rating < b.rating;
									});

  for (auto &it : testing) {
	fmt::println("{}: {}", it.name, it.rating);
  }

}

void test_sorting() {

  using adt::print_inline;

  adt::vector<int> v{23, 45, 56, 454, 1, 4, -4, 8, 15, 90};

  void (*sort)(adt::vector<int> &, bool (*)(const int &, const int &)) = adt::bubble_sort<int>;

  print_inline(v);
  sort(v, [](const int &a, const int &b) { return a > b; });
  print_inline(v);

}

int main() {
//  test_loading();
  test_sorting();
  return 0;
}