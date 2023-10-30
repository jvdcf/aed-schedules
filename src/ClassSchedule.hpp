/**
 * @file ClassSchedule.hpp
 */
#ifndef CLASSSCHEDULE_H
#define CLASSSCHEDULE_H
#include <cstdint>
#include <vector>
#include "Lesson.hpp"


class ClassSchedule {
private:
  uint64_t n_students = 0;
  uint16_t uc_code;
  uint16_t class_code;
  std::vector<Lesson*> classes;
  
public:
  ClassSchedule(uint16_t uc_code, uint16_t class_code);
  bool add_entry(Lesson* entry);
  bool remove_entry(Lesson* entry);
  void add_student();
  void remove_student();
  uint64_t get_student_count() const;
  uint32_t get_id() const;
  uint16_t get_uc() const;
  uint16_t get_class() const;
  std::vector<Lesson*>* get_class_schedule();
};


#endif // CLASSSCHEDULE_H
