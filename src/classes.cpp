#include "classes.hpp"
#include "Utils.hpp"
#include <iomanip>

using namespace std;

// Constructor:
Class::Class(std::string line) {
  std::vector<std::string> linebuf;
  parse_csv_line(line, linebuf);
  class_code = parse_class(linebuf[0]);
  uc_code = parse_uc(linebuf[1]);
  day = parse_day(linebuf[2]);
  start_hour = stof(linebuf[3]);
  duration = stof(linebuf[4]);
  type = parse_type(linebuf[5]);
}

//______________________________________________________________________________________________________________________
// Getters:
unsigned short Class::getUcCode() const { return uc_code; }

unsigned short Class::getClassCode() const { return class_code; }

WeekDay Class::getDay() const { return day; }

double Class::getStartHour() const { return start_hour; }

double Class::getDuration() const { return duration; }

Type Class::getType() const { return type; }

//______________________________________________________________________________________________________________________
// Parsers:
uint16_t Class::parse_uc(std::string uc_code) {
  uint64_t hash = 5381;
  std::string num_part;
  for (char c : uc_code) {
    if (!isnum(c)) {
      hash = (hash << 5) + hash + c;
    }
    if (isnum(c)) {
      num_part.push_back(c);
    }
  }
  try {
    uint8_t num = 0;
    if (num_part != "") {
      num = std::stoi(num_part);
    }
    return (uint16_t)((hash % 256) << 8) + (uint16_t)(num);
  } catch (std::invalid_argument &e) {
    std::cerr << e.what() << " uc: failed to parse" << '\n';
    std::exit(1);
  }
}

uint16_t Class::parse_class(std::string class_code) {
  uint8_t year = class_code[0] - '0';
  std::string classnum;
  for (int i = 1; i < class_code.size(); ++i) {
    if (isnum(class_code[i])) {
      classnum.push_back(class_code[i]);
    }
  }
  try {
    uint8_t num = 0;
    if (classnum != "") {
      num = std::stoi(classnum);
    }
    return ((uint16_t)year << 8) + num;
  } catch (std::invalid_argument &e) {
    std::cerr << e.what() << " class: failed to parse" << '\n';
    std::exit(1);
  }
}

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

void Class::uc_to_str(std::string &out) {
  std::stringstream s;
  std::string classname;
  bool found = false;
  uint16_t hash_of_class = uc_code >> 8;
  for (int i = 0; i <= sizeof(this->types_of_uc) / sizeof(char *); ++i) {
    if (hash_of_class == hash_str(std::string(this->types_of_uc[i]))) {
      classname = this->types_of_uc[i];
      found = true;
      break;
    }
  }
  if (!found) {
    std::cerr << "There is no known uc type with hash " << hash_of_class
              << "!\n";
    std::exit(1);
  }
  s << classname << std::setfill('0') << std::setw(3) << (uc_code & 255);
  out = s.str();
}

void Class::class_to_str(std::string &out) {
  std::stringstream s;
  // TODO: use exceptions to handle errors instead of closing.
  if ((class_code >> 8) == 19) {
    out = "ClassCode";
    return;
  }
  s << (class_code >> 8) << "LEIC" << std::setfill('0') << std::setw(2)
    << (class_code & 255);
  out = s.str();
}

void Class::day_to_str(std::string &out) {
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

void Class::type_to_str(std::string &out) {
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
void Class::display() {
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
