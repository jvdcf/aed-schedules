/**
 * @file Runtime.hpp
 */
#ifndef RUNTIME_H
#define RUNTIME_H
#include "Student.hpp"
#include "ClassSchedule.hpp"
#include <set>
#include <vector>


class Runtime {
private:
  std::set<Student> students;
  std::vector<ClassSchedule> classes;

public:
  // TODO
};


#endif //RUNTIME_H
