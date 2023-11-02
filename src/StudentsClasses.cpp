/**
 * @file StudentsClasses.cpp
 */
#include "StudentsClasses.hpp"
#include "Utils.hpp"
#include <string>
#include <cstdint>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>


/**
 * The constructor reads the line and assigns each string value to its attribute.
 * Theoretical Complexity: O(n), n being the number of values in the line.
 * @param line
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
/**
 * @brief Accesses the student code.
 * Theoretical Complexity: O(1).
 * @return the student code
 */
uint32_t StudentsClasses::get_student_code() const {return student_code_;}

/**
 * @brief Accesses the student name
 * Theoretical Complexity: O(1).
 * @return a const reference to the student name.
 */
const std::string & StudentsClasses::get_student_name() const {return student_name_;}

// Parsers
/**
 * @brief Converts the student code from string to a 32 bits unsigned integer.
 * Theoretical Complexity: O(1).
 * @param student_code
 * @return a 32 bits unsigned integer corresponding to the student code.
 */
uint32_t StudentsClasses::parse_student_code(const std::string& student_code) const {
    std::istringstream iss(student_code);
    uint32_t student_code_int;
    iss >> student_code_int;
    return student_code_int;
}

// String format
/**
 * This method converts the attribute student_code_ into a string and assigns the parameter out with its string value.
 * Theoretical Complexity: O(1).
 * @param student_code
 */
void StudentsClasses::student_code_to_str(std::string& student_code) const {
    student_code = std::to_string(student_code_);
}

// Debug
/**
 * This method prints the csv line of the current state of the object.
 * Theoretical Complexity: O(1).
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
