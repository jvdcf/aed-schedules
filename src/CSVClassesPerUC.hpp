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
  std::string uc_cath_name;
  std::string class_cath_name;
  /// Vector with every line of the csv file
  std::vector<ClassPerUC> entries;
  /// Capacity on any class
  uint8_t cap;

public:
    CSVClassPerUC(const std::string& csv, uint8_t cap = 30);
    CSVClassPerUC();
    void display();
    void sort_by(std::string category);
    std::vector<ClassPerUC>* get_classes();
    uint8_t get_cap() const;
};


#endif // CSVCLASSESPERUC_HPP
