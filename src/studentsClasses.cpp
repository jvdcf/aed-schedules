#include "studentsClasses.hpp"
#include "Utils.hpp"
#include <string>
#include <cstdint>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>

/**
 * @file studentsClasses.cpp
 */

// Constructor
/**
 * The constructor reads the line and assigns each string value to its attribute.
 * @param line
 * @tparam std::string
 */
StudentsClasses::StudentsClasses(std::string& line) {
    std::vector<std::string> linebuf;
    parse_csv_line(line, linebuf);
    student_code_ = parse_student_code(linebuf[0]);
    student_name_ = linebuf[1];
    uc_code_ = parse_uc(linebuf[2]);
    class_code_ = parse_class(linebuf[3]);
}


// Getters
uint32_t StudentsClasses::get_student_code() const {return student_code_;}
const std::string &StudentsClasses::get_student_name() const {return student_name_;}


// Parsers
uint32_t StudentsClasses::parse_student_code(const std::string& student_code) const {
    std::istringstream iss(student_code);
    uint32_t student_code_int;
    iss >> student_code_int;
    return student_code_int;
}


// String format
/**
 * This method converts the attribute student_code_ into a string and assigns the parameter out with its string value.
 * @param student_code
 * @tparam std::string
 */
void StudentsClasses::student_code_to_str(std::string& student_code) const {
    student_code = std::to_string(student_code_);
}

// Debug
/**
 * This method prints the csv line of the current state of the object.
 */
void StudentsClasses::display() const {
    std::string student_code;
    std::string student_name = get_student_name();
    std::string uc_code;
    std::string class_code;
    student_code_to_str(student_code);
    uc_to_str(uc_code);
    class_to_str(class_code);
    std::cout << student_code << ","
              << student_name << ","
              << uc_code << ","
              << class_code << '\n';
}
