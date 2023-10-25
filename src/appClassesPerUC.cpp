#include "appClassesPerUC.hpp"
#include "classesPerUC.hpp"
#include <sstream>
#include <string>
#include <algorithm>
#include <fstream>

AppClassPerUC::AppClassPerUC(std::string csv) {
    std::stringstream s(csv);
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
 * Erases the contents of classes_per_uc.csv and saves there the updated values.
 */
AppClassPerUC::~AppClassPerUC() {
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

void AppClassPerUC::display() {
    std::cout << this->uc_cath_name << ',' << this->class_cath_name << '\n';
    for (auto e : this->entries) {
        e.display();
    }
}

void AppClassPerUC::sort_by(std::string category) {
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
    } else {
        std::cerr << "Error: invalid category" << '\n';
        std::exit(1);
    }
}
