/**
 * @file ClassesPerUC.cpp
 */
#include "ClassesPerUC.hpp"
#include "Utils.hpp"
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>


/**
 * The constructor reads the line and assigns each string value to its attribute.
 * We opted to transform the sting values of uc_code and class_code_ into hashes for sakes of performance,
 * since it is quicker to compare integers than strings.
 * @param line
 * @tparam
 */
ClassPerUC::ClassPerUC(std::string line) {
  std::vector<std::string> linebuf;
  parse_csv_line(line, linebuf);
  uc_code_ = parse_uc(linebuf[0]);
  class_code_ = parse_class(linebuf[1]);
}

ClassPerUC::ClassPerUC() {
  uc_code_ = 0;
  class_code_ = 0;
}

uint16_t ClassPerUC::get_uc_code() const {
    return uc_code_;
}

uint16_t ClassPerUC::get_class_code() const {
    return class_code_;
}

uint16_t ClassPerUC::parse_uc(std::string uc_code) {
  return parse_uc_gen(uc_code);
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

/**
 * This method converts the attribute uc_code_ into a string and assigns the parameter out with its string value.
 * @param out
 * @tparam std::string
 */
void ClassPerUC::uc_to_str(std::string &out) const {
    std::stringstream s;
    std::string classname;
    uint16_t hash_of_class = uc_code_ >> 8;
    classname = std::string(this->types_of_uc[hash_of_class]);
    if (classname == "") {
        std::cerr << "There is no known uc type with hash " << hash_of_class
                  << "!\n";
        std::exit(1);
    }
    s << classname << std::setfill('0') << std::setw(3) << (uc_code_ & 255);
    out = s.str();
}

/**
 * This method converts the attribute class_code_ into a string and assigns the parameter out with its string value.
 * @param out
 * @tparam std::string
 */
void ClassPerUC::class_to_str(std::string &out) const {
  std::stringstream s;
  // TODO: use exceptions to handle errors instead of closing.
  if ((class_code_ >> 8) == 19) {
    out = "ClassCode";
    return;
  }
  s << (class_code_ >> 8) << "LEIC" << std::setfill('0') << std::setw(2)
    << (class_code_ & 255);
  out = s.str();
}

/**
 * This method prints the csv line of the current state of the object.
 */
void ClassPerUC::display() const {
    // std::cout << "UcCode,ClassCode\n";
    std::string uc;
    std::string cc;
    uc_to_str(uc);
    class_to_str(cc);
    std::cout << uc << "," << cc << "\n";
}

uint32_t ClassPerUC::get_id() const {return ((uint32_t)uc_code_ << 16) + class_code_;}
