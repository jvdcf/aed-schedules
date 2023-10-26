#include "Data.hpp"

Data::Data(std::string& csv_classes_per_uc, uint8_t cap, std::string& csv_classes, std::string& csv_students_classes):
          app_classes_per_uc_(csv_classes_per_uc, cap), app_classes_(csv_classes), app_students_classes_(csv_students_classes) {}

// ------------------------------------------------------------------------------------------------------------------------------

bool Data::students_with_n_ucs(int n, std::vector<StudentsClasses *> &results) {
  return false;
}

bool Data::class_ocupance(uint16_t uc_code, std::vector<class_ocupance_struct> &results) {
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

/**
 * This function appends to the results parameter (passed by reference) pointers to every StudentClasses object
 * that has the desired uc_code.
 * @param uc_code
 * @param results
 * @return true if found any class with that uc_code and false otherwise.
 */
// Nota: O user input para uc_code vai ser em string. Antes de executar esta função, é preciso converter o uc_code para hash.
bool Data::students_of_uc(uint16_t uc_code, std::vector<StudentsClasses *> &results) {
    bool ret = false;
    app_students_classes_.sort_by("UcCode");
    for (StudentsClasses entry: app_students_classes_.getEntries()) {
        if (entry.get_uc_code() == uc_code) {
            ret = true;
            results.push_back(&entry);
        } else if (ret and entry.get_uc_code() != uc_code) {
            break; // If true, from now on the entries won't have the wanted uc_code. So, we break the cycle.
        }
    }
    return ret;
}

/**
 * This function appends to the results parameter (passed by reference) pointers to every Class object
 * that has the desired uc_code
 * @param uc_code
 * @param results
 * @return true if found any class with that uc_code and false otherwise.
 */
// Nota: O user input para uc_code vai ser em string. Antes de executar esta função, é preciso converter o uc_code para hash.
bool Data::classes_of_uc(uint16_t uc_code, std::vector<Class *> &results) {
    bool ret = false;
    app_classes_.sort_by("UcCode");
    for (Class entry: app_classes_.getEntries()) {
        if (entry.get_uc_code() == uc_code) {
            ret = true;
            results.push_back(& entry);
        } else if (ret and entry.get_uc_code() != uc_code) {
            break; // If true, from now on the entries won't have the wanted uc_code. So, we break the cycle.
        }
    }
    return ret;
}
