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

/**
 * @brief Erases the contents of students_classes.csv and saves there the updated values.
 */
CSVStudentsClasses::~CSVStudentsClasses() {
    std::ofstream ofs;
    ofs.open("../schedule/students_classes.csv", std::ofstream::out | std::ofstream::trunc);
    ofs << student_code_cath_name << ',' << student_name_cath_name << ','
        << uc_cath_name << ',' << class_cath_name << '\n';
    for (StudentsClasses entry: entries) {
        std::string value;
        entry.student_code_to_str(value);
        ofs << value << ',';
        ofs << entry.get_student_name() << ',';
        entry.uc_to_str(value);
        ofs << value << ',';
        entry.class_to_str(value);
        ofs << value << ',' << '\n';
    }
    ofs.close();
}

// Methods
/**
 * @brief Sort the entries vector by the category parameter.
 * @details Available categories: UcCode, ClassCode, StudentCode, StudentName.
 * Theoretical complexity: O(n log n), where n is the number of entries in the vector.
 * @param category
 */
void CSVStudentsClasses::sort_by(const std::string& category) {
    if (category == "StudentCode") {
        std::stable_sort(this->entries.begin(), this->entries.end(),
                  [](const StudentsClasses& a, const StudentsClasses& b) {return a.get_student_code() < b.get_student_code();});

    } else if (category == "StudentName") {
        std::stable_sort(this->entries.begin(), this->entries.end(),
                  [](const StudentsClasses& a, const StudentsClasses& b) {return a.get_student_name() < b.get_student_name();});

    } else if (category == "UcCode") {
        std::stable_sort(this->entries.begin(), this->entries.end(),
                         [](const ClassPerUC &first, const ClassPerUC &second) {
                             std::string first_uc, second_uc;
                             first.uc_to_str(first_uc);
                             second.uc_to_str(second_uc);
                             return first_uc < second_uc;
                         });
    } else if (category == "ClassCode") {
        std::stable_sort(this->entries.begin(), this->entries.end(),
                         [](const ClassPerUC &first, const ClassPerUC &second) {
                             return first.get_class_code() < second.get_class_code();
                         });

    } else {
        std::cerr << "Error: invalid category" << '\n';
        std::exit(1);
    }
}

/**
 * @deprecated
 * @brief Search the lines for the first class with the given uc_code.
 * @param uc_code
 * @return Iterator to the first student with the given uc_code. If not found, returns a past-the-end pointer.
 */
std::vector<StudentsClasses>::iterator CSVStudentsClasses::search_by_uc(uint16_t uc_code) {
    sort_by(uc_cath_name);
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

/**
 * @deprecated
 * @brief Search the lines for the first class with the given student_code.
 * @param student_code
 * @return Iterator to the first class with the given student_code. If not found, returns a past-the-end pointer.
 */
std::vector<StudentsClasses>::iterator CSVStudentsClasses::search_by_student(uint32_t student_code) {
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

/**
 * @deprecated
 * @brief Search the lines for the first class with the given class_code.
 * @param class_code
 * @return Iterator to the first class with the given class_code. If not found, returns a past-the-end pointer.
 */
std::vector<StudentsClasses>::iterator CSVStudentsClasses::search_by_class(uint16_t class_code) {
    sort_by(class_cath_name);
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

// Debug
/**
 * @brief Displays the contents of the class.
 */
void CSVStudentsClasses::display() const {
    std::cout << this->student_code_cath_name << ','
              << this->student_name_cath_name << ','
              << this->uc_cath_name << ','
              << this->class_cath_name << '\n';
    for (const auto& e : this->entries) {
        e.display();
    }
}
/**
 * @brief Getter for the vector of StudentsClasses.
 * @return Pointer to entries
 */
std::vector<StudentsClasses> *CSVStudentsClasses::get_students() {return &this->entries;}
