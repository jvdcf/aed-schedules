/**
 * @file ClassSchedule.hpp
 */
#ifndef CLASSSCHEDULE_H
#define CLASSSCHEDULE_H
#include <cstdint>
#include <vector>
#include <string>
#include "ClassesPerUC.hpp"
#include "Lesson.hpp"


/**
 * @brief Representation of a class and their respective lessons.
 */
class ClassSchedule : public ClassPerUC {
private:
  /// Derivative attribute that indicates the number of students enrolled in this class.
  std::vector<uint32_t> students;
  /// Pointers to all of the lessons associated to this class.
  std::vector<Lesson*> classes;
  
public:
  ClassSchedule(uint16_t uc_code, uint16_t class_code);
  bool add_entry(Lesson* entry);
  void add_student(uint32_t s);
  void remove_student(uint32_t s);
  uint64_t get_student_count() const;
  const std::vector<uint32_t>& get_students_enrolled();
  const std::vector<Lesson*> & get_class_schedule();
  void sort();
  std::string display() const;
};


#endif // CLASSSCHEDULE_H
