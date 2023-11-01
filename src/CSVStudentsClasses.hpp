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
    std::string student_code_cath_name;
    std::string student_name_cath_name;
    std::string uc_cath_name;
    std::string class_cath_name;
    /// Vector with every line of the file
    std::vector<StudentsClasses> entries;

public:
    // Constructor
    CSVStudentsClasses(const std::string& csv);

    // Destructor
    virtual ~CSVStudentsClasses();

    // Methods
    void sort_by(const std::string& category);
    std::vector<StudentsClasses>::iterator search_by_student(uint32_t student_code);
    std::vector<StudentsClasses>::iterator search_by_uc(uint16_t uc_code);
    std::vector<StudentsClasses>::iterator search_by_class(uint16_t class_code);
    std::vector<StudentsClasses>* get_students();

    // Debug
    void display() const;
};


#endif // CSVSTUDENTCLASSES_H
