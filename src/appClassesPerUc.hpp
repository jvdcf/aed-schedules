#include "classesPerUc.hpp"
#include <string>
#include <vector>


class AppCPU {
  private:
    std::string uc_cath_name;
    std::string class_cath_name;
    std::vector<ClassPerUC> entries;
  public:
    AppCPU(std::string csv);
    void display();
    void sort_by(std::string category);
};
