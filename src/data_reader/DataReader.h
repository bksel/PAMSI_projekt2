//
// Created by ksel on 06/04/24.
//

#ifndef MINIPROJEKT1_SRC_DATA_READER_DATAREADER_H_
#define MINIPROJEKT1_SRC_DATA_READER_DATAREADER_H_

#include <cstdio>
#include <string>
#include <fstream>

#include "../abstract_data_type/vector/vector.cpp"
#include "../movie_entry/MovieEntry.h"

namespace mdb {

class DataReader {

  std::ifstream file_stream;

  adt::vector<MovieEntry> entries{};
  std::string buffer{};

  void open_file(const std::string& filename);
  void close_file();

  u_int count_lines_in_file();

  void load_entries();
  void read_entry(const std::string &line);
  static MovieEntry parse_entry(const std::string &line);


 public:

  DataReader() = default;
  void read_data(const std::string &filename);
  [[nodiscard]] const adt::vector<MovieEntry> &get_entries() const;

  class InvalidMovieEntry : public std::exception {
   char* message;
   public:
	explicit InvalidMovieEntry(const std::string &line) {
	  message = new char[line.size() + 1];
	  std::strcpy(message, line.c_str());
	}
	~InvalidMovieEntry() override {
	  delete message;
	}
	[[nodiscard]] const char *what() const noexcept override {
	  return message;
	}
  };


};

} // mdb

#endif //MINIPROJEKT1_SRC_DATA_READER_DATAREADER_H_
