#include "Data.hpp"

Data::Data(std::string* csv_classes_per_uc, uint8_t cap, std::string* csv_classes, std::string* csv_students_classes) {
  app_classes_per_uc_ = AppClassPerUC(*csv_classes_per_uc, cap);
  app_classes_ = AppClass(*csv_classes);
  app_students_classes_ = AppStudentsClasses(*csv_students_classes);
}

// ----------------------------------------------------------------------------------------------

bool Data::students_with_n_ucs(int n, std::vector<StudentsClasses *> &results) {
  return false;
}

bool Data::class_ocupance(uint16_t uc_code, std::vector<class_ocupance> &results) {
  return false;
}

bool Data::schedule_of_student(uint32_t student_code, std::vector<Class *> &results) {
  return false;
}

bool Data::classes_of_student(uint32_t student_code, std::vector<uint16_t> &results) {
  return false;
}

bool Data::students_of_class(uint16_t class_code, std::vector<StudentsClasses *> &results) {
  return false;
}

bool Data::students_of_uc(uint16_t uc_code, std::vector<StudentsClasses *> &results) {
  return false;
}

bool Data::classes_of_uc(uint16_t uc_code, std::vector<Class *> &results) {
  return false;
}
