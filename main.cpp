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

int main() {
  std::ifstream file =  std::ifstream("schedule/classes_per_uc.csv");
  std::string contents;
  std::ostringstream sstr;
  sstr << file.rdbuf();
  contents = sstr.str();
  AppCPU cpu = AppCPU(contents);
  cpu.display();

  //std::cout << "Hello, World!" << std::endl;
  return 0;
}
