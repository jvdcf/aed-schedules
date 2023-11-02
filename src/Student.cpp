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
#include <algorithm>

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
 * @brief Verifies if there are any time conflicts between the lessons of a given vector of classes.
 * @details Theoretical complexity: O(n²), n being the number of lessons inside the vector.
 * @param c_sched
 * @param ignore_conflicts
 * @return
 */
OperationResult Student::is_overlapping(const std::vector<ClassSchedule *>& c_sched) {
  OperationResult result = OperationResult::Success;
  for (int i = 0; i < c_sched.size(); i++) {
    for (int j = i + 1; j < c_sched.size(); j++) {
      for (Lesson* l1: c_sched.at(i)->get_class_schedule()) {
        for (Lesson* l2: c_sched.at(j)->get_class_schedule()) {
          if (l1->get_day() != l2->get_day()) continue;
          if (l1->get_start_hour() + l1->get_duration() <= l2->get_start_hour()) continue;
          if (l2->get_start_hour() + l2->get_duration() <= l1->get_start_hour()) continue;

          if (l1->get_type() == Type::T || l2->get_type() == Type::T) {
            result = OperationResult::Conflicts;
            continue;
          }
          return OperationResult::Error;
        }
      }
    }
  }
  return result;
}

/**
 * @brief Verifies if this Student is enrolled in a given class, so that it can be removed later.
 * @details Theoretical complexity: O(log(n)), n being the number of classes.
 * @param c
 * @return bool
 */
bool Student::verify_remove(ClassSchedule* c) {
  return std::binary_search(this->classes.begin(), this->classes.end(), c);
}

/**
 * @brief Verifies if adding this class is legal or not.
 * @details The following rules need to be followed:
 * Number of UCs must be 7 or lower;
 * The class must have a vacancy;
 * No time conflicts;
 * Only one class per UC;
 * All classes must be balanced (Difference lower than or equal to 4).
 * Theoretical complexity: O(n²), n being the number of lessons inside the vector.
 * @param c
 * @return Error, Conflicts or Success
 */
OperationResult Student::verify_add(ClassSchedule *c) {
  // Number of UCs | O(1)
  if (this->classes.size() >= 7)
    return OperationResult::Error;

  // Class vacancy | O(1)
  if (c->get_student_count() >= 30)
    return OperationResult::Error;

  // One class per UC | O(n)
  for (auto clas : this->get_schedule()) {
    if (clas->get_uc_code() == c->get_uc_code())
      return OperationResult::Error;
  }

  // Balanced classes | O(n)
  std::vector<uint64_t> occupancy;
  for (ClassSchedule* class_ : this->get_schedule()) {
    occupancy.push_back(class_->get_student_count());
  }
  occupancy.push_back(c->get_student_count());
  auto [min, max] = std::minmax_element(occupancy.begin(), occupancy.end());
  if (*max - *min > 4) return OperationResult::Error;

  // No time conflicts | O(n²)
  std::vector<ClassSchedule *> c_sched = this->get_schedule();
  c_sched.push_back(c);
  OperationResult result = is_overlapping(c_sched);
  return result;
}

/**
 * @brief Verifies if switching classes is legal or not.
 * @details No time conflicts are allowed for both students.
 */
OperationResult Student::verify_switch(Student other, uint16_t uc_code) {
  ClassSchedule* this_class = find_class(uc_code);
  ClassSchedule* other_class = other.find_class(uc_code);

  std::vector<ClassSchedule *> sched = this->get_schedule();
  std::erase(sched, this_class);
  sched.push_back(other_class);
  OperationResult result = is_overlapping(sched);
  if (result != OperationResult::Success) return result;

  sched.clear();

  sched = other.get_schedule();
  std::erase(sched, other_class);
  sched.push_back(this_class);
  result = other.is_overlapping(sched);
  return result;
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
