#include "appStudentsClasses.hpp"
#include "studentsClasses.hpp"
#include "Utils.hpp"
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

// Constructor
AppStudentsClasses::AppStudentsClasses(std::string csv) {
    std::stringstream s(csv);
    std::string line;
    this->entries = std::vector<StudentsClasses>();
    getline(s,line,'\n');
    std::vector<std::string> bufs;
    parse_csv_line(line,bufs);
    this->student_code_cath_name = bufs[0];
    this->student_name_cath_name = bufs[1];
    this->uc_code_cath_name = bufs[2];
    this->class_code_cath_name = bufs[3];
    line.clear();
    while (std::getline(s,line,'\n')) {
        this->entries.push_back(StudentsClasses(line));
    }
}

// Methods
void AppStudentsClasses::sort_by(const std::string& category) {
    if (category == this->student_code_cath_name) {
        std::sort(this->entries.begin(), this->entries.end(),
                  [](const StudentsClasses& a, const StudentsClasses& b) {return a.get_student_code() < b.get_student_code();});

    } else if (category == this->student_name_cath_name) {
        std::sort(this->entries.begin(), this->entries.end(),
                  [](const StudentsClasses& a, const StudentsClasses& b) {return a.get_student_name() < b.get_student_name();});

    } else if (category == this->uc_code_cath_name) {
        std::sort(this->entries.begin(), this->entries.end(),
                  [](const StudentsClasses& a, const StudentsClasses& b) {return a.get_uc_code() < b.get_uc_code();});

    } else if (category == this->class_code_cath_name) {
        std::sort(this->entries.begin(), this->entries.end(),
                  [](const StudentsClasses& a, const StudentsClasses& b) {return a.get_class_code() < b.get_class_code();});

    } else {
        std::cerr << "Error: invalid category" << '\n';
        std::exit(1);
    }
}

std::vector<StudentsClasses>::iterator AppStudentsClasses::search_by_uc(uint16_t uc_code) {
    sort_by(uc_code_cath_name);
    auto ret = entries.end();
    size_t mid = entries.size() / 2;

    while (true) { // Binary search
        if (mid == entries.size()) {
            return ret;
        } else if (entries[mid].get_uc_code() == uc_code) {
            ret = entries.begin() + mid;
            break;
        } else if (entries[mid].get_uc_code() > uc_code) {
            mid = mid / 2;
        } else {
            mid = mid + mid / 2;
        }
    }

    while (true) {
        if ((ret - 1)->get_uc_code() != uc_code) {
            return ret;
        } else --ret;
    }
}

std::vector<StudentsClasses>::iterator AppStudentsClasses::search_by_student(uint32_t student_code) {
    sort_by(student_code_cath_name);
    auto ret = entries.end();
    size_t mid = entries.size() / 2;

    while (true) { // Binary search
        if (mid == entries.size()) {
            return ret;
        } else if (entries[mid].get_student_code() == student_code) {
            ret = entries.begin() + mid;
            break;
        } else if (entries[mid].get_student_code() > student_code) {
            mid = mid / 2;
        } else {
            mid = mid + mid / 2;
        }
    }

    while (true) {
        if ((ret - 1)->get_student_code() != student_code) {
            return ret;
        } else --ret;
    }
}

std::vector<StudentsClasses>::iterator AppStudentsClasses::search_by_class(uint16_t class_code) {
    sort_by(class_code_cath_name);
    auto ret = entries.end();
    size_t mid = entries.size() / 2;

    while (true) { // Binary search
        if (mid == entries.size()) {
            return ret;
        } else if (entries[mid].get_class_code() == class_code) {
            ret = entries.begin() + mid;
            break;
        } else if (entries[mid].get_class_code() > class_code) {
            mid = mid / 2;
        } else {
            mid = mid + mid / 2;
        }
    }

    while (true) {
        if ((ret - 1)->get_class_code() != class_code) {
            return ret;
        } else --ret;
    }
}


// Degub
void AppStudentsClasses::display() const {
    std::cout << this->student_code_cath_name << ','
              << this->student_name_cath_name << ','
              << this->uc_code_cath_name << ','
              << this->class_code_cath_name << '\n';
    for (const auto& e : this->entries) {
        e.display();
    }
}



