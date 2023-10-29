/*
 * @file main.cpp
 * @brief Point of entry of the program.
 */

#include "src/appClasses.hpp"
#include "src/appClassesPerUC.hpp"
#include "src/appStudentsClasses.hpp"
#include "src/classes.hpp"
#include "src/classesPerUC.hpp"
#include "src/studentsClasses.hpp"
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
