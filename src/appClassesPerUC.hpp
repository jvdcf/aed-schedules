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
    AppClassPerUC(const std::string& csv, uint8_t cap = 30);
    ~AppClassPerUC();
    void display();
    void sort_by(std::string category);
    std::vector<ClassPerUC>::iterator search_by_uc(uint16_t uc_code) const;
    int count_classes(uint16_t uc_code) const;
};
