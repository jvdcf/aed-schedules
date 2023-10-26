#include "classesPerUC.hpp"
#include <string>
#include <vector>

class AppClassPerUC {
private:
  std::string uc_cath_name;
  std::string class_cath_name;
  std::vector<ClassPerUC> entries;
  uint8_t cap;  // Capacity on any class

public:
    AppClassPerUC(const std::string& csv, uint8_t cap);
    ~AppClassPerUC();
    void display();
    void sort_by(std::string category);
};
