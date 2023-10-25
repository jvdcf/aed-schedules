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
    this->uc_cath_name = bufs[2];
    this->class_cath_name = bufs[3];
    line.clear();
    while (std::getline(s,line,'\n')) {
        this->entries.push_back(StudentsClasses(line));
    }
}

// Methods
void AppStudentsClasses::sort_by(const std::string& category) {
    if (category == this->student_code_cath_name) {
        std::stable_sort(this->entries.begin(), this->entries.end(),
                  [](const StudentsClasses& a, const StudentsClasses& b) {return a.getStudentCode() < b.getStudentCode();});

    } else if (category == this->student_name_cath_name) {
        std::stable_sort(this->entries.begin(), this->entries.end(),
                  [](const StudentsClasses& a, const StudentsClasses& b) {return a.getStudentName() < b.getStudentName();});

    } else if (category == this->uc_cath_name) {
        std::stable_sort(this->entries.begin(), this->entries.end(),
                         [](const ClassPerUC &first, const ClassPerUC &second) {
                             std::string first_uc, second_uc;
                             first.uc_to_str(first_uc);
                             second.uc_to_str(second_uc);
                             return first_uc < second_uc;
                         });
    } else if (category == this->class_cath_name) {
        std::stable_sort(this->entries.begin(), this->entries.end(),
                         [](const ClassPerUC &first, const ClassPerUC &second) {
                             return first.getClassCode() < second.getClassCode();
                         });

    } else {
        std::cerr << "Error: invalid category" << '\n';
        std::exit(1);
    }
}

std::vector<StudentsClasses>::iterator AppStudentsClasses::search_by_uc(uint16_t uc_code) {
    sort_by(uc_cath_name);
    auto ret = entries.end();
    size_t mid = entries.size() / 2;

    while (true) { // Binary search
        if (mid == entries.size()) {
            return ret;
        } else if (entries[mid].getUcCode() == uc_code) {
            ret = entries.begin() + mid;
            break;
        } else if (entries[mid].getUcCode() > uc_code) {
            mid = mid / 2;
        } else {
            mid = mid + mid / 2;
        }
    }

    while (true) {
        if ((ret - 1)->getUcCode() != uc_code) {
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
        } else if (entries[mid].getStudentCode() == student_code) {
            ret = entries.begin() + mid;
            break;
        } else if (entries[mid].getStudentCode() > student_code) {
            mid = mid / 2;
        } else {
            mid = mid + mid / 2;
        }
    }

    while (true) {
        if ((ret - 1)->getStudentCode() != student_code) {
            return ret;
        } else --ret;
    }
}

std::vector<StudentsClasses>::iterator AppStudentsClasses::search_by_class(uint16_t class_code) {
    sort_by(class_cath_name);
    auto ret = entries.end();
    size_t mid = entries.size() / 2;

    while (true) { // Binary search
        if (mid == entries.size()) {
            return ret;
        } else if (entries[mid].getClassCode() == class_code) {
            ret = entries.begin() + mid;
            break;
        } else if (entries[mid].getClassCode() > class_code) {
            mid = mid / 2;
        } else {
            mid = mid + mid / 2;
        }
    }

    while (true) {
        if ((ret - 1)->getClassCode() != class_code) {
            return ret;
        } else --ret;
    }
}


// Degub
void AppStudentsClasses::display() const {
    std::cout << this->student_code_cath_name << ','
              << this->student_name_cath_name << ','
              << this->uc_cath_name << ','
              << this->class_cath_name << '\n';
    for (const auto& e : this->entries) {
        e.display();
    }
}



