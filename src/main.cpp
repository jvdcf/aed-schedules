#include "app.h"
#include "Parser.h"
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>

int main() {
  std::ifstream s("../schedule/classes_per_uc.csv");
  std::string content;
  std::getline(s,content,'\0');
  AppCPU test = AppCPU(content);
  test.display();
}
