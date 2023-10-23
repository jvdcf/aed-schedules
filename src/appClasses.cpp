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
        sort(this->entries.begin(), this->entries.end(),
             [] (const Class & first, const Class & second) {return first.getUcCode() < second.getUcCode();});
    } else if (category == class_cath_name) {
        sort(this->entries.begin(), this->entries.end(),
             [] (const Class & first, const Class & second) {return first.getClassCode() < second.getClassCode();});
    } else if (category == weekday_cath_name) {
        sort(this->entries.begin(), this->entries.end(),
             [] (const Class & first, const Class & second) {return first.getDay() < second.getDay();});
    } else if (category == start_hour_cath_name) {
        sort(this->entries.begin(), this->entries.end(),
             [] (const Class & first, const Class & second) {return first.getStartHour() < second.getStartHour();});
    } else if (category == duration_cath_name) {
        sort(this->entries.begin(), this->entries.end(),
             [] (const Class & first, const Class & second) {return first.getDuration() < second.getDuration();});
    } else if (category == type_cath_name) {
        sort(this->entries.begin(), this->entries.end(),
             [] (const Class & first, const Class & second) {return first.getType() < second.getType();});
    }
}


std::vector<Class>::iterator AppClass::search_by_uc(uint16_t uc_code) { // Sorts the entries by UC and returns the iterator of the first found. If not found, returns a past-the-end pointer
    sort_by(uc_cath_name);
    vector<Class>::iterator ret = entries.end();
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
    // ret is an iterator to a class that has the desired uc_code. Let's now find the first one in entries.
    while (true) {
        if ((ret - 1)->getUcCode() != uc_code) {
            return ret;
        } else --ret;
    }
    return ret;
}

std::vector<Class>::iterator AppClass::search_by_class(uint16_t class_code) {
    sort_by(class_cath_name);
    vector<Class>::iterator ret = entries.end();
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
    // ret is an iterator to a class that has the desired class_code. Let's now find the first one in entries.
    while (true) {
        if ((ret - 1)->getClassCode() != class_code) {
            return ret;
        } else --ret;
    }
    return ret;
}