#ifndef DATA_H
#define DATA_H

#include <cstdint>
#include <vector>
#include "appClassesPerUC.hpp"
#include "appClasses.hpp"
#include "appStudentsClasses.hpp"

struct class_ocupance_struct {
  uint16_t class_code;
  uint8_t ocupance;
};

class Data {
private:
  AppClassPerUC app_classes_per_uc_;
  AppClass app_classes_;
  AppStudentsClasses app_students_classes_;

public:
  // Constructor
  Data(std::string& csv_classes_per_uc, uint8_t cap, std::string& csv_classes, std::string& csv_students_classes);

  // Listings
  static bool students_with_n_ucs(int n, std::vector<StudentsClasses*> &results);
  static bool class_ocupance(uint16_t uc_code, std::vector<class_ocupance_struct> &results);
  static bool schedule_of_student(uint32_t student_code, std::vector<Class*> &results);
  static bool classes_of_student(uint32_t student_code, std::vector<uint16_t> &results);

  static bool students_of_class(uint16_t class_code, std::vector<StudentsClasses *> &results);
  static bool students_of_uc(uint16_t uc_code, std::vector<StudentsClasses*> &results);
  static bool classes_of_uc(uint16_t uc_code, std::vector<Class*> &results);
};


#endif // DATA_H