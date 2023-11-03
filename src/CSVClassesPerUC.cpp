/**
 * @file CSVClassesPerUC.cpp
 */
#include "CSVClassesPerUC.hpp"
#include "ClassesPerUC.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

/**
 * @brief This constructor receives a string containing all the lines of a csv
 * file and creates the AppClassPerUC from it.
 * @details Theoretical complexity: O(n), where n is the number of lines in the csv file.
 * @param csv
 */
CSVClassPerUC::CSVClassPerUC(const std::string &csv) {
  // CSV file into memory
  std::ifstream file = std::ifstream(csv);
  std::string contents;
  std::ostringstream sstr;
  sstr << file.rdbuf();
  contents = sstr.str();

  // Parse string
  std::stringstream s(contents);
  std::string line;
  this->entries = std::vector<ClassPerUC>();
  if (!getline(s, line, '\n')) {
    std::cerr << "ERROR: CRITICAL: INVALID FILE CSVCLASSESPERUC" << std::endl;
    std::exit(1);
  }
  if (line != "UcCode,ClassCode") {
    std::cerr << "ERROR: CRITICAL: INVALID FILE CSVCLASSESPERUC" << std::endl;
    std::exit(1);
  }

  line.clear();
  while (std::getline(s, line, '\n')) {
    this->entries.push_back(ClassPerUC(line));
  }
}

CSVClassPerUC::CSVClassPerUC() { this->entries = std::vector<ClassPerUC>();}

/**
 * @brief This method prints the csv file.
 */
void CSVClassPerUC::display() {
  std::cout << "UcCode" << ',' << "ClassCode" << '\n';
  for (auto e : this->entries) {
    e.display();
  }
}

/**
 * @brief Sort the entries vector.
 * @details Order (from most important to least important): uc_code >
 * class_code. Theoretical complexity: O(n log n), where n is the number of
 * entries in the vector.
 */
void CSVClassPerUC::sort() {
  std::sort(this->entries.begin(), this->entries.end(),
            [](const ClassPerUC &first, const ClassPerUC &second) {
              return first.get_id() < second.get_id();
            });
}

/**
 * @brief Getter for the vector of ClassPerUC.
 * @return Pointer to entries.
 */
std::vector<ClassPerUC> *CSVClassPerUC::get_classes() { return &this->entries; }
