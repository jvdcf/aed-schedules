#include "studentsClasses.hpp"
#include <string>
#include <vector>

class AppStudentsClasses {
private:
    std::string student_code_cath_name;
    std::string student_name_cath_name;
    std::string uc_cath_name;
    std::string class_cath_name;
    std::vector<StudentsClasses> entries;

public:
    // Constructor
    AppStudentsClasses(const std::string& csv);

    //Destructor
    virtual ~AppStudentsClasses();

    // Methods
    void sort_by(const std::string& category);
    std::vector<StudentsClasses>::iterator search_by_student(uint32_t student_code);
    std::vector<StudentsClasses>::iterator search_by_uc(uint16_t uc_code);
    std::vector<StudentsClasses>::iterator search_by_class(uint16_t class_code);

    // Debug
    void display() const;
};