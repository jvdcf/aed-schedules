/**
 * @file CSVStudentsClasses.cpp
 */
#include "CSVStudentsClasses.hpp"
#include "StudentsClasses.hpp"
#include "Utils.hpp"
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>


/**
 * @brief This constructor receives a string containing all the lines of a csv file and creates the AppSudentClass from it.
 * @details Theoretical Complexity: O(n), n being the number of characters in a csv line.
 * @param csv
 */
CSVStudentsClasses::CSVStudentsClasses(const std::string& csv) {
    // CSV file into memory
    std::ifstream file = std::ifstream(csv);
    std::string contents;
    std::ostringstream sstr;
    sstr << file.rdbuf();
    contents = sstr.str();

    // Parse string
    std::stringstream s(contents);
    std::string line;
    this->entries = std::vector<StudentsClasses>();
    getline(s,line,'\n');
    line.clear();
    while (std::getline(s,line,'\n')) {
        this->entries.push_back(StudentsClasses(line));
    }
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

// Debug
/**
 * @brief Displays the contents of the class.
 */
void CSVStudentsClasses::display() const {
    std::cout << "StudentCode" << ','
              << "StudentName" << ','
              << "UcCode" << ','
              << "ClassCode" << '\n';
    for (const auto& e : this->entries) {
        e.display();
    }
}

/**
 * @brief Getter for the vector of StudentsClasses.
 * @return Pointer to entries
 */
std::vector<StudentsClasses> *CSVStudentsClasses::get_students() {return &this->entries;}
