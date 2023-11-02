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

  //std::vector<Lesson>* lessons;
  uint8_t cap;
  bool is_batching;

public:
  Runtime(CSVStudentsClasses &sc, CSVClassPerUC &cpu, CSVClasses &c);

  // Sorting

  // Searching
  ClassSchedule* find_class(uint32_t id);
  // TODO
  void run();
  void process_args(std::vector<std::string> args);
  void handle_process(Process p);
  void execute_queue();
  void save_all();
};


#endif //RUNTIME_H
