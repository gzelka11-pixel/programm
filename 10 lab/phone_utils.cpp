#include "phone_utils.h"
#include <cstring>
#include <map>

namespace PhoneProcessor {
    
    // Проверка является ли символ цифрой
    bool isDigit(char c) {
        return c >= '0' && c <= '9';
    }
    
    // Проверка номера
    bool isValidRussianPhone(const char* phone) {
        if (!phone) return false;
        
        int digitCount = 0;
        for (int i = 0; phone[i] != '\0'; i++) {
            if (isDigit(phone[i])) {
                digitCount++;
            }
        }
        
        // 11 цифр (с кодом страны 7 или 8) или 10 цифр (без кода страны)
        if (digitCount == 11) {
            // Находим первую цифру
            for (int i = 0; phone[i] != '\0'; i++) {
                if (isDigit(phone[i])) {
                    return (phone[i] == '7' || phone[i] == '8');
                }
            }
        } else if (digitCount == 10) {
            return true;  // 10 цифр - номер без кода страны
        }
        
        return false;
    }
    
    // Удаление нецифровых символов
    void removeNonDigits(const char* src, char* dest) {
        if (!src || !dest) return;
        
        while (*src) {
            if (isDigit(*src)) {
                *dest = *src;
                dest++;
            }
            src++;
        }
        *dest = '\0';
    }
    
    // Форматирование номера
    std::string formatPhone(const std::string& phone) {
        char cleaned[32];
        removeNonDigits(phone.c_str(), cleaned);
        std::string digits(cleaned);
        
        if (digits.length() == 11) {
            // Заменяем первую 8 на 7
            if (digits[0] == '8') {
                digits[0] = '7';
            }
            return "+7 (" + digits.substr(1, 3) + ") " + 
                   digits.substr(4, 3) + "-" + 
                   digits.substr(7, 2) + "-" + 
                   digits.substr(9, 2);
        } else if (digits.length() == 10) {
            return "+7 (" + digits.substr(0, 3) + ") " + 
                   digits.substr(3, 3) + "-" + 
                   digits.substr(6, 2) + "-" + 
                   digits.substr(8, 2);
        }
        
        return phone; // Неизмененный, если формат не распознан
    }
    
    // Извлечение кода
    std::string extractCode(const std::string& phone) {
        char cleaned[32];
        removeNonDigits(phone.c_str(), cleaned);
        std::string digits(cleaned);
        
        if (digits.length() == 11) {
            return digits.substr(1, 3);  // Пропускаем первую цифру (7 или 8)
        } else if (digits.length() == 10) {
            return digits.substr(0, 3);  // Первые 3 цифры
        }
        
        return "";
    }
    
    // Определение оператора по коду
    std::string getOperatorByCode(const std::string& code) {
        // Простая база операторов
        if (code == "999" || code == "926" || code == "920" || 
            code == "921" || code == "922" || code == "923") {
            return "Megafon";
        } else if (code == "916" || code == "910" || code == "915" ||
                  code == "980" || code == "981" || code == "982") {
            return "MTS";
        } else if (code == "903" || code == "905" || code == "906" ||
                  code == "909" || code == "950" || code == "951") {
            return "Beeline";
        } else if (code == "900" || code == "901" || code == "902" ||
                  code == "904" || code == "908" || code == "950") {
            return "Tele2";
        } else if (code == "495" || code == "499" || code == "812" ||
                  code == "813" || code == "816") {
            return "City";
        } else {
            return "Other";
        }
    }
    
    // Проверка мобильного номера
    bool isMobileNumber(const std::string& code) {
        std::string op = getOperatorByCode(code);
        return (op == "Megafon" || op == "MTS" || op == "Beeline" || op == "Tele2");
    }
}