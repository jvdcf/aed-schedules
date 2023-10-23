#include "classesPerUC.hpp"
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "Utils.hpp"


void parse_csv_line(std::string s, std::vector<std::string> &res) {
  std::stringstream line(s);
  std::string buf;
  while (getline(line, buf, ','))
    res.push_back(buf);
}

ClassPerUC::ClassPerUC(std::string line) {
  std::vector<std::string> linebuf;
  parse_csv_line(line, linebuf);
  uc_codes_ = parse_uc(linebuf[0]);
  class_codes_ = parse_class(linebuf[1]);
}

uint16_t ClassPerUC::parse_uc(std::string uc_code) {
  uint64_t hash = 5381;
  std::string num_part;
  for (char c : uc_code) {
    if (!isnum(c)) {
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
    return (uint16_t)((hash % 256) << 8) + (uint16_t)(num);
  } catch (std::invalid_argument &e) {
    std::cerr << e.what() << " uc: failed to parse" << '\n';
    std::exit(1);
  }
}

uint16_t ClassPerUC::parse_class(std::string class_code) {
  uint8_t year = class_code[0] - '0';
  std::string classnum;
  for (int i = 1; i < class_code.size(); ++i) {
    if (isnum(class_code[i])) {
      classnum.push_back(class_code[i]);
    }
  }
  try {
    uint8_t num = 0;
    if (classnum != "") {
      num = std::stoi(classnum);
    }
    return ((uint16_t)year << 8) + num;
  } catch (std::invalid_argument &e) {
    std::cerr << e.what() << " class: failed to parse" << '\n';
    std::exit(1);
  }
}

void ClassPerUC::display() {
  // std::cout << "UcCode,ClassCode\n";
  std::string uc;
  std::string cc;
  uc_to_str(uc);
  class_to_str(cc);
  std::cout << uc << "," << cc << "\n";
}

void ClassPerUC::class_to_str(std::string &out) {
  std::stringstream s;
  // TODO: use exceptions to handle errors instead of closing.
  if ((class_codes_ >> 8) == 19) {
    out = "ClassCode";
    return;
  }
  s << (class_codes_ >> 8) << "LEIC" << std::setfill('0') << std::setw(2)
    << (class_codes_ & 255);
  out = s.str();
}

void ClassPerUC::uc_to_str(std::string &out) {
  std::stringstream s;
  std::string classname;
  bool found = false;
  uint16_t hash_of_class = uc_codes_ >> 8;
  for (int i = 0; i <= sizeof(this->types_of_uc) / sizeof(char *); ++i) {
    if (hash_of_class == hash_str(std::string(this->types_of_uc[i]))) {
      classname = this->types_of_uc[i];
      found = true;
      break;
    }
  }
  if (!found) {
    std::cerr << "There is no known uc type with hash " << hash_of_class
              << "!\n";
    std::exit(1);

  }
  s << classname << std::setfill('0') << std::setw(3) << (uc_codes_ & 255);
  out = s.str();
}
