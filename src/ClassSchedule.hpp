#include <cstdint>
#include <vector>
#include "classes.hpp"


class ClassSchedule {
private:
  uint64_t n_students = 0;
  uint16_t uc_code;
  uint16_t class_code;
  std::vector<Class*> classes;
  
public:
  ClassSchedule(uint16_t uc_code, uint16_t class_code);
  bool add_entry(Class* entry);
  bool remove_entry(Class* entry);
  void add_student();
  void remove_student();
  uint64_t get_student_count() const;
  uint32_t get_id() const;
  std::vector<Class*>* get_class_schedule();
};
