#include "appClasses.hpp"
#include "classes.hpp"
#include "Utils.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

AppClass::AppClass(std::string csv) {
    std::stringstream s(csv);
    std::string line;
    this->entries = std::vector<Class>();
    getline(s, line, '\n');
    std::vector<std::string> bufs;
    parse_csv_line(line, bufs);
    this->uc_cath_name = bufs[0];
    this->class_cath_name = bufs[1];
    this->weekday_cath_name = bufs[2];
    this->start_hour_cath_name = bufs[3];
    this->duration_cath_name = bufs[4];
    this->type_cath_name = bufs[5];
    line.clear();
    while (std::getline(s, line, '\n')) {
        this->entries.push_back(Class(line));
    }
}

void AppClass::display() {
    cout << this->uc_cath_name << ',' << this->class_cath_name << ',' << this->weekday_cath_name << ','
         << this->start_hour_cath_name << ',' << this->duration_cath_name << ',' << this->type_cath_name << '\n';
    for (auto e : this->entries) {
        e.display();
    }
}

void AppClass::sort_by(std::string category) {
    if (category == uc_cath_name) {
        vector<int> i = vector<int>();
        sort(i.begin(), i.end(), [] (const Class & first, const Class & second) {return first.getUcCode() < first.getUcCode()});
        this->entries.
    } else if (category == class_cath_name) {

    } else if (category == weekday_cath_name) {

    } else if (category == start_hour_cath_name) {

    } else if (category == duration_cath_name) {

    } else if (category == type_cath_name) {

    }
}
