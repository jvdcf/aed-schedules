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

  ClassSchedule* find_class(uint16_t uc_code);

public:
  Student(uint32_t code, std::string name);
  uint32_t get_code() const;
  bool operator<(const Student& other) const;
  std::vector<ClassSchedule*>& get_schedule();
  void add_to_class(ClassSchedule* c);
  OperationResult verify_add(ClassSchedule* c);
  OperationResult verify_switch(Student other, uint16_t uc_code);
  void remove_from_class(ClassSchedule* c);
  void switch_class_with(Student other, uint16_t uc_code);


};


#endif // STUDENT_H