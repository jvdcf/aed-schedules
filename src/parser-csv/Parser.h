#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>



class ClassPerUC {
private: 
  std::vector<uint16_t> uc_codes_;
  std::vector<uint16_t> class_codes_;


public:
  ClassPerUC(std::string csv);
  uint16_t parse_uc(std::string uc_code);  
  uint16_t parse_class(std::string class_code);
  void class_to_str(int idx, std::string& out); 
  void uc_to_str(int idx, std::string& out); 
  void display(); 
    
   
};




