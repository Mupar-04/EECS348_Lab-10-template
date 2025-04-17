#include "calculator.hpp"
#include <fstream>
#include <iostream>
#include <cctype>
#include <algorithm>
#include <sstream>

bool isValidDouble(const std::string &s) {
    int len = s.length();
    if (len == 0) return false;

    int i = 0;

    // optional sign
    if (s[i] == '+' || s[i] == '-') i++;

    bool hasDigits = false;
    while (i < len && isdigit(s[i])) {
        i++;
        hasDigits = true;
    }

    bool hasDecimal = false;
    if (i < len && s[i] == '.') {
        i++;
        hasDecimal = true;
    }

    bool hasDigitsAfterDecimal = false;
    while (i < len && isdigit(s[i])) {
        i++;
        hasDigitsAfterDecimal = true;
    }

    if (i != len) return false;
    if (!hasDigits && !hasDigitsAfterDecimal) return false;
    if (hasDecimal && !hasDigitsAfterDecimal) return false;

    return true;
}

std::string removeLeadingZeros(const std::string &num) {
    std::string res = num;
    bool isNeg = false;

    if (!res.empty() && res[0] == '-') {
        isNeg = true;
        res = res.substr(1);
    }

    size_t dot = res.find('.');
    size_t i = 0;
    while (i < dot && res[i] == '0') ++i;

    res = res.substr(i);
    if (res.empty() || res[0] == '.') res = "0" + res;

    return isNeg ? "-" + res : res;
}

std::string trimTrailingZeros(const std::string &num) {
    std::string res = num;
    if (res.find('.') == std::string::npos) return res;

    while (res.back() == '0') res.pop_back();
    if (res.back() == '.') res.pop_back();

    return res.empty() ? "0" : res;
}

void normalizeStrings(const std::string &inA, const std::string &inB, std::string &aOut, std::string &bOut) {
    std::string a = inA;
    std::string b = inB;

    if (a.find('.') == std::string::npos) a += ".0";
    if (b.find('.') == std::string::npos) b += ".0";

    size_t aDot = a.find('.');
    size_t bDot = b.find('.');

    int intDiff = (int)aDot - (int)bDot;
    if (intDiff > 0)
        b = std::string(intDiff, '0') + b;
    else if (intDiff < 0)
        a = std::string(-intDiff, '0') + a;

    int aFrac = a.length() - a.find('.') - 1;
    int bFrac = b.length() - b.find('.') - 1;
    int fracDiff = aFrac - bFrac;
    if (fracDiff > 0)
        b += std::string(fracDiff, '0');
    else if (fracDiff < 0)
        a += std::string(-fracDiff, '0');

    aOut = a;
    bOut = b;
}


std::string addUnsignedStrings(std::string a, std::string b) {
    std::string na, nb;
    normalizeStrings(a, b, na, nb);

    std::string result = "";
    int carry = 0;

    for (int i = na.length() - 1; i >= 0; --i) {
      if (na[i] == '.') {
        result = '.' + result;
        continue;
    }

    int digitSum = (na[i] - '0') + (nb[i] - '0') + carry;
    carry = digitSum / 10;
    result = char((digitSum % 10) + '0') + result;
}


    if (carry) result = '1' + result;

    return result;
}



bool isSmaller(const std::string &a, const std::string &b) {
    std::string na, nb;
    normalizeStrings(a, b, na, nb);
    return na < nb;
}

std::string subtractUnsignedStrings(std::string a, std::string b) {
    std::string na, nb;
    normalizeStrings(a, b, na, nb);

    std::string result = "";
    int borrow = 0;

    for (int i = na.length() - 1; i >= 0; --i) {
        if (na[i] == '.') {
            result = '.' + result;
            continue;
        }

        int digitA = na[i] - '0' - borrow;
        int digitB = nb[i] - '0';

        if (digitA < digitB) {
            digitA += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result = char((digitA - digitB) + '0') + result;
    }

    // Remove leading zeros
    size_t dotPos = result.find('.');
    size_t start = result.find_first_not_of('0');
    if (start == std::string::npos) start = dotPos - 1;
    result = result.substr(start);

    // Remove trailing zeros after decimal
    while (result.back() == '0') result.pop_back();
    if (result.back() == '.') result.pop_back();

    return result;
}



std::string addDoubles(const std::string &aStr, const std::string &bStr) {
    std::string a = aStr, b = bStr;

    // Extract signs
    bool aNeg = false, bNeg = false;
    if (a[0] == '-') { aNeg = true; a = a.substr(1); }
    if (b[0] == '-') { bNeg = true; b = b.substr(1); }

    std::string result;

    if (aNeg == bNeg) {
        // Same signs → add and keep sign
        result = addUnsignedStrings(a, b);
        if (aNeg) result = '-' + result;
    } else {
        // Different signs → subtract
        if (isSmaller(a, b)) {
            result = subtractUnsignedStrings(b, a);
            if (bNeg) result = '-' + result;
        } else {
            result = subtractUnsignedStrings(a, b);
            if (aNeg) result = '-' + result;
        }
    }

    result = removeLeadingZeros(result);
    result = trimTrailingZeros(result);
    if (result.empty() || result == "-") result = "0";

    return result;
}

std::vector<std::string> readNumbersFromFile(const std::string &filename) {
    std::vector<std::string> numbers;
    std::ifstream file(filename);
    std::string line;
    if (!file.is_open()) {
        std::cerr << "Could not open file.\n";
        return numbers;
    }

    while (getline(file, line)) {
        numbers.push_back(line);
    }

    file.close();
    return numbers;
}


// double parse_number(const std::string &expression) {
//     // ONLY for internal testing or debugging
//     try {
//         return std::stod(expression);
//     } catch (...) {
//         return 0.0;
//     }
// }
