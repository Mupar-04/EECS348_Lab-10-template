#include <iostream>

#include "calculator.hpp"

int main(int argc, char *argv[]) {
    std::string filename;
    std::cout << "Enter input file name: ";
    std::getline(std::cin, filename);

    std::vector<std::string> numbers = readNumbersFromFile(filename);

 
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
