#include "studentsClasses.hpp"
#include "Utils.hpp"
#include <string>
#include <cstdint>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>

// Constructor
StudentsClasses::StudentsClasses(std::string& line) {
    std::vector<std::string> linebuf;
    parse_csv_line(line, linebuf);
    student_code_ = parse_student_code(linebuf[0]);
    student_name_ = linebuf[1];
    uc_codes_ = parse_uc(linebuf[2]);
    class_codes_ = parse_class(linebuf[3]);
}


// Getters
uint32_t StudentsClasses::get_student_code() const { return student_code_; }
std::string StudentsClasses::get_student_name() const { return student_name_; }
uint16_t StudentsClasses::get_uc_code() const { return uc_codes_; }
uint16_t StudentsClasses::get_class_code() const { return class_codes_; }


// Parsers
uint32_t StudentsClasses::parse_student_code(const std::string& student_code) const {
    std::istringstream iss(student_code);
    uint32_t student_code_int;
    iss >> student_code_int;
    return student_code_int;
}


// String format
void StudentsClasses::student_code_to_str(std::string& student_code) const {
    student_code = std::to_string(student_code_);
}


// Debug
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
