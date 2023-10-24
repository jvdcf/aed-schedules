#include <cctype>
#include <iostream>
#include <string>
#include <cstdint>


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

enum class Type{
    T,
    TP,
    PL,

};

class Class{
private:
    uint16_t uc_code;
    uint16_t class_code;
    constexpr const static char* types_of_uc[] = {"L.EIC", "UP", "IAPD", "CSR", "IADE", "IR", "MPSAC", "DDS", "SEESTE"};
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
    void uc_to_str(std::string & out);

    void class_to_str(std::string & out);

    void day_to_str(std::string & out);

    void type_to_str(std::string & out);

    // Other Methods:
    void display();
};

#endif // CLASS_HPP