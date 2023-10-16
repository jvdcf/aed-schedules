#include "Parser.h"
#include <string>
#include <vector>


class AppCPU {
  private:
    std::vector<ClassPerUC> entries;
  public:
    AppCPU(std::string csv);
    void display();
};
