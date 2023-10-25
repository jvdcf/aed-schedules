#include <cctype>
#include <cstdint>
#include <iostream>
#include <string>
#include "classesPerUC.hpp"

#ifndef CLASS_HPP
#define CLASS_HPP

/**
 * Since it is quicker to compare numbers instead of strings and there are only 7 days in a week, we decided to store
 * the days as objects of this class.
 * This allows us to store the string value of the week day into a single byte.
 */
enum class WeekDay {
  SUNDAY,
  MONDAY,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY,
};

/**
 * Since it is quicker to compare numbers instead of strings and there are only 3 types of classes, we decided to store
 * the types as objects of this class.
 * This allows us to store the string value of the class type into a single byte.
 */
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
  WeekDay get_day() const;

  double get_start_hour() const;

  double get_duration() const;

  Type get_type() const;

  // Parsers:
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
