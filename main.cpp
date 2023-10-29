#include "src/CSVClasses.hpp"
#include "src/CSVClassesPerUC.hpp"
#include "src/CSVStudentsClasses.hpp"
#include "src/Lesson.hpp"
#include "src/ClassesPerUC.hpp"
#include "src/StudentsClasses.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main(int argc, char** argv) {
  AppClassPerUC cpu = AppClassPerUC("schedule/classes_per_uc.csv");
  cpu.display();

  AppStudentsClasses sc("schedule/students_classes.csv");
  sc.display();

  AppClass ac("schedule/classes.csv");
  ac.display();

  return 0;
}
