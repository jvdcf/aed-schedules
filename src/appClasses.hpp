#include "classes.hpp"
#include <string>
#include <vector>

#ifndef APPCLASSES_H
#define APPCLASSES_H

class AppClass{
private:
    std::string uc_cath_name;
    std::string class_cath_name;
    std::string weekday_cath_name;
    std::string start_hour_cath_name;
    std::string duration_cath_name;
    std::string type_cath_name;
    std::vector<Class> entries;

public:
    AppClass(std::string csv);
    void display();
    void sort_by(std::string category);
};

#endif // APPCLASSES_H