/**
 * @file Process.hpp
 */
#ifndef PROCESS_H
#define PROCESS_H
#include <string>
#include <vector>


/**
 * @brief Used to efficiently store the type of request.
 */
enum class TypeOfRequest {
  Add,
  Remove,
  Switch,
  Print_Student,
  Print_Student_Count,
  Print_UC,
  Print_Class,
  Print_Student_List,
  Batch,
  Save,
  Undo,
  PopHistory,
  Enroll,
};

/**
 * @brief Stores the user requests.
 */
class Process {
private:
  /// The type of request it was made.
  TypeOfRequest type;
  /// The arguments for the function.
  std::vector<std::string> operands;

public:
  Process(TypeOfRequest t);
  void add_operand(std::string s);
  TypeOfRequest get_type();
  std::vector<std::string>& get_ops();
};


#endif // PROCESS_H
