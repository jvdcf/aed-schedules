/**
 * @file CSVClassesPerUC.hpp
 */
#ifndef CSVCLASSESPERUC_HPP
#define CSVCLASSESPERUC_HPP
#include "ClassesPerUC.hpp"
#include <string>
#include <vector>


class CSVClassPerUC {
private:
  std::string uc_cath_name;
  std::string class_cath_name;
  std::vector<ClassPerUC> entries;
  uint8_t cap;  // Capacity on any class

public:
    CSVClassPerUC(const std::string& csv, uint8_t cap = 30);
    ~CSVClassPerUC();
    void display();
    void sort_by(std::string category);
};


#endif // CSVCLASSESPERUC_HPP
