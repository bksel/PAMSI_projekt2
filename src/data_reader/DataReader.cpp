//
// Created by ksel on 06/04/24.
//

#include "DataReader.h"

#include <algorithm>
#include <iostream>

namespace mdb {
const adt::vector<MovieEntry>&
DataReader::get_entries() const
{
  return entries;
}
void
DataReader::open_file(const std::string& filename)
{

  file_stream.open(filename);
  if (!file_stream.is_open())
    throw std::runtime_error("Could not open file");
}
void
DataReader::close_file()
{

  try {
    file_stream.close();
  } catch (std::exception& e) {
    throw std::runtime_error("Could not close file");
  }
}
void
DataReader::read_data(const std::string& filename)
{
  open_file(filename);
  u_int length = count_lines_in_file();
  entries.reserve(length + 10);
  file_stream.seekg(0, std::ios::beg); // go back to the beginning

  load_entries();

  close_file();
}
u_int
DataReader::count_lines_in_file()
{

  u_int count = 0;
  count = std::count(std::istreambuf_iterator<char>(file_stream),
                     std::istreambuf_iterator<char>(),
                     '\n');
  return count;
}

void
DataReader::load_entries()
{

  std::string line;
  std::getline(file_stream, line); // skip header
  while (std::getline(file_stream, line)) {
    read_entry(line);
  }
}
void
DataReader::read_entry(const std::string& line)
{
  MovieEntry entry{};
  try {
    entry = parse_entry(line);
  } catch (InvalidMovieEntry& e) {
    fmt::println(stderr, "Invalid entry: {}", e.what());
    return;
  }
  entries.push_back(entry);
}
MovieEntry
DataReader::parse_entry(const std::string& line)
{

  u_int commas = std::count(line.begin(), line.end(), ',');
  if (commas != 2) {
    throw InvalidMovieEntry(line);
  }
  // make 3 substrings that are separated by commas
  [[maybe_unused]] std::string order_number = line.substr(0, line.find(','));
  std::string name =
    line.substr(line.find(',') + 1, line.rfind(',') - line.find(',') - 1);
  std::string rating = line.substr(line.rfind(',') + 1);

  if (rating.empty()) {
    throw InvalidMovieEntry(line);
  }

  try {
    return MovieEntry{ name, (u_int)std::stoi(rating) };
  } catch (std::exception& e) {
    fmt::println(stderr, "exception during movie entry parsing: {}", e.what());
    throw InvalidMovieEntry(line);
  }
  return MovieEntry{}; // for the compiler, it should never reach this point
}
} // mdb