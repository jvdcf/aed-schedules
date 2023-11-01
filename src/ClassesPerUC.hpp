/**
 * @file ClassesPerUC.hpp
 */
#ifndef CLASSPERUC_H
#define CLASSPERUC_H
#include <cctype>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>


void parse_csv_line(std::string s, std::vector<std::string> &res);

/**
 * @brief Class representation of one line inside the file classes_per_uc.
 */
class ClassPerUC {
protected:
  /// Code of curricular unit. See parse_uc() for more info about the hash.
  uint16_t uc_code_;
  /// Code of class. See parse_class() for more info about the hash.
  uint16_t class_code_;

  /**
   * @brief Lookup table for the names of the UCs. Used in uc_to_str();
   * @details constexpr const static char *types_of_uc[256] = {
   *   [0]  = "IR"
   *   ,[14] = "SEESTE"
   *   ,[16]   = "L.EIC"
   *   ,[64]  = "DDS"
   *   ,[67] = "IAPD"
   *   ,[138] = "UP"
   *   ,[184] = "IADE"
   *   ,[237] = "CSR"
   *   ,[249]  = "MPSAC"
   * };
   */

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
    ClassPerUC();
    uint16_t get_uc_code() const;
    uint16_t get_class_code() const;
    uint32_t get_id() const;
    uint16_t parse_uc(std::string uc_code);
    uint16_t parse_class(std::string class_code);
    void class_to_str(std::string &out) const;
    void uc_to_str(std::string &out) const;
  

  virtual void display() const;
};


#endif // !CLASSPERUC_H
