/**
 * @file Utils.hpp
 */
#ifndef UTILS_HPP
#define UTILS_HPP
#include <cinttypes>
#include <cstdint>
#include <string>
#include <vector>
#include <sstream>


// djb2 hash : https://theartincode.stanis.me/008-djb2/
uint8_t hash_str(std::string s);

uint16_t parse_uc_gen(std::string s);

bool isnum(uint32_t c);

void parse_csv_line(std::string s, std::vector<std::string> &res);

enum class OperationResult {
  Success = 0,
  Conflicts = 1,
  Error = 2,
};


#endif // !UTILS_HPP
