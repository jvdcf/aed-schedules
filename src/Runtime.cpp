/**
 * @file Runtime.cpp
 */
#include "Runtime.hpp"
#include "ClassSchedule.hpp"
#include "Lesson.hpp"
#include "Student.hpp"
#include "Utils.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iomanip>
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
    cs.sort();
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

/**
 * @brief Find all the classes with the same uc_code.
 * @param uc_code
 * @return Vector with pointers to the found ClassSchedules, or empty vector if not found.
 */
std::vector<ClassSchedule *> Runtime::find_uc(uint16_t uc_code) {
  std::vector<ClassSchedule *> ret;
  size_t high = classes.size();
  size_t low = 0;

  while (low <= high) {
    size_t mid = low + (high - low) / 2;
    if (classes[mid].get_uc_code() < uc_code) {
      low = mid + 1;
    } else if (classes[mid].get_uc_code() > uc_code){
      high = mid - 1;
    } else { // == id
      while (classes[mid].get_uc_code() == uc_code) {
        mid--;
      }
      mid++;
      while (classes[mid].get_uc_code() == uc_code) {
        ret.push_back(&classes[mid]);
        mid++;
      }
      return ret;
    }
  }

  // If not found, return empty vector
  return ret;
}

// ----------------------------------------------------------------------------------------------------

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
    if (args.size() < 2) {
      std::cerr << "ERROR:   USAGE: print student takes 1 argument: print student <student_code>\n"
                << "         USAGE: print uc takes 1 argument:      print uc <uc_code>\n"
                << "         USAGE: print class takes 2 argument:   print class <uc_code> <class_code>\n";
      return;
    } else if (args[1] == "student") {
      if (args.size() != 3) {
        std::cerr << "ERROR: USAGE: print student takes 1 argument: print student <student_code>\n";
        return;
      } else {
        Process t(TypeOfRequest::Print_Student);
        t.add_operand(args[2]);
        procs.push(t);
        return;
      }
    } else if (args[1] == "uc") {
      if (args.size() != 3) {
        std::cerr << "ERROR: USAGE: print uc takes 1 argument: print uc <uc_code>\n";
        return;
      } else {
        Process t(TypeOfRequest::Print_UC);
        t.add_operand(args[2]);
        procs.push(t);
        return;
      }
    } else if (args[1] == "class") {
      if (args.size() != 4) {
        std::cerr << "ERROR: USAGE: print class takes 2 argument: print class <uc_code> <class_code>\n";
        return;
      } else {
        Process t(TypeOfRequest::Print_Class);
        t.add_operand(args[2]);
        t.add_operand(args[3]);
        procs.push(t);
        return;
      }
    } else {
      std::cerr << "ERROR: No such command " << args[0] << ' ' << args[1]
                << ". Try typing 'help' to know the available commands."
                << std::endl;
      return;
    }

  }

  if (args[0] == "help") {
    std::cout << "The available commands are:\n" <<
      "    print student:  takes 1 argument:  print student  <student_code>\n" <<
      "        Prints the student name, enrolled classes and schedule.\n\n" <<
      "    print uc:       takes 1 argument:  print uc       <uc_code>\n" <<
      "        Prints all the classes associated with this UC.\n\n" <<
      "    print class:    takes 2 argument:  print class    <uc_code> <class_code>\n" <<
      "        Prints the number of students enrolled and the schedule.\n\n" <<
      "    add:            takes 3 arguments: add            <student_code> <uc_code> <class_code>\n" <<
      "        Adds a student to a class if possible.\n\n" <<
      "    remove:         takes 2 arguments: remove         <student_code> <uc_code>\n" <<
      "        Removes a student from a class if possible.\n\n" <<
      "    switch:         takes 3 arguments: switch         <student_code> <student_code> <uc_code>\n" <<
      "        Switches the class of two students.\n\n" <<
      "    quit:           takes 0 arguments: quit\n" <<
      "        Quits the program.\n\n" <<
      "    help:           takes 0 arguments: help\n" <<
      "        Prints this help.\n\n";
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

  // handle print student
  if (p.get_type() == TypeOfRequest::Print_Student) {
    uint32_t student_code;
    try {
      student_code = std::stoi(ops[0]);
    } catch (std::exception& e) {
      std::cerr << "ERROR: The string " << ops[0] << " is not a student_code."
                << std::endl;
      return;
    }
    if (auto itr = students.find(Student(student_code, ""));
        itr != students.end()) {
      Student s = *itr;

      // Name and Code:
      std::cout << "Name: " << s.get_name() << "\nCode: " << s.get_code() << "\n\n";

      // Classes:
      std::cout << "Classes enrolled: \n";
      for (ClassSchedule *class_ : s.get_schedule()) {
        std::string class_code;
        class_->class_to_str(class_code);
        std::string uc_code;
        class_->uc_to_str(uc_code);
        std::cout << uc_code << ": " << class_code << std::endl;
      }
      std::cout << std::endl;

      // Schedule:
      // Group all Lessons into one Schedule
      std::vector<ClassSchedule *> sched = s.get_schedule();
      std::vector<Lesson*> grouped;
      for (ClassSchedule *class_ : sched) {
        for (Lesson *lesson : *class_->get_class_schedule()) {
          grouped.push_back(lesson);
        }
      }
      std::sort(grouped.begin(), grouped.end(), [](Lesson *a, Lesson *b) {
        if (a->get_day() == b->get_day()) {
          if (a->get_start_hour() == b->get_start_hour()) {
            if (a->get_duration() == b->get_duration()) {
              return a->get_type() < b->get_type();
            }
            else return a->get_duration() < b->get_duration();
          }
          else return a->get_start_hour() < b->get_start_hour();
        }
        else return a->get_day() < b->get_day();
      });

      print_schedule(grouped);

    } else {
      std::cerr << "ERROR: There is no such student with code: " << student_code
                << std::endl;
    }
    return;
  }

  // handle print uc
  if (p.get_type() == TypeOfRequest::Print_UC) {
    uint16_t uc_code = parse_uc_gen(ops[0]);
    std::vector<ClassSchedule *> classes_found = find_uc(uc_code);

    if (classes_found.empty()) {
      std::cerr << "ERROR: There is no such uc_code.\n";
      return;
    }

    std::cout << "Classes with uc_code " << ops[0] << ":\n";
    for (auto i : classes_found) {
      std::string class_code;
      i->class_to_str(class_code);
      std::cout << class_code << std::endl;
    }
    return;
  }

  // handle print class
  if (p.get_type() == TypeOfRequest::Print_Class) {
    uint16_t uc_code = parse_uc_gen(ops[0]);
    uint16_t class_code = parse_class_gen(ops[1]);
    uint32_t id = ((uint32_t)uc_code << 16) + class_code;
    ClassSchedule* cs = find_class(id);

    if (cs == nullptr) {
      std::cerr << "ERROR: There is no such class.\n";
      return;
    }

    std::cout << "Class " << ops[1] << ":\n"
              << "Number of students: " << cs->get_student_count() << '\n';

    print_schedule(*cs->get_class_schedule());
    return;
  }
}

void Runtime::print_schedule(const std::vector<Lesson *>& schedule) const {
  std::cout << "Schedule:\n" << "(Type | Start Time | Duration | UC | Class)\n";
  int start_hour;
  int start_minutes;
  WeekDay day = WeekDay::NONE;
  std::string day_str;
  for (Lesson *lesson: schedule) {
    if (lesson->get_day() != day) {
      day = lesson->get_day();
      lesson->day_to_str(day_str);
      std::cout << std::setw(19) << day_str << std::setw(0) << std::endl;
    }
    start_hour = static_cast<int>(lesson->get_start_hour());
    start_minutes = (lesson->get_start_hour() - start_hour) * 60;
    std::string type;
    lesson->type_to_str(type);
    std::string uc;
    lesson->uc_to_str(uc);
    std::string class_;
    lesson->class_to_str(class_);

    std::cout << std::setw(2) << type << std::setw(0) << " | " << std::setw(2) << start_hour << std::setw(0);
    std::cout << ':' << std::setw(2) << std::setfill('0') << start_minutes << std::setfill(' ');
    std::cout << " | " << std::setw(3) << lesson->get_duration() << "h"
              << " | " << std::setw(7) << uc << std::setw(0) << " | " << std::setw(7) << class_ << std::setw(0) << '\n';
  }
}
