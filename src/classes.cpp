
#include "classes.hpp"

// Constructor:
Class::Class(std::string line) {

}


// Getters:
unsigned short Class::getUcCode() const {
    return uc_code;
}

unsigned short Class::getClassCode() const {
    return class_code;
}

WeekDay Class::getDay() const {
    return day;
}

double Class::getStartHour() const {
    return start_hour;
}

double Class::getDuration() const {
    return duration;
}

Type Class::getType() const {
    return type;
}
