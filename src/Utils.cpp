/**
 * @file Utils.cpp
 * This file defines some functions that are gonna be useful in other classes
 */
#include "Utils.hpp"
#include <iostream>

/**
 * This function converts a string to a 8 bit hash.
 * This algorithm (djb2 hash) is better explained here: https://theartincode.stanis.me/008-djb2/
 * @param s
 * @tparam std::string
 * @return the string converted to hash
 */
uint8_t hash_str(std::string s) {
  uint64_t hash = 5381;
  for (char c : s) {
    hash = (hash << 5) + hash + c;
  }
  return (uint8_t)(hash % 256);
}

uint16_t parse_uc_gen(std::string uc_code) {
  uint64_t hash = 5381;
  std::string num_part;
  for (char c : uc_code) {
    if (!isnum(c)) {
      // DEBUG : printf("%c",c);
      hash = (hash << 5) + hash + c;
    }
    if (isnum(c)) {
      num_part.push_back(c);
    }
  }
  try {
    uint8_t num = 0;
    if (num_part != "") {
      num = std::stoi(num_part);
    }
    // DEBUG : printf(" -> code : %d\n", (uint8_t)hash);
    return (uint16_t)((hash % 256) << 8) + (uint16_t)(num);
  } catch (std::invalid_argument &e) {
    std::cerr << e.what() << " uc: failed to parse" << '\n';
    std::exit(1);
  }
}

/**
 * This function checks if a given character in a number.
 * @param c
 * @tparam uint32_t
 * @return bool
 */
bool isnum(uint32_t c) { return (c >= '0' && c <= '9'); }

/**
 * This function reads a line of the csv file given in the parameter std::string s and appends to the vector passed
 * by reference res the comma separated values of the line
 * @param s
 * @tparam std::string
 * @param res
 * @tparam std::vector<std::string>
 */
void parse_csv_line(std::string s, std::vector<std::string> &res) {
  std::stringstream line(s);
  std::string buf;
  while (getline(line, buf, ','))
    res.push_back(buf);
}
