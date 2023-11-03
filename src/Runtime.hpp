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
#include "Process.hpp"
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>


class Runtime {
private:
  std::set<Student> students;
  std::vector<ClassSchedule> classes;
  std::queue<Process> procs;
  std::stack<Process> history;
  CSVStudentsClasses * students_classes_;

  // Searching
  ClassSchedule* find_class(uint32_t id);
  std::vector<ClassSchedule*> find_uc(uint16_t uc_code);

  // Helper Methods
  void process_args(std::vector<std::string> args);
  void handle_process(Process p);
  void save_all();
  void print_schedule(const std::vector<Lesson*>& schedule) const;

public:
  // Constructor
  Runtime(CSVStudentsClasses &sc, CSVClassPerUC &cpu, CSVClasses &c);

  // Runner
  void run();
};


#endif //RUNTIME_H
