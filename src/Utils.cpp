/**
 * @file Utils.cpp
 * This file defines some functions that are gonna be useful in other classes
 */
#include "Utils.hpp"
#include <cstdint>
#include <iostream>
#include <numeric>

/**
 * This function converts a string to a 8 bit hash.
 * This algorithm (djb2 hash) is better explained here: https://theartincode.stanis.me/008-djb2/
 * Theoretical Complexity: O(n), n being the number of characters in the string.
 * @param s
 * @return the string converted to hash
 */
uint8_t hash_str(std::string s) {
  uint64_t hash = 5381;
  for (char c : s) {
    hash = (hash << 5) + hash + c;
  }
  return (uint8_t)(hash % 256);
}

/**
 * This function converts a uc code (in string) to a 16 bit hash.
 * The non numerical part will be stored in the first 8 bits and the algorith (djb2 hash) to
 * transform a string in a hash code is better explained here: https://theartincode.stanis.me/008-djb2/
 * The numerical part will be stored in the last 8 bits.
 * Theoretical Complexity: O(n), n being the number of characters in the string.
 * @param uc_code
 * @return the hash code for the given uc_code.
 */
uint16_t parse_uc_gen(std::string uc_code) {
  uint64_t hash = 5381;
  std::string num_part;
  for (char c : uc_code) {
    if (!isnum(c)) {
      // DEBUG : printf("%c",c);
      hash = (hash << 5) + hash + c;
    }
    if (isnum(c)) {
      num_part.push_back(c);
    }
  }
  try {
    uint8_t num = 0;
    if (num_part != "") {
      num = std::stoi(num_part);
    }
    // DEBUG : printf(" -> code : %d\n", (uint8_t)hash);
    return (uint16_t)((hash % 256) << 8) + (uint16_t)(num);
  } catch (std::invalid_argument &e) {
    std::cerr << e.what() << " uc: failed to parse" << '\n';
    std::exit(1);
  }
}

/**
 * @brief Parse class_code from a std::string to an uint16_t.
 * @details Useful to save memory and to make comparisons faster.
 * Theoretical Complexity: O(n), n being the number of characters of the std::string.
 * @param class_code
 * @return class_code as uint16_t
 */
uint16_t parse_class_gen(std::string class_code) {
  uint8_t year = class_code[0] - '0';
  std::string classnum;
  for (int i = 1; i < class_code.size(); ++i) {
    if (isnum(class_code[i])) {
      classnum.push_back(class_code[i]);
    }
  }
  try {
    uint8_t num = 0;
    if (!classnum.empty()) {
      num = std::stoi(classnum);
    }
    return ((uint16_t)year << 8) + num;
  } catch (std::invalid_argument &e) {
    std::cerr << e.what() << " class: failed to parse" << '\n';
    std::exit(1);
  }
}

/**
 * This function checks if a given character in a number.
 * Theoretical Complexity: O(1).
 * @param c
 * @return bool
 */
bool isnum(uint32_t c) { return (c >= '0' && c <= '9'); }

/**
 * This function reads a line of the csv file given in the parameter std::string s and appends to the vector passed
 * by reference res the comma separated values of the line
 * Theoretical Complexity: O(n), n being the number of values in the line.
 * @param s
 * @param res
 */
void parse_csv_line(std::string s, std::vector<std::string> &res) {
  std::stringstream line(s);
  std::string buf;
  while (getline(line, buf, ','))
    res.push_back(buf);
}

/**
 * This function calculates the standard deviance for the number of students in each class of a given UC, taking a mean as the input. 
 * Theoretical Complexity: O(n), n being the number of classes in a given UC.
 * @param mean
 * @param c
 */
double uc_variance(double mean, const std::vector<ClassSchedule *> &c) {
  uint64_t size = c.size();
  auto variance_func = [&mean,&size](double acc, const ClassSchedule* val) {
    return acc + (((double)val->get_student_count() - mean) * ((double)val->get_student_count() - mean)) / ((double)size - 1.0);
  };
  return std::accumulate(c.begin(), c.end(), 0.0, variance_func);
}



