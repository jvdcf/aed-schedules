/**
 * @file ClassSchedule.cpp
 */
#include "ClassSchedule.hpp"
#include <cstdint>
#include <cstdio>
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
  this->n_students = 0;
}

/**
 * @brief Add one student to the counter.
 */
void ClassSchedule::add_student() {n_students += 1;}
/**
 * @brief Remove one student of the counter.
 */
void ClassSchedule::remove_student() {n_students -= 1;}

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
 * @deprecated
 * @brief Remove a Lesson to the vector of this class.
 * @param c
 * @return bool (If the action is valid or not.)
 */
bool ClassSchedule::remove_entry(Lesson* c) {
  // Probably unecessary
  for (std::vector<Lesson*>::iterator itr = this->classes.begin();  itr != this->classes.end(); ++itr) {
    if (*itr == c) {
      this->classes.erase(itr);
      return true;
    }
  }
  return false;
}

/**
 * @brief Getter for student_count.
 * @return student_count
 */
uint64_t ClassSchedule::get_student_count() const {
  return this->n_students;
}

/**
 * @brief Getter for class_schedule.
 * @return class_schedule
 */
std::vector<Lesson*>* ClassSchedule::get_class_schedule() {
  return &this->classes;
}

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
void ClassSchedule::display() const {
  std::string uc_,class_;
  this->uc_to_str(uc_);
  this->class_to_str(class_);
  std::cout << "Uc: " << uc_ << "\nClass: " << class_ << "\n";
  for (auto i : this->classes) {
    std::cout << "    ";
    i->display();
  }
  std::cout << std::endl;
}

