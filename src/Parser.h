#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

#ifndef CLASSPERUC_H
#define CLASSPERUC_H

class ClassPerUC {
private: 
  uint16_t uc_codes_;
  uint16_t class_codes_;


public:
  ClassPerUC(std::string line);
  uint16_t parse_uc(std::string uc_code);  
  uint16_t parse_class(std::string class_code);
  void class_to_str( std::string& out); 
  void uc_to_str(std::string& out); 
  void display(); 
};

#endif // !CLASSPERUC_H



