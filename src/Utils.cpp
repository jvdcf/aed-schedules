#include "Utils.hpp"
// djb2 hash : https://theartincode.stanis.me/008-djb2/
uint8_t hash_str(std::string s) {
  uint64_t hash = 5381;
  for (char c : s) {
    hash = (hash << 5) + hash + c;
  }
  return (uint8_t)(hash % 256);
}

bool isnum(uint32_t c) { return (c >= '0' && c <= '9'); }

void parse_csv_line(std::string s, std::vector<std::string> &res) {
  std::stringstream line(s);
  std::string buf;
  while (getline(line, buf, ','))
    res.push_back(buf);
}

