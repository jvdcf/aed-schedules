/**
 * @file CSVClasses.hpp
 */
#ifndef APPCLASSES_H
#define APPCLASSES_H
#include "Lesson.hpp"
#include <string>
#include <vector>

/**
 * @brief Class representation of the file classes.csv
 */
class CSVClasses {
private:
    /// Vector with every line of the file
    std::vector<Lesson> entries;

public:
    CSVClasses(const std::string& csv);
    std::vector<Lesson>* get_lessons();
    void display();
    void sort();
};


#endif // APPCLASSES_H
