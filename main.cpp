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
 int cap = 30;

  // AppClassesPerUC
  std::ifstream file1 =  std::ifstream("schedule/classes_per_uc.csv");
  std::string contents1;
  std::ostringstream sstr1;
  sstr1 << file1.rdbuf();
  contents1 = sstr1.str();
  AppClassPerUC cpu = AppClassPerUC(contents1, cap);
  cpu.display();

  // AppStudentsClasses
  std::ifstream file2 = std::ifstream("schedule/students_classes.csv");
  std::string contents2;
  std::ostringstream sstr2;
  sstr2 << file2.rdbuf();
  contents2 = sstr2.str();
  AppStudentsClasses sc(contents2);
  sc.display();

  // AppClass
  std::ifstream file3 = std::ifstream("schedule/classes.csv");
  std::string contents3;
  std::ostringstream sstr3;
  sstr3 << file3.rdbuf();
  contents3 = sstr3.str();
  AppClass ac(contents3);
  ac.display();

  return 0;
}
