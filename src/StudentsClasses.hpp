/**
 * @file StudentsClasses.hpp
 */
#ifndef STUDENTSCLASSES_H
#define STUDENTSCLASSES_H
#include <string>
#include <cstdint>
#include "ClassesPerUC.hpp"

/**
 * @details This stores the information of a line of the file students_classes.csv
 * @brief Stores a class that a student has in a UC.
 */
class StudentsClasses : public ClassPerUC {
private:
    /// Code of the student. See parse_student_code() for more info about the hash.
    uint32_t student_code_;
    /// Name of the student.
    std::string student_name_;

public:
    StudentsClasses(std::string& line);
    StudentsClasses(uint16_t uc_code, uint16_t class_code, const std::string& name, uint32_t student_code);
    uint32_t get_student_code() const;
    const std::string &get_student_name() const;
    uint32_t parse_student_code(const std::string& student_code) const;
    void student_code_to_str(std::string& student_code) const;
    std::string display() const override;
};


#endif // STUDENTSCLASSES_H
