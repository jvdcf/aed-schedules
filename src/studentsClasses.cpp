#include "studentsClasses.hpp"
#include "Utils.hpp"
#include <string>
#include <cstdint>
#include <vector>
#include <iostream>
#include <iomanip>

// Constructor
StudentsClasses::StudentsClasses(std::string line) {
    std::vector<std::string> linebuf;
    parse_csv_line(line, linebuf);
    student_code_ = parse_student_code(linebuf[0]);
    student_name_ = linebuf[1];
    uc_code_ = parse_uc(linebuf[2]);
    class_code_ = parse_class(linebuf[3]);
}


// Parsers
uint32_t StudentsClasses::parse_student_code(std::string student_code) {
    return std::stoi(student_code);
}

uint16_t StudentsClasses::parse_uc(std::string uc_code) {
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

uint16_t StudentsClasses::parse_class(std::string class_code) {
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


// String format
void StudentsClasses::student_code_to_str(std::string& student_code) {
    student_code = std::to_string(student_code_);
}
void StudentsClasses::student_name_to_str(std::string& student_name) {
    student_name = student_name_;
}
void StudentsClasses::uc_code_to_str(std::string& uc_code) {
    std::stringstream s;
    std::string classname;
    bool found = false;
    uint16_t hash_of_class = uc_code_ >> 8;
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
    s << classname << std::setfill('0') << std::setw(3) << (uc_code_ & 255);
    uc_code = s.str();
}
void StudentsClasses::class_code_to_str(std::string& class_code) {
    std::stringstream s;
    // TODO: use exceptions to handle errors instead of closing.
    if ((class_code_ >> 8) == 19) {
        class_code = "ClassCode";
        return;
    }
    s << (class_code_ >> 8) << "LEIC" << std::setfill('0') << std::setw(2)
      << (class_code_ & 255);
    class_code = s.str();
}


// Debug
void StudentsClasses::display() {
    std::string student_code;
    std::string student_name;
    std::string uc_code;
    std::string class_code;
    student_code_to_str(student_code);
    student_name_to_str(student_name);
    uc_code_to_str(uc_code);
    class_code_to_str(class_code);
    std::cout << student_code << ","
              << student_name << ","
              << uc_code << ","
              << class_code << '\n';
}
