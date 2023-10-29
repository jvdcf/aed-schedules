/**
 * @file CSVClasses.hpp
 */
#ifndef APPCLASSES_H
#define APPCLASSES_H
#include "Lesson.hpp"
#include <string>
#include <vector>


class AppClass{
private:
    std::string class_cath_name;
    std::string uc_cath_name;
    std::string weekday_cath_name;
    std::string start_hour_cath_name;
    std::string duration_cath_name;
    std::string type_cath_name;
    std::vector<Lesson> entries;

public:
    AppClass(const std::string& csv);
    ~AppClass();
    void display();
    void sort_by(std::string category);
    std::vector<Lesson>::iterator search_by_uc(uint16_t uc_code);
    std::vector<Lesson>::iterator search_by_class(uint16_t class_code);
};


#endif // APPCLASSES_H