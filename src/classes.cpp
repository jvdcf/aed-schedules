#include "classes.hpp"
#include "Utils.hpp"
#include <iomanip>

using namespace std;

// Constructor:
Class::Class(std::string line) {
  std::vector<std::string> linebuf;
  parse_csv_line(line, linebuf);
  class_code_ = parse_class(linebuf[0]);
  uc_code_ = parse_uc(linebuf[1]);
  day = parse_day(linebuf[2]);
  start_hour = stof(linebuf[3]);
  duration = stof(linebuf[4]);
  type = parse_type(linebuf[5]);
}

//______________________________________________________________________________________________________________________
// Getters:
WeekDay Class::get_day() const { return day; }

double Class::get_start_hour() const { return start_hour; }

double Class::get_duration() const { return duration; }

Type Class::get_type() const { return type; }

//______________________________________________________________________________________________________________________
// Parsers:

WeekDay Class::parse_day(std::string day) {
  if (day == "Monday") {
    return WeekDay::MONDAY;
  } else if (day == "Tuesday") {
    return WeekDay::TUESDAY;
  } else if (day == "Wednesday") {
    return WeekDay::WEDNESDAY;
  } else if (day == "Thursday") {
    return WeekDay::THURSDAY;
  } else if (day == "Friday") {
    return WeekDay::FRIDAY;
  } else if (day == "Saturday") {
    return WeekDay::SATURDAY;
  } else {
    return WeekDay::SUNDAY;
  }
}

Type Class::parse_type(std::string type) {
  if (type == "T") {
    return Type::T;
  } else if (type == "TP") {
    return Type::TP;
  } else {
    return Type::PL;
  }
}

void Class::day_to_str(std::string &out) const {
  if (day == WeekDay::MONDAY) {
    out = "Monday";
  } else if (day == WeekDay::TUESDAY) {
    out = "Tuesday";
  } else if (day == WeekDay::WEDNESDAY) {
    out = "Wednesday";
  } else if (day == WeekDay::THURSDAY) {
    out = "Thursday";
  } else if (day == WeekDay::FRIDAY) {
    out = "Friday";
  } else if (day == WeekDay::SATURDAY) {
    out = "Saturday";
  } else {
    out = "Sunday";
  }
}

void Class::type_to_str(std::string &out) const {
  if (type == Type::T) {
    out = "T";
  } else if (type == Type::TP) {
    out = "TP";
  } else {
    out = "PL";
  }
}

//______________________________________________________________________________________________________________________
// Other Methods:
void Class::display() const {
  string uc;
  string cc;
  string dia;
  string tipo;
  uc_to_str(uc);
  class_to_str(cc);
  day_to_str(dia);
  type_to_str(tipo);
  std::cout << uc << "," << cc << "," << dia << "," << start_hour << ","
            << duration << "," << tipo << "\n";
}
