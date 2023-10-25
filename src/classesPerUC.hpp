#include <cctype>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#ifndef CLASSPERUC_H
#define CLASSPERUC_H
void parse_csv_line(std::string s, std::vector<std::string> &res);
class ClassPerUC {
private:
  uint16_t uc_codes_;
  uint16_t class_codes_;
  // constexpr const static char *types_of_uc[256] = {
  //   ,[0]  = "IR"
  //   ,[14] = "SEESTE"};
  //   ,[16]   = "L.EIC"
  //   ,[64]  = "DDS"
  //   ,[67] = "IAPD"
  //   ,[138] = "UP"
  //   ,[184] = "IADE"
  //   ,[237] = "CSR"
  //   ,[249]  = "MPSAC"
  constexpr const static char *types_of_uc[256] = {
      "IR", "",       "",      "",      "", "", "", "", "",   "", "", "", "",
      "",   "SEESTE", "",      "L.EIC", "", "", "", "", "",   "", "", "", "",
      "",   "",       "",      "",      "", "", "", "", "",   "", "", "", "",
      "",   "",       "",      "",      "", "", "", "", "",   "", "", "", "",
      "",   "",       "",      "",      "", "", "", "", "",   "", "", "", "DDS",
      "",   "",       "IAPD",  "",      "", "", "", "", "",   "", "", "", "",
      "",   "",       "",      "",      "", "", "", "", "",   "", "", "", "",
      "",   "",       "",      "",      "", "", "", "", "",   "", "", "", "",
      "",   "",       "",      "",      "", "", "", "", "",   "", "", "", "",
      "",   "",       "",      "",      "", "", "", "", "",   "", "", "", "",
      "",   "",       "",      "",      "", "", "", "", "UP", "", "", "", "",
      "",   "",       "",      "",      "", "", "", "", "",   "", "", "", "",
      "",   "",       "",      "",      "", "", "", "", "",   "", "", "", "",
      "",   "",       "",      "",      "", "", "", "", "",   "", "", "", "",
      "",   "",       "IADE",  "",      "", "", "", "", "",   "", "", "", "",
      "",   "",       "",      "",      "", "", "", "", "",   "", "", "", "",
      "",   "",       "",      "",      "", "", "", "", "",   "", "", "", "",
      "",   "",       "",      "",      "", "", "", "", "",   "", "", "", "",
      "",   "",       "",      "CSR",   "", "", "", "", "",   "", "", "", "",
      "",   "",       "MPSAC", "",      "", "", "", "", "",
  };

public:
  ClassPerUC(std::string line);
  uint16_t parse_uc(std::string uc_code);
  uint16_t parse_class(std::string class_code);
  void class_to_str(std::string &out);
  void uc_to_str(std::string &out);
  void display();
};

#endif // !CLASSPERUC_H
