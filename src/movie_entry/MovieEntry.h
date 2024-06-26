//
// Created by ksel on 05/04/24.
//

#ifndef MINIPROJEK2_SRC_ENTRY_H_
#define MINIPROJEK2_SRC_ENTRY_H_

#include <cstdlib>
#include <string>

namespace mdb {

struct MovieEntry
{

  std::string name{};
  u_int rating = 0;

  MovieEntry() = default;
  MovieEntry(std::string name, u_int rating)
    : name(std::move(name))
    , rating(rating)
  {
  }

  // operator << overload
  friend std::ostream& operator<<(std::ostream& os, const MovieEntry& entry)
  {
    os << entry.rating;
    return os;
  }
};

} // mdb

#endif // MINIPROJEK2_SRC_ENTRY_H_
