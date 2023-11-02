/**
 * @file Student.cpp
 */
#include "Student.hpp"
#include "Utils.hpp"
#include <cstdint>
#include <iterator>
#include <string>
#include <vector>
#include <iostream>

/**
 * @brief The constructor assigns the code and name to the respective attributes.
 * @param code
 * @param name
 */
Student::Student(uint32_t code, std::string name) {
  this->code = code;
  this->name = name;
  this->classes = std::vector<ClassSchedule *>();
}

/**
 * @brief Getter for the student's schedule.
 * @return Pointer to classes
 */
std::vector<ClassSchedule *> &Student::get_schedule() { return this->classes; }

/**
 * @brief Verifies if adding this class is legal or not.
 * @details The following rules need to be followed:
 * Number of UCs must be 7 or lower;
 * The class must have a vacancy;
 * No time conflicts;
 * Only one class per UC;
 * All classes must be balanced (Difference lower than 4).
 *
 * @param c
 * @return Error, Conflicts or Success
 */
OperationResult Student::verify_add(ClassSchedule *c) {
  // Number of UCs
  if (this->classes.size() >= 7)
    return OperationResult::Error;

  // Class vacancy
  if (c->get_student_count() >= 30)
    return OperationResult::Error;

  // One class per UC
  for (auto clas : this->get_schedule()) {
    if (clas->get_uc_code() == c->get_uc_code())
      return OperationResult::Error;
  }

  // No time conflits
  OperationResult highest = OperationResult::Success;
  std::vector<Lesson *> new_lessons = c->get_class_schedule();
  for (ClassSchedule *a : this->classes) {
    std::vector<Lesson *> lessons = a->get_class_schedule();
    for (Lesson *lesson : lessons) {
      for (Lesson *new_lesson : new_lessons) {
        if (lesson->get_day() == new_lesson->get_day()) {
          // if new_lesson starts in the middle of lesson:
          if (lesson->get_start_hour() < new_lesson->get_start_hour() &&
              new_lesson->get_start_hour() <
                  (lesson->get_start_hour() + lesson->get_duration())) {
            if (lesson->get_type() == Type::T ||
                new_lesson->get_type() == Type::T) {
              highest = highest > OperationResult::Conflicts
                            ? highest
                            : OperationResult::Conflicts;
              // We return conflicts so that
              // the handler function can ask
              // the user whether or not they
              // want to proceed.
            }
            highest = highest > OperationResult::Error
                            ? highest
                            : OperationResult::Error;
          }
          // if lesson starts in the middle of new_lesson:
          if (new_lesson->get_start_hour() < lesson->get_start_hour() &&
              lesson->get_start_hour() <
                  (new_lesson->get_start_hour() + new_lesson->get_duration())) {
            if (lesson->get_type() == Type::T ||
                new_lesson->get_type() == Type::T) {
              highest = highest > OperationResult::Conflicts
                            ? highest
                            : OperationResult::Conflicts;
            }
            highest = highest > OperationResult::Error
                            ? highest
                            : OperationResult::Error;
          }
        }
      }
    }
  }
  return highest;
}

/**
 * @brief Verifies if switching classes is legal or not.
 * @details No time conflits are allowed for both students.
 */
OperationResult Student::verify_switch(Student other, uint16_t uc_code) {
  // TODO
  return OperationResult::Success;
}

/**
 * @brief Add this Student to a particular class.
 * @param c
 */
void Student::add_to_class(ClassSchedule *c) {
  c->add_student();
  this->classes.push_back(c);
}

/**
 * @brief Remove this Student from a given class.
 * @param c
 */
void Student::remove_from_class(ClassSchedule *c) {
  c->remove_student();
  int i = 0;
  for (i = 0; i < classes.size(); ++i) {
    if (classes[i] == c) {
      break;
    }
  }
  classes.erase(classes.begin() + i);
}

/**
 * Switch the classes of Student and other Student with a given uc_code
 * @param other
 * @param uc_code
 */
void Student::switch_class_with(Student other, uint16_t uc_code) {
  ClassSchedule* this_class = this->find_class(uc_code);
  ClassSchedule* other_class = other.find_class(uc_code);

  if (this_class == nullptr or other_class == nullptr) {
    std::cerr << "ERROR: uc_code " << uc_code << " not found inside student'\n";
  }

  this->remove_from_class(this_class);
  this->add_to_class(other_class);
  other.remove_from_class(other_class);
  other.add_to_class(this_class);
}

/**
 * @brief Overload of the < operator.
 * @param other
 * @return bool
 */
bool Student::operator<(const Student &other) const {
  return this->code < other.code;
}

/**
 * @brief Getter for code.
 * @return code
 */
uint32_t Student::get_code() const { return code; }


/**
 * @brief Verifies if this Student is enrolled in a given class, so that it can be removed later.
 * @param c
 * @return bool
 */
bool Student::verify_remove(ClassSchedule* c) {
  for (std::vector<ClassSchedule *>::iterator itr = this->classes.begin();
       itr != this->classes.end(); ++itr) {
    if (c == *itr) {
      return true;
    }
  }
  return false;
}

/**
 * @brief Find a class with a given uc_code.
 * @details Theoretical complexity: O(log(n)), n being the number of classes.
 * @param uc_code
 * @return
 */
ClassSchedule* Student::find_class(uint16_t uc_code) {
  size_t high = classes.size();
  size_t low = 0;

  while (low <= high) {
    size_t mid = low + (high - low) / 2;
    if (classes[mid]->get_uc_code() == uc_code) return classes.at(mid);
    if (classes[mid]->get_uc_code() < uc_code) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return nullptr;
}

/**
 * @brief Getter for name.
 * @return name
 */
const std::string& Student::get_name() const {return name;}
