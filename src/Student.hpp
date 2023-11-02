/**
 * @file Student.hpp
 */
#ifndef STUDENT_H
#define STUDENT_H
#include <cstdint>
#include "ClassSchedule.hpp"
#include "Utils.hpp"
#include <string>


/**
 * @brief A student and their respective classes.
 */
class Student {
private:
  /// The student's code.
  uint32_t code;
  /// The student's name.
  std::string name;
  /// Pointers to all of the classes associated to this student.
  std::vector<ClassSchedule*> classes;

  ClassSchedule* find_class(uint16_t uc_code);
  OperationResult is_overlapping(const std::vector<ClassSchedule*>& c_shed);

public:
  Student(uint32_t code, std::string name);
  uint32_t get_code() const;
  const std::string& get_name() const;

  bool operator<(const Student& other) const;
  std::vector<ClassSchedule*>& get_schedule();
  void add_to_class(ClassSchedule* c);
  OperationResult verify_add(ClassSchedule* c);
  OperationResult verify_switch(Student& other, uint16_t uc_code);
  bool verify_remove(ClassSchedule* c);
  void remove_from_class(ClassSchedule* c);
  void switch_class_with(Student& other, uint16_t uc_code);
  void sort();


};


#endif // STUDENT_H
