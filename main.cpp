/**
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
#include <iostream>
#include <string>

int main(int argc, char** argv) {
  bool done_cpu = false;
  bool done_sc = false;
  bool done_c = false;
  if (argc != 7) {
    std::cerr << "USAGE: The program takes three files, with their specific flags prepending them. Example:\n\n" 
      << "    schdulEd -cpu classes_per_uc.csv -c classes.csv -sc students_classes.csv\n\n"
      << "Where '-cpu' is the flag that specifies a CSV file which contains the list of classes per each UC\n"
      << "Where '-c' is the flag that specifies a CSV file which contains the list of classes an their schedules\n"
      << "Where '-sc' is the flag that specifies a CSV file which contains the list of students and their association with each class\n"
      << std::endl;
    std::exit(1);
  }
  
  CSVClasses c;
  CSVClassPerUC cpu;
  CSVStudentsClasses sc;

  for (int i = 1; i < argc; i+=2) {
    if (std::string(argv[i]) == std::string("-cpu")) {
      done_cpu = std::string(argv[i+1]) != "-c" && std::string(argv[1]) != "-sc";
      cpu = CSVClassPerUC(argv[i+1]);
    }
    if (std::string(argv[i]) == std::string("-c")) {
      done_c = std::string(argv[i+1]) != "-cpu" && std::string(argv[1]) != "-sc";
      c = CSVClasses(argv[i+1]);
    }
    if (std::string(argv[i]) == std::string("-sc")) {
      done_sc = std::string(argv[i+1]) != "-cpu" && std::string(argv[1]) != "-c";
      sc = CSVStudentsClasses(argv[i+1]);
    }
  }

  if (done_c && done_sc && done_cpu) {
    Runtime rt(sc, cpu, c);
    rt.run();
  }
  
  return 0;
}
