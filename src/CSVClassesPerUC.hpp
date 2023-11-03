/**
 * @file CSVClassesPerUC.hpp
 */
#ifndef CSVCLASSESPERUC_HPP
#define CSVCLASSESPERUC_HPP
#include "ClassesPerUC.hpp"
#include <string>
#include <vector>

/**
 * @brief Representation of the file classes_per_uc.csv
 */
class CSVClassPerUC {
private:
  /// Vector with every line of the csv file
  std::vector<ClassPerUC> entries;

public:
    CSVClassPerUC(const std::string& csv);
    CSVClassPerUC();
    void display();
    void sort();
    std::vector<ClassPerUC>* get_classes();
    uint8_t get_cap() const;
};


#endif // CSVCLASSESPERUC_HPP
