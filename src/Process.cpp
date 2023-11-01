#include "Process.hpp"
#include <string>
#include <vector>


Process::Process(TypeOfRequest t) {
  type = t;
  operands = std::vector<std::string>();
}

void Process::add_operand(std::string op) {
  operands.push_back(op);
}

TypeOfRequest Process::get_type() {
  return type;
}

std::vector<std::string>& Process::get_ops() {
  return operands;
}
