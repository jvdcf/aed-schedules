/**
 * @file Runtime.cpp
 */
#include "Runtime.hpp"
#include "ClassSchedule.hpp"
#include "Lesson.hpp"
#include "Student.hpp"
#include "StudentsClasses.hpp"
#include "Utils.hpp"
#include <algorithm>
#include <cstdlib>
#include <exception>
#include <iomanip>
#include <ios>
#include <iostream>
#include <limits>
#include <ostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

/**
 * @brief Organizes the data in the CSV objects in a more efficient way
 * @details Theoretical complexity: O(n * log n), n being the number of objects of each CSV class.
 * @param sc
 * @param cpu
 * @param c
 */
Runtime::Runtime(CSVStudentsClasses &sc, CSVClassPerUC &cpu, CSVClasses &c) {
  // 1. Preparations | O(n * log n)
  students_classes_ = &sc;
  procs = std::queue<Process>();
  auto lessons = c.get_lessons();
  c.sort();

  // 2. Populate classSchedules | O(m * log m + n * m)
  cpu.sort();
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

  // 3. Populate students | O(p * log p)
  sc.sort();
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
  students.insert(s);
}

/**
 * @brief Using Binary Search, find the ClassSchedule inside of the vector classes with
 * the same uc_code ans class_code.
 * @details Theoretical Complexity: O(log n), n being the number of classes.
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
  std::cerr << "WARNING: Tried to find a class for a student, but it does not "
               "exist in our database.\n";
  return nullptr;
}

/**
 * @brief Find all the classes with the same uc_code.
 * @details Theoretical Complexity: O(log n + m), n being the number of classes
 * and m being the distance between the first class with the uc_code and the pivot.
 * @param uc_code
 * @return Vector with pointers to the found ClassSchedules, or empty vector if
 * not found.
 */
std::vector<ClassSchedule *> Runtime::find_uc(uint16_t uc_code) {
  std::vector<ClassSchedule *> ret;
  size_t high = classes.size();
  size_t low = 0;

  while (low <= high) {
    size_t mid = low + (high - low) / 2;
    if (classes[mid].get_uc_code() < uc_code) {
      low = mid + 1;
    } else if (classes[mid].get_uc_code() > uc_code) {
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

// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief Reads the user requests and executes them.
 * @details The reading is done by the process_args method and the execution is done by the handle_process.
 */
void Runtime::run() {
  std::string in;
  std::istringstream stream;
  std::string buf;
  bool exit = false;
  std::vector<std::string> line;
  std::cout << "Welcome to SchedulEd. Type 'help' to learn more." << std::endl;
  while (!exit) {
    std::cout << "> ";
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
    process_args(line);
    in.clear();
    line.clear();
    while (procs.size() != 0) {
      Process p = procs.front();
      procs.pop();
      handle_process(p);
    }
    in.clear();
  }
}

/**
 * @brief reads the user commands and creates a process to be executed.
 * @param args
 */
void Runtime::process_args(std::vector<std::string> args) {
  if (args[0] == "quit") {
    char answer;
    std::cout << "Do you wish to save any changes you have made? [y/N]" << std::endl;
    std::cin >> std::noskipws >> answer;
    if (answer == 'y') {
      std::cout << "Saving..." << std::endl;
      this->save_all();
      this->students_classes_->write_to_file();
    }
    std::cout << "Quitting..." << std::endl;
    std::exit(0);
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
      std::cerr << "ERROR:   USAGE: print student takes 1 argument: print "
                   "student <student_code>\n"
                << "         USAGE: print uc takes 1 argument:      print uc "
                   "<uc_code>\n"
                << "         USAGE: print class takes 2 argument:   print "
                   "class <uc_code> <class_code>\n";
      return;
    } else if (args[1] == "student") {
      if (args.size() != 3) {
        std::cerr << "ERROR: USAGE: print student takes 1 argument: print "
                     "student <student_code>\n";
        return;
      } else {
        Process t(TypeOfRequest::Print_Student);
        t.add_operand(args[2]);
        procs.push(t);
        return;
      }
    } else if (args[1] == "uc") {
      if (args.size() != 3) {
        std::cerr
            << "ERROR: USAGE: print uc takes 1 argument: print uc <uc_code>\n";
        return;
      } else {
        Process t(TypeOfRequest::Print_UC);
        t.add_operand(args[2]);
        procs.push(t);
        return;
      }
    } else if (args[1] == "class") {
      if (args.size() != 4) {
        std::cerr << "ERROR: USAGE: print class takes 2 argument: print class "
                     "<uc_code> <class_code>\n";
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

  if (args[0] == "student_count") {
    Process t(TypeOfRequest::Print_Student_Count);
    procs.push(t);
    return;
  }

  if (args[0] == "enroll") {
    if (args.size() < 3) {
      std::cerr << "ERROR: USAGE: enroll <new_student_code> <new_student_name>" << std::endl;
      return;
    }
    Process t(TypeOfRequest::Enroll);
    for (int i = 1; i < args.size(); ++i) {
      t.add_operand(args[i]);
    }
    procs.push(t);
    return;
  }

  if (args[0] == "student_list") {
    if (args.size() == 2) {
      Process t(TypeOfRequest::Print_Student_List);
      t.add_operand(args[1]);
      procs.push(t);
      return;
    } else if (args.size() == 4) {
      Process t(TypeOfRequest::Print_Student_List);
      t.add_operand(args[1]);
      t.add_operand(args[2]);
      t.add_operand(args[3]);
      procs.push(t);
      return;
    } else {
      std::cerr << "ERROR: USAGE: student_list <'name'|'code'> [<first_position> "
                   "<number_of_students>]"
                << std::endl;
      return;
    }
  }

  if (args[0] == "save") {
    Process t(TypeOfRequest::Save);
    if (args.size() == 2) {
      t.add_operand(args[1]);
    }
    procs.push(t);
    return;
  }

    if (args[0] == "undo") {
        if (args.size() != 1) {
            std::cerr << "ERROR: USAGE: undo" << std::endl;
        } else {
            Process t(TypeOfRequest::Undo);
            procs.push(t);
        }
        return;
    }

  if (args[0] == "help") {
    std::cout
      << "The available commands are:\n"
      << "    print student:  takes 1 argument:       print student  <student_code>\n"
      << "        Prints the student name, enrolled classes and schedule.\n\n"
      << "    print uc:       takes 1 argument:       print uc       <uc_code>\n"
      << "        Prints all the classes associated with this UC.\n\n"
      << "    print class:    takes 2 argument:       print class    <uc_code> <class_code>\n"
      << "        Prints the number of students enrolled and the schedule.\n\n"
      << "    add:            takes 3 arguments:      add            <student_code> <uc_code> <class_code>\n"
      << "        Adds a student to a class if possible.\n\n"
      << "    remove:         takes 2 arguments:      remove         <student_code> <uc_code>\n"
      << "        Removes a student from a class if possible.\n\n"
      << "    switch:         takes 3 arguments:      switch         <student_code> <student_code> <uc_code>\n"
      << "        Switches the class of two students.\n\n"
      << "    student_count:  takes 0 arguments:      student_count\n"
      << "        Displays the number of students enrolled.\n\n"
      << "    student_list:   takes 1 or 3 arguments: student_count  <'name'|'code> [<first_position> <number_of_students>]\n"
      << "        Displays the students enrolled with the option (denoted in []) of specifying a beginning and number of students to display.\n\n"
      << "    undo:           takes 0 arguments:      undo\n"
      << "        Reverts the last change.\n\n"
      << "    quit:           takes 0 arguments:      quit\n"
      << "        Quits the program.\n\n"
      << "    enroll:         takes 2 arguments:      enroll         <new_student_code> <new_student_name>\n"
      << "        Creates a new student.\n\n"
      << "    save:           takes 0 or 1 arguments: save           [<filename>]\n"
      << "        Saves the changes to the csv which contains the students and their relations to the classes, and optionally takes a filename.\n\n"
      << "    help:           takes 0 arguments:      help\n"
      << "        Prints this help.\n\n";
    return;
  }

  std::cerr << "ERROR: No such command " << args[0]
            << ". Try typing 'help' to know the available commands."
            << std::endl;
}

/**
 * @brief Executes the commands.
 * @details Theoretical complexity of every command:
 * print student: O(log n + m * p), n being the number of students, m the number of classes and p the number of lessons of the class.
 * student_count: O(1)
 * student_list code: O(n), n being the number of students.
 * student_list name: O(n * log n + m), n being the number of students to show and m the number of students.
 * print class: O(log n + m log p + q), n being the number of classes, m the number of students from a class, p the number of students and q the number of lessons of the class.
 * print uc: O(log n + m + p), n being the number of classes, m the distance between the first class with the uc_code and the pivot and p the number of classes of the UC.
 * enroll: O(log n), n being the number of students.
 * add: O(n² + m), n being the number of classes a student is enrolled in and m the number of classes of the UC.
 * remove: O(n), n being the number of classes a student is enrolled in.
 * switch: O(n²), n being the number of classes a student is enrolled in.
 * save: O(n), n being the number of students.
 * @param p
 */
void Runtime::handle_process(Process p) {
  std::vector<std::string> ops = p.get_ops();

  // handle remove------------------------------------------------------------------------------------------------------
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
          std::string class_code;
          a->class_to_str(class_code);
          s.remove_from_class(a);
          students.erase(s);
          students.insert(s);
          p.add_operand(class_code);
          history.push(p);
          return;
        }
      }
      std::cerr << "ERROR: Student " << student_code
                << " is not enrolled in " << ops[1] << std::endl;
    } else {
      std::cerr << "ERROR: There is no such student with code: " << student_code
                << std::endl;
    }
    return;
  }

  // handle add--------------------------------------------------------------------------------------------------------
  if (p.get_type() == TypeOfRequest::Add) {
    uint32_t student_code;
    try {
      student_code = std::stoi(ops[0]);
    } catch (std::exception e) {
      std::cerr << "ERROR: The string " << ops[0] << " is not a student_code."
                << std::endl;
      return;
    }
    uint32_t id = (((uint32_t)parse_uc_gen(ops[1])) << 16) + parse_class_gen(ops[2]);
    ClassSchedule* target = find_class(id);
    if (target == nullptr) {
      std::cerr << "ERROR: Did not find class with id: " << id << std::endl;
      return;
    }
    if (auto itr = students.find(Student(student_code, "")); itr != students.end()) {
      Student s = *itr;
      OperationResult res = s.verify_add(target);
      if (res == OperationResult::Success) {
        // Balanced classes | O(n)
        std::vector<uint64_t> occupancy;
        double sum = 0.0;
        auto classes_ = this->find_uc(parse_uc_gen(ops[1]));
        for (ClassSchedule* class_ : classes_) {
          occupancy.push_back(class_->get_student_count() + (class_==target ? 1 : 0));
          sum += (double)class_->get_student_count();
        }
        double mean = sum / (double)classes_.size(); 
        double std_deviance_before = uc_variance(mean, classes_);
        sum += 1.0;
        for (ClassSchedule* class_ : classes_) {
          if (class_ == target) {
            class_->add_student(student_code);
          }
        }
        mean = sum / (double)classes_.size(); 
        double std_deviance_after = uc_variance(mean, classes_);
        auto [min, max] = std::minmax_element(occupancy.begin(), occupancy.end());
        for (ClassSchedule* class_ : classes_) {
          if (class_ == target) {
            class_->remove_student(student_code);
          }
        }
        if ((*max - *min > 4) && (std_deviance_after > std_deviance_before)) {
          std::cerr << "ERROR: Critical conflicts found: the classes will not be balanced. Skipping." << std::endl;
          return;
        }

        students.erase(s);
        s.add_to_class(target);
        students.insert(s);
        history.push(p);
        return;
      }
      if (res == OperationResult::Conflicts) {
        std::string answer;
        std::cout << "WARNING: Conflict found, some classes overlap non critically. Do you wish to proceed adding? [y/N] ";
        std::cin >> std::noskipws >> answer;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (answer == "y") {
          // Balanced classes | O(n)
          std::vector<uint64_t> occupancy;
          double sum = 0.0;
          auto classes_ = this->find_uc(parse_uc_gen(ops[1]));
          for (ClassSchedule* class_ : classes_) {
            occupancy.push_back(class_->get_student_count() + (class_==target ? 1 : 0));
            sum += (double)class_->get_student_count();
          }
          double mean = sum / (double)classes_.size(); 
          double std_deviance_before = uc_variance(mean, classes_);
          sum += 1.0;
          for (ClassSchedule* class_ : classes_) {
            if (class_ == target) {
              class_->add_student(student_code);
            }
          }
          mean = sum / (double)classes_.size(); 
          double std_deviance_after = uc_variance(mean, classes_);
          auto [min, max] = std::minmax_element(occupancy.begin(), occupancy.end());
          for (ClassSchedule* class_ : classes_) {
            if (class_ == target) {
              class_->remove_student(student_code);
            }
          }
          if ((*max - *min > 4) && (std_deviance_after > std_deviance_before)) {
            std::cerr << "ERROR: Critical conflicts found: the classes will not be balanced. Skipping." << std::endl;
            return;
          }

          students.erase(s);
          s.add_to_class(target);
          students.insert(s);
          history.push(p);
        }
        return;
      }
      if (res == OperationResult::Error) {
        std::cerr << "ERROR: Critical conflicts found: the schedule is not valid. Skipping." << std::endl;
        return;
      }
    }
  }

  // handle switch------------------------------------------------------------------------------------------------------
  if (p.get_type() == TypeOfRequest::Switch) {
    uint32_t student_code1;
    uint32_t student_code2;
    try {
      student_code1 = std::stoi(ops[0]);
    } catch (std::exception e) {
      std::cerr << "ERROR: The string " << ops[0] << " is not a student_code."
                << std::endl;
      return;
    }
    try {
      student_code2 = std::stoi(ops[1]);
    } catch (std::exception e) {
      std::cerr << "ERROR: The string " << ops[1] << " is not a student_code."
                << std::endl;
      return;
    }
    uint16_t uc_code = parse_uc_gen(ops[2]);
    if (auto itr = students.find(Student(student_code1, "")); itr != students.end()) {
      if (auto itr2 = students.find(Student(student_code2, "")); itr != students.end()) { 
        Student s1 = *itr;
        Student s2 = *itr2;
        OperationResult res = s1.verify_switch(s2, uc_code);
        if (res == OperationResult::Success) {
          students.erase(s1);
          students.erase(s2);
          s1.switch_class_with(s2, uc_code);
          history.push(p);
          students.insert(s1);
          students.insert(s2);
          return;
        }
        if (res == OperationResult::Conflicts) {
          std::string answer;
          std::cout << "WARNING: Conflict found, some classes overlap non critically. Do you wish to proceed switching? [y/N] ";
          std::cin >> std::noskipws >> answer;
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          if (answer == "y") {
            students.erase(s1);
            students.erase(s2);
            s1.switch_class_with(s2, uc_code);
            students.insert(s1);
            students.insert(s2);
            history.push(p);
          } 
          return;
        }
        if (res == OperationResult::Error) {
          std::cerr << "ERROR: Critical conflicts found: at least one schedule is not valid. Skipping." << std::endl;
          return;
        }
      }
    }
  }

  // handle print student-----------------------------------------------------------------------------------------------
  if (p.get_type() == TypeOfRequest::Print_Student) {
    uint32_t student_code;
    try {
      student_code = std::stoi(ops[0]);
    } catch (std::exception &e) {
      std::cerr << "ERROR: The string " << ops[0] << " is not a student_code."
                << std::endl;
      return;
    }
    if (auto itr = students.find(Student(student_code, ""));
        itr != students.end()) {
      Student s = *itr;

      // Name and Code:
      std::cout << "Name: " << s.get_name() << "\nCode: " << s.get_code()
                << "\n\n";

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
      std::vector<Lesson *> grouped;
      for (ClassSchedule *class_ : sched) {
        for (Lesson *lesson : class_->get_class_schedule()) {
          grouped.push_back(lesson);
        }
      }
      std::sort(grouped.begin(), grouped.end(), [](Lesson *a, Lesson *b) {
        if (a->get_day() == b->get_day()) {
          if (a->get_start_hour() == b->get_start_hour()) {
            if (a->get_duration() == b->get_duration()) {
              return a->get_type() < b->get_type();
            } else
              return a->get_duration() < b->get_duration();
          } else
            return a->get_start_hour() < b->get_start_hour();
        } else
          return a->get_day() < b->get_day();
      });

      print_schedule(grouped);

    } else {
      std::cerr << "ERROR: There is no such student with code: " << student_code
                << std::endl;
    }
    return;
  }

  // handle print uc----------------------------------------------------------------------------------------------------
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
      std::cout << class_code << ": " << i->get_student_count() << " students." << std::endl;
    }
    return;
  }

  // handle print class-------------------------------------------------------------------------------------------------
  if (p.get_type() == TypeOfRequest::Print_Class) {
    uint16_t uc_code = parse_uc_gen(ops[0]);
    uint16_t class_code = parse_class_gen(ops[1]);
    uint32_t id = ((uint32_t)uc_code << 16) + class_code;
    ClassSchedule *cs = find_class(id);

    if (cs == nullptr) {
      std::cerr << "ERROR: There is no such class.\n";
      return;
    }

    std::cout << "Class " << ops[1] << ":\n"
              << "Number of students: " << cs->get_student_count() << "\n\n";

    std::cout << "Students enrolled:\n";
    for (uint32_t s : cs->get_students_enrolled()) {
      if (auto itr = students.find(Student(s,"")); itr != students.end()) {
        Student stud = *itr;
        std::cout << "| Code: " << stud.get_code() << " Name: " << stud.get_name() << std::endl;
      } 
    }
    std::cout << std::endl;

    print_schedule(cs->get_class_schedule());
    return;
  }

  // handle student_count-----------------------------------------------------------------------------------------------
  if (p.get_type() == TypeOfRequest::Print_Student_Count) {
    std::cout << "There are " << this->students.size() << " students enrolled."
              << std::endl;
    return;
  }

  // handle student_list------------------------------------------------------------------------------------------------
  if (p.get_type() == TypeOfRequest::Print_Student_List) {
    std::vector<std::string> args = p.get_ops();
    uint64_t start = 0;
    uint64_t end = students.size();
    if (args.size() == 3) {
      try {
        start = std::stoi(args[1]);
        end = std::stoi(args[2]);
      } catch (std::exception e) {
        std::cerr << "ERROR: The function optionally takes two numbers as "
                     "arguments. At least one is not a number."
                  << std::endl;
        return;
      }
    }
    if (args[0] == "code") {
      for (auto itr = this->students.begin(); itr != students.end(); ++itr) {
        if (start == 0) {
          if (end != 0) {
            std::cout << "| Code: " << itr->get_code()
                      << " Name: " << itr->get_name() << std::endl;
            --end;
          } else {
            break;
          }
        } else {
          --start;
        }
      }
    } else if (args[0] == "name") {
      std::vector<Student> studs;
      for (auto itr = this->students.begin(); itr != students.end(); ++itr) {
        const Student& s = *itr;
        studs.push_back(s);
      }
      std::sort(studs.begin(), studs.end(), [](const Student& a, const Student& b) {
        return a.get_name() < b.get_name();
      });
      for (auto itr = studs.begin(); itr != studs.end(); ++itr) {
        if (start == 0) {
          if (end != 0) {
            std::cout << "| Code: " << itr->get_code()
                      << " Name: " << itr->get_name() << std::endl;
            --end;
          } else {
            break;
          }
        } else {
          --start;
        }
      }

    } else {
      std::cerr << "ERROR: Unknown sort directive '" << args[0] <<"', please consider using either 'code' or 'name'" << std::endl;
    }
    return;
  }

  // handle save--------------------------------------------------------------------------------------------------------
  if(p.get_type() == TypeOfRequest::Save) {
    if (p.get_ops().size() != 0) {
      this->students_classes_->set_filename(p.get_ops()[0]);
    }
    this->save_all();
    this->students_classes_->write_to_file();
    return;
  }

  // handle undo--------------------------------------------------------------------------------------------------------
  if (p.get_type() == TypeOfRequest::Undo) {
    if (history.empty()) {
      std::cerr << "ERROR: There is nothing to undo." << std::endl;
      return;
    }

    Process to_revert = history.top();
    history.pop();
    if (to_revert.get_type() == TypeOfRequest::Remove) {
      Process t = Process(TypeOfRequest::Add);
      t.add_operand(to_revert.get_ops()[0]);
      t.add_operand(to_revert.get_ops()[1]);
      t.add_operand(to_revert.get_ops()[2]);
      procs.push(t);
    }
    if (to_revert.get_type() == TypeOfRequest::Add) {
            Process t = Process(TypeOfRequest::Remove);
            t.add_operand(to_revert.get_ops()[0]);
            t.add_operand(to_revert.get_ops()[1]);
            procs.push(t);
    }
    if (to_revert.get_type() == TypeOfRequest::Switch) {
      procs.push(to_revert);
    }
    Process pop = Process(TypeOfRequest::PopHistory);
    procs.push(pop);
    return;
  }

  // handle pop
  if (p.get_type() == TypeOfRequest::PopHistory) {
      history.pop();
  }

  //handle enroll
  if (p.get_type() == TypeOfRequest::Enroll) {
    uint32_t student_code;
    try {
      student_code = std::stoi(ops[0]);
    } catch (std::exception e) {
      std::cerr << "ERROR: The string " << ops[0] << " is not a student_code."
                << std::endl;
      return;
    }
    std::string name = ops[1];
    for (int i = 2; i < ops.size(); ++i) {
      name += " " + ops[i];
    }
    if (auto itr = students.find(Student(student_code, "")); itr == students.end()) {
      students.insert(Student(student_code, name));
      return;
    } else {
      std::cerr << "ERROR: There is already such student with code " << student_code << "." << std::endl;
      return;
    }
  }
}

/**
 * @brief Prints the schedule from a vector of lessons.
 * @details Used in print student and print class.
 * @param schedule
 */
void Runtime::print_schedule(const std::vector<Lesson *> &schedule) const {
  std::cout << "Schedule:\n"
            << "(Type | Start Time | Duration | UC | Class)\n";
  int start_hour;
  int start_minutes;
  WeekDay day = WeekDay::NONE;
  std::string day_str;
  for (Lesson *lesson : schedule) {
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

    std::cout << std::setw(2) << type << std::setw(0) << " | " << std::setw(2)
              << start_hour << std::setw(0);
    std::cout << ':' << std::setw(2) << std::setfill('0') << start_minutes
              << std::setfill(' ');
    std::cout << " | " << std::setw(3) << lesson->get_duration() << "h"
              << " | " << std::setw(7) << uc << std::setw(0) << " | "
              << std::setw(7) << class_ << std::setw(0) << '\n';
  }
}

/**
 * @brief Updates the data in the CSV classes.
 * @details Since new classes are not created, the only file to be updated is the
 * student_classes.csv. Thus, the only CSV class that needs to be updated is the
 * CSVStudentClasses. To update this class, we create a new vector that will
 * substitute the entries attribute in CSVStudentClasses.
 * Theoretical complexity: O(n), n being the number of entries in the vector of the CSVStudentClasses.
 */
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
