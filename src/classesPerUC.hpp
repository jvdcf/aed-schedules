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
  //   ,[10]  = "IR"
  //   ,[26]   = "L.EIC"
  //   ,[35]  = "MPSAC"
  //   ,[74]  = "DDS"
  //   ,[151] = "CSR"
  //   ,[173] = "IAPD"
  //   ,[194] = "IADE"
  //   ,[212] = "UP"
  //   ,[216] = "SEESTE"};
  constexpr const static char *types_of_uc[256] = {
      "",       "", "",      "", "", "",     "", "",    "",   "", "IR", "",
      "",       "", "",      "", "", "",     "", "",    "",   "", "",   "",
      "",       "", "L.EIC", "", "", "",     "", "",    "",   "", "",   "MPSAC",
      "",       "", "",      "", "", "",     "", "",    "",   "", "",   "",
      "",       "", "",      "", "", "",     "", "",    "",   "", "",   "",
      "",       "", "",      "", "", "",     "", "",    "",   "", "",   "",
      "",       "", "DDS",   "", "", "",     "", "",    "",   "", "",   "",
      "",       "", "",      "", "", "",     "", "",    "",   "", "",   "",
      "",       "", "",      "", "", "",     "", "",    "",   "", "",   "",
      "",       "", "",      "", "", "",     "", "",    "",   "", "",   "",
      "",       "", "",      "", "", "",     "", "",    "",   "", "",   "",
      "",       "", "",      "", "", "",     "", "",    "",   "", "",   "",
      "",       "", "",      "", "", "",     "", "CSR", "",   "", "",   "",
      "",       "", "",      "", "", "",     "", "",    "",   "", "",   "",
      "",       "", "",      "", "", "IAPD", "", "",    "",   "", "",   "",
      "",       "", "",      "", "", "",     "", "",    "",   "", "",   "",
      "",       "", "IADE",  "", "", "",     "", "",    "",   "", "",   "",
      "",       "", "",      "", "", "",     "", "",    "UP", "", "",   "",
      "SEESTE", "", "",      "", "", "",     "", "",    "",   "", "",   "",
      "",       "", "",      "", "", "",     "", "",    "",   "", "",   "",
      "",       "", "",      "", "", "",     "", "",    "",   "", "",   "",
      "",       "", "",
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
