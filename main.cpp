/*
 * @file main.cpp
 * @brief Point of entry of the program.
 */
#include "src/CSVClasses.hpp"
#include "src/CSVClassesPerUC.hpp"
#include "src/CSVStudentsClasses.hpp"
#include "src/ClassesPerUC.hpp"
#include "src/StudentsClasses.hpp"
#include "src/Lesson.hpp"
#include "src/ClassSchedule.hpp"
#include "src/Student.hpp"
#include "src/Runtime.hpp"
#include "src/Utils.hpp"

int main(int argc, char** argv) {
  CSVClassPerUC cpu("schedule/classes_per_uc.csv");
  cpu.display();

  CSVStudentsClasses sc("schedule/students_classes.csv");
  sc.display();

  CSVClasses ac("schedule/classes.csv");
  ac.display();

  return 0;
}
