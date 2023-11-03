/**
 * @file ClassSchedule.hpp
 */
#ifndef CLASSSCHEDULE_H
#define CLASSSCHEDULE_H
#include <cstdint>
#include <vector>
#include "ClassesPerUC.hpp"
#include "Lesson.hpp"
#include "Student.hpp"


/**
 * @brief Representation of a class and their respective lessons.
 */
class ClassSchedule : public ClassPerUC {
private:
  /// Pointers to all of the students enrolled in this class.
  std::vector<Student*> students;
  /// Pointers to all of the lessons associated to this class.
  std::vector<Lesson*> classes;
  
public:
  ClassSchedule(uint16_t uc_code, uint16_t class_code);
  bool add_entry(Lesson* entry);
  bool remove_entry(Lesson* entry);
  void add_student(Student* s);
  bool remove_student(Student* s);
  uint64_t get_student_count() const;
  const std::vector<Student*>& get_students_enrolled();
  const std::vector<Lesson*> & get_class_schedule();

  void sort();

  std::string display() const;
};


#endif // CLASSSCHEDULE_H
