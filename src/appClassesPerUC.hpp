#include "classesPerUC.hpp"
#include <string>
#include <vector>

class AppClassPerUC {
private:
  std::string uc_cath_name;
  std::string class_cath_name;
  std::vector<ClassPerUC> entries;

public:
    AppClassPerUC(std::string csv);
    void display();
    void sort_by(std::string category);
};
