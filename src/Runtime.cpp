/**
 * @file Runtime.cpp
 */
#include "Runtime.hpp"
#include "ClassSchedule.hpp"
#include "Student.hpp"
#include "Utils.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <exception>
#include <iostream>
#include <ostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

Runtime::Runtime(CSVStudentsClasses &sc, CSVClassPerUC &cpu, CSVClasses &c) {
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
  if (args[0] == "remove") {
    if (args.size() != 3) {
      std::cerr << "ERROR: USAGE: remove takes two arguments: remove " << "<student_code> <uc_code>" << std::endl;
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
      std::cerr << "ERROR: USAGE: add takes three arguments: add " <<
                      "<student_code> <uc_code> <class_code>" << std::endl;
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
      std::cerr << "ERROR: USAGE: switch takes three arguments: switch " <<
                      "<student_code> <student_code> <uc_code>\n" << std::endl;
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
}



void Runtime::handle_process(Process p) {
  std::vector<std::string> ops = p.get_ops();
  // handle remove
  if (p.get_type() == TypeOfRequest::Remove) {
    uint32_t student_code;
    try {
      student_code = stoi(ops[0]);
    } catch (std::exception e) {
      std::cerr << "ERROR: The string " << ops[0].c_str() << " is not a student_code." << std::endl;
      return;
    }
    uint16_t uc_code = parse_uc_gen(ops[1]);
    if (auto itr = students.find(Student(student_code, "")); itr != students.end()) {
      Student s = *itr;
      std::vector<ClassSchedule*> sched = s.get_schedule();
      for (auto a : sched) {
        if (a->get_uc() == uc_code) {
          s.remove_from_class(a); 
          history.push(p);
          return;
        }
      }
    } else {
      std::cerr << "ERROR: There is no such student with code: " << student_code << std::endl;
    }
    return;
  }
  // End Remove
}
