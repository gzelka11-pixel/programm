#ifndef PHONE_UTILS_H
#define PHONE_UTILS_H

#include <string>

namespace PhoneProcessor {
    bool isValidRussianPhone(const char* phone);
    void removeNonDigits(const char* src, char* dest);
    std::string formatPhone(const std::string& phone);
    std::string extractCode(const std::string& phone);
    std::string getOperatorByCode(const std::string& code);
    bool isMobileNumber(const std::string& code);
}

#endif