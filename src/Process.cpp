#include "Process.hpp"
#include <string>
#include <vector>

/**
 * @brief Constructs a request of a certain type.
 * This request is not yet completed, as the operands are still to be added.
 * Theoretical Complexity: O(1).
 * @param t
 */
Process::Process(TypeOfRequest t) {
  type = t;
  operands = std::vector<std::string>();
}

/**
 * @brief Adds a string to the operands vector
 * Theoretical Complexity: O(1).
 * @param op
 */
void Process::add_operand(std::string op) {
  operands.push_back(op);
}

/**
 * @brief Accesses the type of request.
 * Theoretical Complexity: O(1).
 * @return
 */
TypeOfRequest Process::get_type() {
  return type;
}

/**
 * @brief Accesses the vector of operands.
 * Theoretical Complexity: O(1).
 * @return
 */
std::vector<std::string>& Process::get_ops() {
  return operands;
}
