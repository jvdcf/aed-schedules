/**
 * @file Runtime.hpp
 */
#ifndef RUNTIME_H
#define RUNTIME_H
#include "Student.hpp"
#include "ClassSchedule.hpp"
#include "Lesson.hpp"
#include "CSVClasses.hpp"
#include "CSVClassesPerUC.hpp"
#include "CSVStudentsClasses.hpp"
#include <set>
#include <vector>


class Runtime {
private:
  std::set<Student> students;
  std::vector<ClassSchedule> classes;
  //std::vector<Lesson>* lessons;
  uint8_t cap;

public:
  Runtime(CSVStudentsClasses &sc, CSVClassPerUC &cpu, CSVClasses &c);

  // Sorting

  // Searching
  ClassSchedule* find_class(uint32_t id);
  // TODO
};


#endif //RUNTIME_H
