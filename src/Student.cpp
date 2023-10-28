#include "Student.hpp"
#include "Utils.hpp"
#include <cstdint>
#include <string>
#include <vector>

Student::Student(uint32_t code, std::string name) {
  this->code = code;
  this->name = name;
  this->classes = std::vector<ClassSchedule *>();
}

std::vector<ClassSchedule *> *Student::get_schedule() { return &this->classes; }

OperationResult Student::add_to_class(ClassSchedule *c) {
  std::vector<Class *> *new_lessons = c->get_class_schedule();
  // return false;
  for (ClassSchedule *a : this->classes) {
    std::vector<Class *> *lessons = a->get_class_schedule();
    for (Class *lesson : *lessons) {
      for (Class *new_lesson : *new_lessons) {
        if (lesson->get_start_hour() < new_lesson->get_start_hour() &&
            new_lesson->get_start_hour() <
                (lesson->get_start_hour() + lesson->get_duration())) {
          if (lesson->get_type() == Type::T ||
              new_lesson->get_type() == Type::T) {
            return OperationResult::Conlicts; // We return conflicts so that the
                                              // handler function can ask the
                                              // user whether or not they want
                                              // to proceed.
          }
          return OperationResult::Error;
        }
        if (lesson->get_start_hour() <
                (new_lesson->get_start_hour() + new_lesson->get_duration()) &&
            (new_lesson->get_start_hour() + new_lesson->get_duration()) <
                (lesson->get_start_hour() + lesson->get_duration())) {
          if (lesson->get_type() == Type::T ||
              new_lesson->get_type() == Type::T) {
            return OperationResult::Conlicts;
          }
          return OperationResult::Error;
        }
      }
    }
  }
  c->add_student();
  this->classes.push_back(c);
  return OperationResult::Success;
}

void Student::remove_from_class(ClassSchedule *c) {
  c->remove_student();
  for (std::vector<ClassSchedule*>::iterator itr = this->classes.begin(); itr != this->classes.end(); ++itr) {
    if (c == *itr) {
      this->classes.erase(itr);
      return;
    }
  }
  this->classes.push_back(c);
}

OperationResult Student::switch_class_with(Student other, ClassSchedule *thisone,
                                ClassSchedule *theoother) {
  return OperationResult::Success; //TODO
}
