/**
 * @file ClassSchedule.cpp
 */
#include "ClassSchedule.hpp"
#include <cstdio>
#include <sstream>
#include <vector>
#include <algorithm>

/**
 * @brief Constructor of the class.
 * @param uc_code
 * @param class_code
 */
ClassSchedule::ClassSchedule(uint16_t uc_code, uint16_t class_code) {
  this->uc_code_ = uc_code;
  this->class_code_ = class_code;
  this->classes = std::vector<Lesson*>();
  this->students = {};
}

/**
 * @brief Add one student to the list.
 * @details Theoretical complexity: O(n log n), where n is the number of students in the vector.
 * @param student_code
 */
void ClassSchedule::add_student(uint32_t student_code) {
  students.push_back(student_code);
  std::sort(this->students.begin(), this->students.end());
}

/**
 * @brief Remove one student from the list.
 * @details Theoretical complexity: O(n), where n is the number of students in the vector.
 * @param student_code
 */
void ClassSchedule::remove_student(uint32_t student_code) {
  for (auto itr = students.begin(); itr != students.end(); ++itr) {
    if (*itr == student_code) {
      students.erase(itr);
      break;
    }
  } 
}

/**
 * @brief Add a Lesson to the vector of this class.
 * @param c
 * @return bool (If the action is valid or not.)
 */
bool ClassSchedule::add_entry(Lesson* c) {
  if (c->get_id() != this->get_id()) {
    fprintf(stdout, "Error: Operation Invalid: Can't add a lesson to a schedule of a different class!");
    return false;
  }
  this->classes.push_back(c);
  return true;
}

/**
 * @brief Getter for student_count.
 * @return student_count
 */
uint64_t ClassSchedule::get_student_count() const {
  return this->students.size();
}

/**
 * @brief Getter for classes vector.
 * @return classes
 */
const std::vector<Lesson*> & ClassSchedule::get_class_schedule() {
  return this->classes;
}

/**
 * @brief Getter for students vector.
 * @return students
 */
const std::vector<uint32_t>& ClassSchedule::get_students_enrolled() {
  return this->students;
}

/**
 * @brief Sort all of the lesson pointers inside of the vector classes.
 * @details Theoretical complexity: O(n log n), where n is the number of lessons in the vector.
 */
void ClassSchedule::sort() {
  std::sort(this->classes.begin(), this->classes.end(), [](Lesson *a, Lesson *b) {
    if (a->get_day() == b->get_day()) {
      if (a->get_start_hour() == b->get_start_hour()) {
        if (a->get_duration() == b->get_duration()) {
          return a->get_type() < b->get_type();
        }
        else return a->get_duration() < b->get_duration();
      }
      else return a->get_start_hour() < b->get_start_hour();
    }
    else return a->get_day() < b->get_day();
  });
}

/**
 * @brief Prints to the screen the contents of this class.
 */
std::string ClassSchedule::display() const {
  std::stringstream s;
  std::string uc_,class_;
  this->uc_to_str(uc_);
  this->class_to_str(class_);
  s << "Uc: " << uc_ << "\nClass: " << class_ << "\n";
  for (auto i : this->classes) {
    s << "    " << i->display();
  }
  s << std::endl;
  return s.str();
}
