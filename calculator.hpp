#ifndef __CALCULATOR_HPP
#define __CALCULATOR_HPP

#include <string>
#include <vector>

// this function should expect that `expression` has already been
// validated and thus throw no exceptions
double parse_number(const std::string &expression);
bool isValidDouble(const std::string &s);
std::string addDoubles(const std::string &a, const std::string &b);
std::vector<std::string> readNumbersFromFile(const std::string &filename);

#endif // __CALCULATOR_HPP
