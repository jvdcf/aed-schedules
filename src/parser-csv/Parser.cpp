#include "Parser.h"
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

// djb2 hash : https://theartincode.stanis.me/008-djb2/
uint8_t hash_str(std::string s) {
  uint64_t hash = 5381;
  for (char c : s) {
    hash = (hash << 5) + hash + c;
  }
  return (uint8_t)(hash % 256);
}

bool isnum(uint32_t c) {
  return (c >= 48 && c <= 57);
}

void parse_csv_line(std::string s, std::vector<std::string>& res) {
  std::stringstream line(s); 
  std::string buf;
  while (getline(line,buf,',')) res.push_back(buf);
}

ClassPerUC::ClassPerUC(std::string csv) {
  std::stringstream s(csv);
  std::string line;
  s >> line;
  std::vector<std::string> linebuf;
  while (s >> line) {
    parse_csv_line(line, linebuf);
    uc_codes_.push_back(parse_uc(linebuf[0]));
    class_codes_.push_back(parse_class(linebuf[1]));
    linebuf.clear();
  }
  
}

uint16_t ClassPerUC::parse_uc(std::string uc_code) {
  uint64_t hash = 5381;
  std::string num_part;
  for (char c : uc_code) {
    if (isalpha(c)) {
      hash = (hash << 5) + hash + c;
    } 
    if (isnum(c)) {
      num_part.push_back(c);
    }
  }
  uint8_t num = std::stoi(num_part);

  return (uint16_t)((hash % 256) << 8) + (uint16_t)(num);
}

uint16_t ClassPerUC::parse_class(std::string class_code) {
  uint8_t year = class_code[0];
  std::string classnum;
  for (int i = 1; i < class_code.size(); ++i) {
    if (isnum(class_code[i])) {
      classnum.push_back(class_code[i]);
    }
  } 
  uint8_t num = stoi(classnum);
  return ((uint16_t)year << 8) + num;
}

void ClassPerUC::display() {
  std::cout << "UcCode,ClassCode\n";
  for (int i = 0; i < uc_codes_.size(); ++i) {
    std::cout << uc_codes_[i] << "," << class_codes_[i] << "\n";
  }
}

void ClassPerUC::class_to_str(int idx, std::string& out) {
  std::stringstream s;
  if (idx >= class_codes_.size()) {
    // TODO: use exceptions to handle errors instead of closing.
    std::cerr << "Index to class_to_str is bigger than allowed!" << std::endl;
    std::exit(1);
  }
  s << (class_codes_[idx] >> 8) << "LEIC" << std::setfill('0') << std::setw(2) << (class_codes_[idx] & 255);
  out = s.str();
}

void ClassPerUC::uc_to_str(int idx, std::string& out) {
  std::stringstream s;
  if (idx >= uc_codes_.size()) {
    std::cerr << "Index to uc_to_str is bigger than allowed!" << std::endl;
    std::exit(1);
  }
  std::string classname;
  uint16_t hash_of_class = uc_codes_[idx] >> 8;
  if (hash_of_class == hash_str("LEIC")) {
    classname = "L.EIC";
  } else if (hash_of_class == hash_str("UP")) {
    classname = "UP";
  } else {
    std::cerr << "There is no known uc type with hash " << hash_of_class << "!\n";
    std::exit(1);
  }

  s << (class_codes_[idx] >> 8) << classname << std::setfill('0') << std::setw(3) << (class_codes_[idx] & 255);
  out = s.str();
}










