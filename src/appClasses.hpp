#include "classes.hpp"
#include <string>
#include <vector>

#ifndef APPCLASSES_H
#define APPCLASSES_H

class AppClass{
private:
    std::string class_cath_name;
    std::string uc_cath_name;
    std::string weekday_cath_name;
    std::string start_hour_cath_name;
    std::string duration_cath_name;
    std::string type_cath_name;
    std::vector<Class> entries;

public:
    AppClass(const std::string& csv);
    ~AppClass();
    void display();
    void sort_by(std::string category);
    std::vector<Class>::iterator search_by_class(uint16_t uc_code, uint16_t class_code);
    int count_classes(uint16_t uc_code) const;
};

#endif // APPCLASSES_H