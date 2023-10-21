#include "appClassesPerUC.hpp"
#include <sstream>
#include <string>
#include "Parser.h"

AppCPU::AppCPU(std::string csv) {
    std::stringstream s(csv);
    std::string line;
    this->entries = std::vector<ClassPerUC>();
    getline(s,line,'\n');
    std::vector<std::string> bufs;
    parse_csv_line(line,bufs);
    this->uc_cath_name = bufs[0];
    this->class_cath_name = bufs[1];
    line.clear();
    while (std::getline(s,line,'\n')) {
        this->entries.push_back(ClassPerUC(line));
    }
}


void AppCPU::display() {
    std::cout << this->uc_cath_name << ',' << this->class_cath_name << '\n';
    for (auto e : this->entries) {
        e.display();
    }
}
