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
};

/**
 * @brief Stores the user requests.
 */
class Process {
private:
  TypeOfRequest type;
  std::vector<std::string> operands;

public:
  // Costructor
  Process(TypeOfRequest t);

  // Methods
  void add_operand(std::string s);

  // Getters
  TypeOfRequest get_type();
  std::vector<std::string>& get_ops();
};
