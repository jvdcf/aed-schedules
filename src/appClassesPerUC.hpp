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
    AppClassPerUC(std::string csv, uint8_t cap);
    ~AppClassPerUC();
    const std::vector<ClassPerUC> &getEntries() const;
    void display();
    void sort_by(std::string category);
};
