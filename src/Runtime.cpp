/**
 * @file Runtime.cpp
 */
#include "Runtime.hpp"
#include <algorithm>


Runtime::Runtime(CSVStudentsClasses &sc, CSVClassPerUC &cpu, CSVClasses &c) {
  // 1. Populate lessons
  lessons = c.get_lessons();
  c.sort_by("id");

  // 2. Populate classSchedules
  cpu.sort_by("id");
  int idx = 0;
  for (ClassPerUC &entry: *cpu.get_classes()) {
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
  Student s(sc_vector->at(0).get_student_code(), sc_vector->at(0).get_student_name());

  for (const auto & i : *sc_vector) {
    if (i.get_student_code() == s.get_code()) {
      s.add_to_class(find_class(i.get_id()));
    } else {
      students.insert(s);
      s = Student(i.get_student_code(), i.get_student_name());
    }
  }
}

/**
 * Using Binary Search, find the ClassSchedule inside of the vector classes with the same uc_code ans class_code.
 * Theoretical Complexity: O(log n)
 * @param id
 * @return Pointer to the found ClassSchedule
 */
ClassSchedule* Runtime::find_class(uint32_t id) {
  size_t ret = classes.size();
  size_t mid = classes.size() / 2;

  while (true) { // Binary search
    if (mid == classes.size() or mid == 0) {
      return nullptr;
    } else if (classes[mid].get_id() == id) {
      return &classes.at(mid);
    } else if (classes[mid].get_id() > id) {
      mid = mid + mid / 2;
    } else {
      mid = mid / 2;
    }
  }
}
