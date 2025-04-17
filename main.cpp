#include <iostream>

#include "calculator.hpp"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <filename>\n";
    return 1;
  }

  std::vector<std::string> numbers = readNumbersFromFile(argv[1]);
  std::string constant = "-123.456";

  for (const std::string &num : numbers) {
    if (isValidDouble(num)) {
        std::string result = addDoubles(num, constant);
        std::cout << "Valid: " << num << " + " << constant << " = " << result << "\n";
    } 
    
    else {
            std::cout << "Invalid number: " << num << "\n";
        }
    }

    return 0;
}
