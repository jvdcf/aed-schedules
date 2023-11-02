/**
 * @file CSVStudentsClasses.cpp
 */
#include "CSVStudentsClasses.hpp"
#include "StudentsClasses.hpp"
#include "Utils.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

/**
 * This constructor receives a string containing all the lines of a csv file and
 * creates the AppSudentClass from it.
 * @param csv
 */
CSVStudentsClasses::CSVStudentsClasses(const std::string &csv) {
  // CSV file into memory
  this->filename = csv;
  std::ifstream file = std::ifstream(csv);
  std::string contents;
  std::ostringstream sstr;
  sstr << file.rdbuf();
  contents = sstr.str();

  // Parse string
  std::stringstream s(contents);
  std::string line;
  this->entries = std::vector<StudentsClasses>();
  if (!getline(s, line, '\n')) {
    std::cerr << "ERROR: CRITICAL: INVALID FILE CSVSTUDENTCLASSES(0)" << std::endl;
    std::exit(1);
  }
  if (line != "StudentCode,StudentName,UcCode,ClassCode") {
    std::cout << line <<" != " << std::string("StudentCode,StudentName,UcCode,ClassCode") << std::endl;
    std::cerr << "ERROR: CRITICAL: INVALID FILE CSVSTUDENTCLASSES(1)" << std::endl;
    std::exit(1);
  }
  line.clear();
  while (std::getline(s, line, '\n')) {
    this->entries.push_back(StudentsClasses(line));
  }
}

CSVStudentsClasses::CSVStudentsClasses() { this->entries = {}; }

/**
 * @brief Displays the contents of the class.
 */
std::string CSVStudentsClasses::display() const {
  std::stringstream s;
  s << "StudentCode" << ','
              << "StudentName" << ','
              << "UcCode" << ','
              << "ClassCode" << '\n';
  for (const auto &e : this->entries) {
    s << e.display();
  }
  return s.str();
}

/**
 * @brief Getter for the vector of StudentsClasses.
 * @return Pointer to entries
 */
std::vector<StudentsClasses> *CSVStudentsClasses::get_students() {
  return &this->entries;
}

void CSVStudentsClasses::set_students(
    const std::vector<StudentsClasses> &entries) {
  this->entries = entries;
}

void CSVStudentsClasses::write_to_file() {
  std::ofstream ofs(this->filename);
  ofs << this->display();
}

void CSVStudentsClasses::set_filename(const std::string& name) {
  this->filename = name; 
} 

/**
 * @brief Sorts the entries vector.
 * @details Order (from most important to least important): student_code > uc_code > class_code.
 * Theoretical complexity: O(n log n), where n is the number of entries in the vector.
 */
void CSVStudentsClasses::sort() {
    std::sort(this->entries.begin(), this->entries.end(), [](const StudentsClasses &a, const StudentsClasses &b) {
        if (a.get_student_code() == b.get_student_code()) {
            if (a.get_uc_code() == b.get_uc_code()) {
                return a.get_class_code() < b.get_class_code();
            } else return a.get_uc_code() < b.get_uc_code();
        } else return a.get_student_code() < b.get_student_code();
    });
}
