/**
 * @file ClassSchedule.cpp
 */
#include "ClassSchedule.hpp"
#include <cstdint>
#include <cstdio>
#include <vector>


ClassSchedule::ClassSchedule(uint16_t uc_code, uint16_t class_code) {
  this->uc_code = uc_code;
  this->class_code = class_code;
  this->classes = std::vector<Lesson*>();
  this->n_students = 0;
}

void ClassSchedule::add_student() {n_students += 1;}
void ClassSchedule::remove_student() {n_students -= 1;}

bool ClassSchedule::add_entry(Lesson* c) {
  if (c->get_uc_code() != this->uc_code || c->get_class_code() != this->uc_code) {
    //fprintf(stdout, "Error: Operation Invalid: Can't add a lesson to a schedule of a different class!" , ...);
    return false;
  }
  this->classes.push_back(c);
  return true;
}

bool ClassSchedule::remove_entry(Lesson* c) {
  // Probably unecessary
  for (std::vector<Lesson*>::iterator itr = this->classes.begin();  itr != this->classes.end(); ++itr) {
    if (*itr == c) {
      this->classes.erase(itr);
      return true;
    }
  }
  return false;
}

uint64_t ClassSchedule::get_student_count() const {
  return this->n_students;
}

uint32_t ClassSchedule::get_id() const {
  return ((uint32_t)this->uc_code << 16) + this->class_code;
}

std::vector<Lesson*>* ClassSchedule::get_class_schedule() {
  return &this->classes;
}
