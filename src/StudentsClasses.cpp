/**
 * @file StudentsClasses.cpp
 */
#include "StudentsClasses.hpp"
#include "Utils.hpp"
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/**
 * The constructor reads the line and assigns each string value to its
 * attribute.
 * Theoretical Complexity: O(n), n being the number of values in the line.
 * @param line
 */
StudentsClasses::StudentsClasses(std::string &line) {
  std::vector<std::string> linebuf;
  parse_csv_line(line, linebuf);
  student_code_ = parse_student_code(linebuf[0]);
  student_name_ = linebuf[1];
  uc_code_ = parse_uc(linebuf[2]);
  class_code_ = parse_class(linebuf[3]);
}

/**
 * @brief Trivial constructor from atributes.
 */
StudentsClasses::StudentsClasses(uint16_t uc_code, uint16_t class_code,
                                 const std::string &name,
                                 uint32_t student_code) {
  uc_code_ = uc_code;
  class_code_ = class_code;
  student_name_ = name;
  student_code_ = student_code;
}

/**
 * @brief Accesses the student code.
 * Theoretical Complexity: O(1).
 * @return the student code
 */
uint32_t StudentsClasses::get_student_code() const { return student_code_; }
const std::string &StudentsClasses::get_student_name() const {
  return student_name_;
}

/**
 * @brief Converts the student code from string to a 32 bits unsigned integer.
 * Theoretical Complexity: O(1).
 * @param student_code
 * @return a 32 bits unsigned integer corresponding to the student code.
 */
uint32_t
StudentsClasses::parse_student_code(const std::string &student_code) const {
  uint32_t student_code_int;
  try {
    student_code_int = std::stoi(student_code);
  } catch (std::exception e) {
    std::cerr << "ERROR: CRITICAL: CSV StudentsClasses has invalid information "
                 "saved; Exiting."
              << std::endl;
    std::exit(1);
  }
  return student_code_int;

/**
 * @brief Accesses the student name
 * Theoretical Complexity: O(1).
 * @return a const reference to the student name.
 */
const std::string & StudentsClasses::get_student_name() const {return student_name_;}

/**
 * This method converts the attribute student_code_ into a string and assigns
 * the parameter out with its string value.
 * Theoretical Complexity: O(1).
 * @param student_code
 */
void StudentsClasses::student_code_to_str(std::string &student_code) const {
  student_code = std::to_string(student_code_);
}

/**
 * This method prints the csv line of the current state of the object.
 * Theoretical Complexity: O(1).
 */
std::string StudentsClasses::display() const {
  std::stringstream s;
  std::string student_code;
  std::string student_name = get_student_name();
  std::string uc_code;
  std::string class_code;
  student_code_to_str(student_code);
  uc_to_str(uc_code);
  class_to_str(class_code);
  s << student_code << "," << student_name << "," << uc_code << ","
            << class_code << '\n';
  return s.str();
}
