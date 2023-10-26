#include "classesPerUC.hpp"
#include <string>
#include <vector>

class AppClassPerUC {
private:
  std::string uc_cath_name;
  std::string class_cath_name;
  std::vector<ClassPerUC> entries;
  int cap;

public:
    AppClassPerUC(std::string csv, int cap);
    ~AppClassPerUC();
    void display();
    void sort_by(std::string category);
};
