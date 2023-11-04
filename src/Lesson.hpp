/**
 * @file Lesson.hpp
 */
#ifndef LESSON_HPP
#define LESSON_HPP
#include <cctype>
#include <cstdint>
#include <iostream>
#include <string>
#include "ClassesPerUC.hpp"


/**
 * @brief The days of the week stored in a single byte.
 * @details Since it is quicker to compare numbers instead of strings and there are only 7 days in a week, we decided to store
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
  NONE,
};

/**
 * @brief The types of classes stored in a single byte.
 * @details Since it is quicker to compare numbers instead of strings and there are only 3 types of classes, we decided to store
 * the types as objects of this class.
 * This allows us to store the string value of the class type into a single byte.
 */
enum class Type {
  T,
  TP,
  PL,
};

/**
 * @brief A lesson from a given class and a representation of one line inside the file classes.csv
 */
class Lesson : public ClassPerUC {
private:
  /// The day of the week the class takes place.
  WeekDay day;
  /// The hour the class starts.
  float start_hour;
  /// How long the class lasts.
  float duration;
  /// The type of class: T, TP or PL.
  Type type;

public:
  Lesson(std::string line); // Constructor
  WeekDay get_day() const;
  double get_start_hour() const;
  double get_duration() const;
  Type get_type() const;
  WeekDay parse_day(std::string day);
  Type parse_type(std::string type);
  void day_to_str(std::string &out) const;
  void type_to_str(std::string &out) const;
  std::string display() const override;
};


#endif // LESSON_HPP
