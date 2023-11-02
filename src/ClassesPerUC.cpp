/**
 * @file ClassesPerUC.cpp
 */
#include "ClassesPerUC.hpp"
#include "Utils.hpp"
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * @brief The constructor reads the line and assigns each string value to its
 * attribute.
 * @details It was opted to transform the sting values of uc_code and
 * class_code_ into hashes for sakes of performance, since it is quicker to
 * compare integers than strings. Theoretical Complexity: O(n), n being the
 * number of characters in a csv line.
 * @param line
 */
ClassPerUC::ClassPerUC(std::string line) {
  std::vector<std::string> linebuf;
  parse_csv_line(line, linebuf);
  uc_code_ = parse_uc(linebuf[0]);
  class_code_ = parse_class(linebuf[1]);
}

/**
 * @brief The constructor implicitly used for subclasses. Not used standalone.
 */
ClassPerUC::ClassPerUC() {
  uc_code_ = 0;
  class_code_ = 0;
}

/**
 * @brief Getter for uc_code.
 * @return uc_code
 */
uint16_t ClassPerUC::get_uc_code() const { return uc_code_; }

/**
 * @brief Getter for class_code.
 * @return class_code
 */
uint16_t ClassPerUC::get_class_code() const { return class_code_; }

/**
 * @brief Getter for uc_code and class_code as a single uint32_t.
 * @return id
 */
uint32_t ClassPerUC::get_id() const {
  return ((uint32_t)uc_code_ << 16) + class_code_;
}

/**
 * @brief Parse uc_code from a std::string to an uint16_t.
 * @details Useful to save memory and to make comparisons faster.
 * Theoretical Complexity: O(n), n being the number of characters of the
 * std::string.
 * @param uc_code
 * @return uc_code as a uint16_t
 */
uint16_t ClassPerUC::parse_uc(std::string uc_code) {
  return parse_uc_gen(uc_code);
}

/**
 * @brief Parse class_code from a std::string to an uint16_t.
 * @details Useful to save memory and to make comparisons faster.
 * Theoretical Complexity: O(n), n being the number of characters of the
 * std::string.
 * @param class_code
 * @return class_code as uint16_t
 */
uint16_t ClassPerUC::parse_class(std::string class_code) {
  return parse_class_gen(class_code); 
}

/**
 * @brief This method converts the attribute uc_code_ into a string and assigns
 * the parameter out with its string value.
 * Theoretical Complexity: O(1).
 * @param out
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
 * @brief This method converts the attribute class_code_ into a string and
 * assigns the parameter out with its string value.
 * Theoretical Complexity: O(1).
 * @param out
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
 * @brief This method prints the csv line of the current state of the object.
 * Theoretical Complexity: O(1).
 */
std::string ClassPerUC::display() const {
  // std::cout << "UcCode,ClassCode\n";
  std::stringstream s; 
  std::string uc;
  std::string cc;
  uc_to_str(uc);
  class_to_str(cc);
  s << uc << "," << cc << "\n";
  return s.str();
}
