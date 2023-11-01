/**
 * @file CSVStudentsClasses.hpp
 */
#ifndef CSVSTUDENTCLASSES_H
#define CSVSTUDENTCLASSES_H
#include "StudentsClasses.hpp"
#include <string>
#include <vector>


class CSVStudentsClasses {
private:
    std::string student_code_cath_name;
    std::string student_name_cath_name;
    std::string uc_cath_name;
    std::string class_cath_name;
    std::vector<StudentsClasses> entries;

public:
    // Constructor
    CSVStudentsClasses(const std::string& csv);

    // Destructor
    virtual ~CSVStudentsClasses();

    // Getter
    std::vector<StudentsClasses>* get_students();

    // Methods
    void sort_by(const std::string& category);
    std::vector<StudentsClasses>::iterator search_by_student(uint32_t student_code);
    std::vector<StudentsClasses>::iterator search_by_uc(uint16_t uc_code);
    std::vector<StudentsClasses>::iterator search_by_class(uint16_t class_code);

    // Debug
    void display() const;
};


#endif // CSVSTUDENTCLASSES_H
