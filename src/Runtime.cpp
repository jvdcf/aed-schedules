/**
 * @file Runtime.cpp
 */
#include "Runtime.hpp"
#include "ClassSchedule.hpp"
#include "Student.hpp"
#include "StudentsClasses.hpp"
#include "Utils.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

Runtime::Runtime(CSVStudentsClasses &sc, CSVClassPerUC &cpu, CSVClasses &c) {
  students_classes_ = &sc;
  cap = cpu.get_cap();
  is_batching = false;
  procs = std::queue<Process>();

  // 1. Populate lessons
  auto lessons = c.get_lessons();
  c.sort_by("id");

  // 2. Populate classSchedules
  cpu.sort_by("id");
  int idx = 0;
  for (ClassPerUC &entry : *cpu.get_classes()) {
    ClassSchedule cs(entry.get_uc_code(), entry.get_class_code());
    while (idx < lessons->size()) {
      if ((*lessons)[idx].get_id() == cs.get_id()) {
        cs.add_entry(&lessons->at(idx));
        ++idx;
        continue;
      }
      break;
    }
    classes.push_back(cs);
  }

  // 3. Populate students
  sc.sort_by(std::string("StudentCode"));
  auto sc_vector = sc.get_students();
  Student s(sc_vector->at(0).get_student_code(),
            sc_vector->at(0).get_student_name());

  for (const auto &i : *sc_vector) {
    if (i.get_student_code() == s.get_code()) {
      s.add_to_class(find_class(i.get_id()));
    } else {
      students.insert(s);
      s = Student(i.get_student_code(), i.get_student_name());
      s.add_to_class(find_class(i.get_id()));
    }
  }
}

/**
 * Since new classes are not created, the only file to be updated is the
 * student_classes.csv. Thus, the only CSV class that needs to be updated is the
 * CSVStudentClasses. To update this class, we create a new vector that will
 * substitute the entries attribute in CSVStudentClasses.
 * @brief Updates the data in the CSV classes.
 */
Runtime::~Runtime() {
  std::vector<StudentsClasses> entries;
  for (Student student : this->students) {
    for (ClassSchedule *classSchedule : student.get_schedule()) {
      std::ostringstream oss;
      oss << student.get_code() << ',' << student.get_name() << ','
          << classSchedule->get_uc_code() << ','
          << classSchedule->get_class_code() << ',';
      std::string line = oss.str();
      entries.push_back(StudentsClasses(line));
    }
  }
  students_classes_->set_students(entries);
}

/**
 * Using Binary Search, find the ClassSchedule inside of the vector classes with
 * the same uc_code ans class_code. Theoretical Complexity: O(log n)
 * @param id
 * @return Pointer to the found ClassSchedule
 */
ClassSchedule *Runtime::find_class(uint32_t id) {
  size_t high = classes.size();
  size_t low = 0;

  while (low <= high) {
    size_t mid = low + (high - low) / 2;
    if (classes[mid].get_id() == id)
      return &classes.at(mid);
    if (classes[mid].get_id() < id) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return nullptr;
}

void Runtime::run() {
  std::string in;
  std::istringstream stream;
  std::string buf;
  bool exit = false;
  std::vector<std::string> line;
  std::cout << "Welcome to SchedulEd. Type 'help' to learn more." << std::endl;
  while (!exit) {
    if (is_batching) {
      std::cout << "Batching> ";
    } else {
      std::cout << "> ";
    }
    getline(std::cin, in);
    stream = std::istringstream(in);
    while (std::getline(stream, buf, ' ')) {
      line.push_back(buf);
      buf.clear();
    }
    if (line.size() == 0) {
      in.clear();
      continue;
    }
    if (!is_batching) {
      process_args(line);
      in.clear();
      line.clear();
      while (procs.size() != 0) {
        Process p = procs.front();
        procs.pop();
        handle_process(p);
      }
    }
    in.clear();
  }
}

void Runtime::process_args(std::vector<std::string> args) {
  if (args[0] == "quit") {
    std::cout << "Quitting..." << std::endl;
    // TODO: Call saving functions
    std::exit(1);
  }
  if (args[0] == "remove") {
    if (args.size() != 3) {
      std::cerr << "ERROR: USAGE: remove takes two arguments: remove "
                << "<student_code> <uc_code>" << std::endl;
      return;
    } else {
      Process t(TypeOfRequest::Remove);
      t.add_operand(args[1]);
      t.add_operand(args[2]);
      procs.push(t);
      return;
    }
  }
  if (args[0] == "add") {
    if (args.size() != 4) {
      std::cerr << "ERROR: USAGE: add takes three arguments: add "
                << "<student_code> <uc_code> <class_code>" << std::endl;
      return;
    } else {
      Process t(TypeOfRequest::Add);
      t.add_operand(args[1]);
      t.add_operand(args[2]);
      t.add_operand(args[3]);
      procs.push(t);
      return;
    }
  }
  if (args[0] == "switch") {
    if (args.size() != 4) {
      std::cerr << "ERROR: USAGE: switch takes three arguments: switch "
                << "<student_code> <student_code> <uc_code>" << std::endl;
      return;
    } else {
      Process t(TypeOfRequest::Switch);
      t.add_operand(args[1]);
      t.add_operand(args[2]);
      t.add_operand(args[3]);
      procs.push(t);
      return;
    }
  }
  if (args[0] == "print") {
    if (args.size() != 2) {
      std::cerr << "ERROR: USAGE: print takes 1 argument: print <student_code>"
                << std::endl;
      return;
    } else {
      Process t(TypeOfRequest::Print);
      t.add_operand(args[1]);
      procs.push(t);
      return;
    }
  }

  if (args[0] == "help") {
    std::cout
        << "The available commands are:\n\n"
        << "    print:  takes 1 argument:  print  <student_code>\n"
        << "        Prints the student name, the student code and the student "
           "schedule.\n\n"
        << "    add:    takes 3 arguments: add    <student_code> <uc_code> "
           "<class_code>\n"
        << "        Adds a student to a class if possible.\n\n"
        << "    remove: takes 2 arguments: remove <student_code> <uc_code>\n"
        << "        Removes a student from a class if possible.\n\n"
        << "    switch: takes 3 arguments: switch <student_code> "
           "<student_code> <uc_code>\n"
        << "        Switches the class of two students.\n\n"
        << "    quit:   takes 0 arguments: quit\n"
        << "        Quits the program.\n\n"
        << "    help:   takes 0 arguments: help\n"
        << "        Prints this help." << std::endl;
    return;
  }

  std::cerr << "ERROR: No such command " << args[0]
            << ". Try typing 'help' to know the available commands."
            << std::endl;
}

void Runtime::handle_process(Process p) {
  std::vector<std::string> ops = p.get_ops();
  // handle remove
  if (p.get_type() == TypeOfRequest::Remove) {
    uint32_t student_code;
    try {
      student_code = std::stoi(ops[0]);
    } catch (std::exception e) {
      std::cerr << "ERROR: The string " << ops[0] << " is not a student_code."
                << std::endl;
      return;
    }
    uint16_t uc_code = parse_uc_gen(ops[1]);
    if (auto itr = students.find(Student(student_code, ""));
        itr != students.end()) {
      Student s = *itr;
      std::vector<ClassSchedule *> sched = s.get_schedule();
      for (ClassSchedule *a : sched) {
        if (a->get_uc_code() == uc_code) {
          // std::cout << "Lookup: " << uc_code << "\nFound: " <<
          // a->get_uc_code() << std::endl;
          s.remove_from_class(a);
          students.erase(s);
          students.insert(s);
          history.push(p);
          return;
        }
      }
    } else {
      std::cerr << "ERROR: There is no such student with code: " << student_code
                << std::endl;
    }
    return;
  }
  // End Remove

  if (p.get_type() == TypeOfRequest::Print) {
    uint32_t student_code;
    try {
      student_code = std::stoi(ops[0]);
    } catch (std::exception e) {
      std::cerr << "ERROR: The string " << ops[0] << " is not a student_code."
                << std::endl;
      return;
    }
    if (auto itr = students.find(Student(student_code, ""));
        itr != students.end()) {
      Student s = *itr;
      std::cout << "Name: " << s.get_name() << "\nCode: " << s.get_code()
                << std::endl;
      std::vector<ClassSchedule *> sched = s.get_schedule();
      for (auto i : sched) {
        i->display();
      }
    } else {
      std::cerr << "ERROR: There is no such student with code: " << student_code
                << std::endl;
    }
    return;
  }
}
void Runtime::save_all() {
  std::vector<StudentsClasses> ret;
  for (Student s : students) {
    for (ClassSchedule *sched : s.get_schedule()) {
      ret.push_back(StudentsClasses(sched->get_uc_code(),
                                    sched->get_class_code(), s.get_name(),
                                    s.get_code()));
    }
  }
  this->students_classes_->set_students(ret);
}
