#include <iostream>
#include <algorithm>
#include <vector>

#include "src/data_reader/DataReader.h"
#include "src/sorting_algorithms/bubble_sort.cpp"

int main() {
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

  bubble_sort<mdb::MovieEntry>(testing,
							   [](const mdb::MovieEntry &a, const mdb::MovieEntry &b)
							   { return a.rating < b.rating; });

  for (auto & it : testing) {
	fmt::println("{}: {}", it.name, it.rating);
  }


  return 0;
}
