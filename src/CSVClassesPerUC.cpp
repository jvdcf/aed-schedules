/**
 * @file CSVClassesPerUC.cpp
 */
#include "CSVClassesPerUC.hpp"
#include "ClassesPerUC.hpp"
#include <sstream>
#include <string>
#include <algorithm>
#include <fstream>


/**
 * @brief This constructor receives a string containing all the lines of a csv file and creates the AppClassPerUC from it.
 * @details The cap parameter is the capacity of each class (30 by default).
 * Theoretical complexity: O(n), where n is the number of lines in the csv file.
 * @param csv
 * @param cap
 */
CSVClassPerUC::CSVClassPerUC(const std::string& csv, uint8_t cap) {
    this->cap = cap;

    // CSV file into memory
    std::ifstream file = std::ifstream(csv);
    std::string contents;
    std::ostringstream sstr;
    sstr << file.rdbuf();
    contents = sstr.str();

    // Parse string
    std::stringstream s(contents);
    std::string line;
    this->entries = std::vector<ClassPerUC>();
    getline(s, line, '\n');
    std::vector<std::string> bufs;
    parse_csv_line(line, bufs);
    this->uc_cath_name = bufs[0];
    this->class_cath_name = bufs[1];
    line.clear();
    while (std::getline(s, line, '\n')) {
        this->entries.push_back(ClassPerUC(line));
    }
}

/**
 * @brief Erases the contents of classes_per_uc.csv and saves there the updated values.
 */
CSVClassPerUC::~CSVClassPerUC() {
    std::ofstream ofs;
    ofs.open("../schedule/classes_per_uc.csv", std::ofstream::out | std::ofstream::trunc);
    ofs << uc_cath_name << ',' << class_cath_name << '\n';
    for (ClassPerUC entry: entries) {
        std::string value;
        entry.uc_to_str(value);
        ofs << value << ',';
        entry.class_to_str(value);
        ofs << value << ',' << '\n';
    }
    ofs.close();
}

/**
 * @brief This method prints the csv file.
 */
void CSVClassPerUC::display() {
    std::cout << this->uc_cath_name << ',' << this->class_cath_name << '\n';
    for (auto e : this->entries) {
        e.display();
    }
}

/**
 * @brief Sort the entries vector by the category parameter.
 * @details Available categories: UcCode, ClassCode, id.
 * Theoretical complexity: O(n log n), where n is the number of entries in the vector.
 * @param category
 */
void CSVClassPerUC::sort_by(std::string category) {
    if (category == uc_cath_name) {
        std::stable_sort(this->entries.begin(), this->entries.end(),
                         [](const ClassPerUC &first, const ClassPerUC &second) {
                             std::string first_uc, second_uc;
                             first.uc_to_str(first_uc);
                             second.uc_to_str(second_uc);
                             return first_uc < second_uc;
                         });
    } else if (category == class_cath_name) {
      std::stable_sort(this->entries.begin(), this->entries.end(),
                       [](const ClassPerUC &first, const ClassPerUC &second) {
                         return first.get_class_code() < second.get_class_code();
                       });
    } else if (category == "id") {
      std::stable_sort(this->entries.begin(), this->entries.end(),
                       [](const ClassPerUC &first, const ClassPerUC &second) {
                         return first.get_id() < second.get_id();
                       });
    } else {
        std::cerr << "Error: invalid category" << '\n';
        std::exit(1);
    }
}

/**
 * @brief Getter for the vector of ClassPerUC.
 * @return Pointer to entries.
 */
std::vector<ClassPerUC> *CSVClassPerUC::get_classes() {return &this->entries;}

/**
 * @brief Getter for the capacity of every class.
 * @return cap
 */
uint8_t CSVClassPerUC::get_cap() const {return cap;}
