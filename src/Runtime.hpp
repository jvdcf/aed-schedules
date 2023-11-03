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

/**
 * @brief The "SchedulEd" interface and all of the logic behind the connections between the classes.
 */
class Runtime {
private:
  /// Where all of the students are stored.
  std::set<Student> students;
  /// Where all of the classes are stored.
  std::vector<ClassSchedule> classes;
  /// All of the process to be executed.
  std::queue<Process> procs;
  /// All of the processes that have been executed successfully.
  std::stack<Process> history;
  /// Pointer to the CSV representation. Used to save the data.
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
