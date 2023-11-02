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

public:
    CSVStudentsClasses(const std::string& csv);
    std::vector<StudentsClasses>* get_students();
    void sort();
    void display() const;
};


#endif // CSVSTUDENTCLASSES_H
