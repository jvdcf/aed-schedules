/**
 * @file CSVClasses.cpp
 */
#include "CSVClasses.hpp"
#include "Lesson.hpp"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>


/**
 * @brief This constructor receives a string containing all the lines of a csv file and creates the AppClass from it.
 * @param csv
 */
CSVClasses::CSVClasses(const std::string& csv) {
  // CSV file into memory
  std::ifstream file = std::ifstream(csv);
  std::string contents;
  std::ostringstream sstr;
  sstr << file.rdbuf();
  contents = sstr.str();

  // Parse string
  std::stringstream s(contents);
  std::string line;
  this->entries = std::vector<Lesson>();
  getline(s, line, '\n');
  line.clear();
  while (std::getline(s, line, '\n')) {
    this->entries.push_back(Lesson(line));
  }
}

/**
 * @brief Displays the contents of the class.
 */
void CSVClasses::display() {
  std::cout << "ClassCode" << ',' << "UcCode" << ',' << "WeekDay" << ',' << "StartHour"
            << ',' << "Duration" << ',' << "Type" << '\n';
  for (auto e : this->entries) {
    e.display();
  }
}

/**
 * @brief Sorts the entries.
 * @details Theoretical Complexity: O(n log n), n being the number of lines in the csv file.
 */
void CSVClasses::sort() {
  std::sort(this->entries.begin(), this->entries.end(), [](const Lesson &a, const Lesson &b) {
    if(a.get_id() == b.get_id()) {
      if (a.get_day() == b.get_day()) {
        if (a.get_start_hour() == b.get_start_hour()) {
          if (a.get_duration() == b.get_duration()) {
            return a.get_type() < b.get_type();
          } else return a.get_duration() < b.get_duration();
        } else return a.get_start_hour() < b.get_start_hour();
      } else return a.get_day() < b.get_day();
    } else return a.get_id() < b.get_id();
  ;});
}

/**
 * @brief Getter for the vector of Lessons
 * @return Pointer to lessons.
 */
std::vector<Lesson> *CSVClasses::get_lessons() {return &this->entries;}
