#include <cctype>
#include <cstdint>
#include <iostream>
#include <string>
#include "classesPerUC.hpp"

#ifndef CLASS_HPP
#define CLASS_HPP

enum class WeekDay {
  SUNDAY,
  MONDAY,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY,
};

enum class Type {
  T,
  TP,
  PL,
};

class Class : public ClassPerUC {
private:
  WeekDay day;
  float start_hour;
  float duration;
  Type type;

public:
  Class(std::string line); // Constructor

  // Getters:
  uint16_t getUcCode() const;

  uint16_t getClassCode() const;

  WeekDay getDay() const;

  double getStartHour() const;

  double getDuration() const;

  Type getType() const;

  // Parsers:
  uint16_t parse_uc(std::string uc_code);

  uint16_t parse_class(std::string class_code);

  WeekDay parse_day(std::string day);

  Type parse_type(std::string type);

  // To String:
  void day_to_str(std::string &out) const;

  void type_to_str(std::string &out) const;

  // Other Methods:
  void display() const override;
  //void display();
};

#endif // CLASS_HPP
