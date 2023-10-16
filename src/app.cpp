#include "app.h"
#include <sstream>
#include <string>

AppCPU::AppCPU(std::string csv) {
  std::stringstream s(csv);
  std::string line;
  while (std::getline(s,line,'\n')) {
    this->entries.push_back(ClassPerUC(line)); 
  }
}


void AppCPU::display() {
  for (auto e : this->entries) {
    e.display();
  }
}
