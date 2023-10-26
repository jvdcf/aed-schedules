#include "appClasses.hpp"
#include "Utils.hpp"
#include "classes.hpp"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>

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

/**
 * Erases the contents of classes.csv and saves there the updated values.
 */
AppClass::~AppClass() {
    std::ofstream ofs;
    ofs.open("../schedule/classes.csv", std::ofstream::out | std::ofstream::trunc);
    ofs << class_cath_name << ',' << uc_cath_name << ',' << weekday_cath_name << ',' << start_hour_cath_name
        << ',' << duration_cath_name << ',' << type_cath_name << '\n';
    for (Class entry: entries) {
        std::string value;
        entry.class_to_str(value);
        ofs << value << ',';
        entry.uc_to_str(value);
        ofs << value << ',';
        entry.day_to_str(value);
        ofs << value << ',';
        ofs << std::setprecision(3) << entry.get_start_hour() << ',';
        ofs << std::setprecision(2) << entry.get_duration() << ',';
        entry.type_to_str(value);
        ofs << value << ',' << '\n';
    }
    ofs.close();
}

const std::vector<Class> &AppClass::getEntries() const {
    return entries;
}

void AppClass::display() {
  std::cout << this->uc_cath_name << ',' << this->class_cath_name << ','
            << this->weekday_cath_name << ',' << this->start_hour_cath_name
            << ',' << this->duration_cath_name << ',' << this->type_cath_name
            << '\n';
  for (auto e : this->entries) {
    e.display();
  }
}

void AppClass::sort_by(std::string category) {
  if (category == uc_cath_name) {
    std::stable_sort(this->entries.begin(), this->entries.end(),
                     [](const Class &first, const Class &second) {
                         std::string first_uc, second_uc;
                         first.uc_to_str(first_uc);
                         second.uc_to_str(second_uc);
                         return first_uc < second_uc;
                     });
  } else if (category == class_cath_name) {
    std::stable_sort(this->entries.begin(), this->entries.end(),
                     [](const Class &first, const Class &second) {
                         return first.get_class_code() < second.get_class_code();
                     });
  } else if (category == weekday_cath_name) {
    std::stable_sort(this->entries.begin(), this->entries.end(),
                     [](const Class &first, const Class &second) {
                         return first.get_day() < second.get_day();
                     });
  } else if (category == start_hour_cath_name) {
    std::stable_sort(this->entries.begin(), this->entries.end(),
                     [](const Class &first, const Class &second) {
                         return first.get_start_hour() < second.get_start_hour();
                     });
  } else if (category == duration_cath_name) {
    std::stable_sort(this->entries.begin(), this->entries.end(),
                     [](const Class &first, const Class &second) {
                         return first.get_duration() < second.get_duration();
                     });
  } else if (category == type_cath_name) {
    std::stable_sort(this->entries.begin(), this->entries.end(),
                     [](const Class &first, const Class &second) {
                         return first.get_type() < second.get_type();
                     });
  } else {
      std::cerr << "Error: invalid category" << '\n';
      std::exit(1);
  }
}

std::vector<Class>::iterator AppClass::search_by_uc(
    uint16_t
        uc_code) { // Sorts the entries by UC and returns the iterator of the
                   // first found. If not found, returns a past-the-end pointer
  sort_by(uc_cath_name);
  std::vector<Class>::iterator ret = entries.end();
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
  // ret is an iterator to a class that has the desired uc_code. Let's now find
  // the first one in entries.
  while (true) {
    if ((ret - 1)->get_uc_code() != uc_code) {
      return ret;
    } else
      --ret;
  }
  return ret;
}

std::vector<Class>::iterator AppClass::search_by_class(uint16_t class_code) {
  sort_by(class_cath_name);
  std::vector<Class>::iterator ret = entries.end();
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
  // ret is an iterator to a class that has the desired class_code. Let's now
  // find the first one in entries.
  while (true) {
    if ((ret - 1)->get_class_code() != class_code) {
      return ret;
    } else
      --ret;
  }
  return ret;
}
