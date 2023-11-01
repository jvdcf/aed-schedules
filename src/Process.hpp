#include <string>
#include <vector>


enum class TypeOfRequest {
  Add,
  Remove,
  Switch,
  Print_Student,
  Print_UC,
  Print_Class,
  Batch,
};


class Process {
  private:
  TypeOfRequest type;
  std::vector<std::string> operands;

  public:
  Process(TypeOfRequest t);
  void add_operand(std::string s);
  TypeOfRequest get_type();
  std::vector<std::string>& get_ops();
};
