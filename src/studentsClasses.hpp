#include <string>
#include <cstdint>
#include "classesPerUC.hpp"
#ifndef STUDENTSCLASSES_H
#define STUDENTSCLASSES_H

class StudentsClasses : public ClassPerUC {
private:
    uint32_t student_code_;
    std::string student_name_;
public:
    // Constructor
    StudentsClasses(std::string& line);

    // Getters
    uint32_t get_student_code() const;
    std::string get_student_name() const;
    uint16_t get_uc_code() const;
    uint16_t get_class_code() const;

    // Parsers
    uint32_t parse_student_code(const std::string& student_code) const;
    uint16_t parse_uc(const std::string& uc_code) const;
    uint16_t parse_class(std::string class_code) const;

    // String format
    void student_code_to_str(std::string& student_code) const;
    // void student_name_to_str(std::string& student_name) const; (= get_student_name())
    void uc_code_to_str(std::string& uc_code) const;
    void class_code_to_str(std::string& class_code) const;

    // Debug
    void display() const override;
};

#endif // STUDENTSCLASSES_H
