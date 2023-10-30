/**
 * @file Student.cpp
 */
#include "Student.hpp"
#include "Utils.hpp"
#include <cstdint>
#include <string>
#include <vector>

Student::Student(uint32_t code, std::string name) {
  this->code = code;
  this->name = name;
  this->classes = std::vector<ClassSchedule *>();
}

std::vector<ClassSchedule *> *Student::get_schedule() { return &this->classes; }
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
  if (this->classes.size() >= 7) return OperationResult::Error;

  // Class vacancy
  if (c->get_student_count() >= 30) return OperationResult::Error;

  // One class per UC
  for (auto clas: *this->get_schedule()) {
    if (clas->get_uc() == c->get_uc()) return OperationResult::Error;
  }

  // No time conflits
  std::vector<Lesson *> *new_lessons = c->get_class_schedule();
  for (ClassSchedule *a : this->classes) {
    std::vector<Lesson *> *lessons = a->get_class_schedule();
    for (Lesson *lesson : *lessons) {
      for (Lesson *new_lesson : *new_lessons) {
        if (lesson->get_day() == new_lesson->get_day()) {
          // if new_lesson starts in the middle of lesson:
          if (lesson->get_start_hour() < new_lesson->get_start_hour() &&
              new_lesson->get_start_hour() <
              (lesson->get_start_hour() + lesson->get_duration())) {
            if (lesson->get_type() == Type::T ||
                new_lesson->get_type() == Type::T) {
              return OperationResult::Conflicts; // We return conflicts so that
              // the handler function can ask
              // the user whether or not they
              // want to proceed.
            }
            return OperationResult::Error;
          }
          // if lesson starts in the middle of new_lesson:
          if (new_lesson->get_start_hour() < lesson->get_start_hour() &&
              lesson->get_start_hour() <
              (new_lesson->get_start_hour() + new_lesson->get_duration())) {
            if (lesson->get_type() == Type::T ||
                new_lesson->get_type() == Type::T) {
              return OperationResult::Conflicts;
            }
            return OperationResult::Error;
          }
        }
      }
    }
  }

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

void Student::remove_from_class(ClassSchedule *c) {
  c->remove_student();
  for (std::vector<ClassSchedule *>::iterator itr = this->classes.begin();
       itr != this->classes.end(); ++itr) {
    if (c == *itr) {
      this->classes.erase(itr);
      return;
    }
  }
}

OperationResult Student::switch_class_with(Student other,
                                           ClassSchedule *thisone,
                                           ClassSchedule *theoother) {
  return OperationResult::Success; // TODO
}

bool Student::operator<(const Student &other) const {
  return this->code < other.code;
}

uint32_t Student::get_code() const {
  return code;
}


