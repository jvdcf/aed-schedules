/**
 * @file Student.hpp
 */
#ifndef STUDENT_H
#define STUDENT_H
#include <cstdint>
#include "ClassSchedule.hpp"
#include "Utils.hpp"
#include <string>


class Student {
private:
  uint32_t code;
  std::string name;
  std::vector<ClassSchedule*> classes;
public:
  Student(uint32_t code, std::string name);
  uint32_t get_code() const;
  bool operator<(const Student& other) const;
  std::vector<ClassSchedule*>& get_schedule();
  void add_to_class(ClassSchedule* c);
  OperationResult verify_add(ClassSchedule* c);
  void remove_from_class(ClassSchedule* c);
  OperationResult switch_class_with(Student other, ClassSchedule* thisone, ClassSchedule* theother);
};


#endif // STUDENT_H