/**
 * @file CSVStudentsClasses.hpp
 */
#ifndef CSVSTUDENTCLASSES_H
#define CSVSTUDENTCLASSES_H
#include "StudentsClasses.hpp"
#include <string>
#include <vector>

/**
 * @brief Representation of the file students_classes.csv
 */
class CSVStudentsClasses {
private:
  /// Vector with every line of the file
  std::vector<StudentsClasses> entries;
  /// Target file to save
  std::string filename;

public:
  CSVStudentsClasses(const std::string &csv);
  CSVStudentsClasses();
  std::vector<StudentsClasses> *get_students();
  void set_students(const std::vector<StudentsClasses> &entries);
  void sort();
  void write_to_file();
  void set_filename(const std::string& name);
  std::string display() const;
};

#endif // CSVSTUDENTCLASSES_H
