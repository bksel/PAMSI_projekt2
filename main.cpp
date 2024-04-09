#include <iostream>
#include <algorithm>
#include <vector>

#include "src/data_reader/DataReader.h"





int main() {
  std::cout << "Hello, World!" << std::endl;


  mdb::DataReader reader;
  reader.read_data("../projekt2_dane.csv");
//  reader.read_data("projekt2_dane.csv");

  const adt::vector<mdb::MovieEntry> &entries = reader.get_entries();

  adt::vector<mdb::MovieEntry> testing{};

  for (auto it = entries.begin(); it != entries.begin() + 1000; ++it) {
	testing.push_back(*it);
  }






  return 0;
}
