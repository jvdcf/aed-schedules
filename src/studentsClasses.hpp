#include <string>
#include <cstdint>
#ifndef STUDENTSCLASSES_H
#define STUDENTSCLASSES_H

class StudentsClasses {
private:
    uint32_t student_code_;
    std::string student_name_;
    uint16_t uc_code_;
    uint16_t class_code_;
    constexpr const static char *types_of_uc[] = {
            "L.EIC", "UP", "IAPD", "CSR", "IADE", "IR", "MPSAC", "DDS", "SEESTE"};

public:
    // Constructor
    StudentsClasses(std::string line);

    // Parsers
    uint32_t parse_student_code(std::string student_code);
    uint16_t parse_uc(std::string uc_code);
    uint16_t parse_class(std::string class_code);

    // String format
    void student_code_to_str(std::string& student_code);
    void student_name_to_str(std::string& student_name);
    void uc_code_to_str(std::string& uc_code);
    void class_code_to_str(std::string& class_code);

    // Debug
    void display();
};

#endif // STUDENTSCLASSES_H