#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

// Простые функции для работы с телефонными номерами
bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

void removeNonDigits(const char* src, char* dest) {
    while (*src) {
        if (isDigit(*src)) {
            *dest = *src;
            dest++;
        }
        src++;
    }
    *dest = '\0';
}

bool isValidRussianPhone(const char* phone) {
    char cleaned[32];
    removeNonDigits(phone, cleaned);
    int len = strlen(cleaned);
    
    if (len == 11) {
        return (cleaned[0] == '7' || cleaned[0] == '8');
    } else if (len == 10) {
        return true;
    }
    return false;
}

std::string formatPhone(const std::string& phone) {
    char cleaned[32];
    removeNonDigits(phone.c_str(), cleaned);
    std::string digits(cleaned);
    
    if (digits.length() == 11) {
        if (digits[0] == '8') digits[0] = '7';
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
    return phone;
}

std::string extractCode(const std::string& phone) {
    char cleaned[32];
    removeNonDigits(phone.c_str(), cleaned);
    std::string digits(cleaned);
    
    if (digits.length() == 11) {
        return digits.substr(1, 3);
    } else if (digits.length() == 10) {
        return digits.substr(0, 3);
    }
    return "";
}

std::string getOperatorByCode(const std::string& code) {
    // Простая база операторов
    if (code == "999" || code == "926") return "Megafon";
    if (code == "916") return "MTS";
    if (code == "903") return "Beeline";
    if (code == "495" || code == "812") return "City";
    return "Other";
}

std::string getRegionByCode(const std::string& code) {
    if (code == "999" || code == "926" || code == "916" || code == "903") {
        return "Mobile";
    }
    if (code == "495") return "Moscow";
    if (code == "812") return "Saint Petersburg";
    return "Unknown";
}
// Главная функция
int main() {
    std::cout << "Phone Number Processor\n";
    std::cout << "======================\n\n";
    
    // Тестовые данные
    std::vector<std::string> phones = {
        "+7 (999) 123-45-67",
        "8-926-765-43-21",
        "+79161234567",
        "8 (812) 456 78 90",
        "7-903-555-66-77",
        "9261234567",
        "+7 (495) 123-45-67"
    };
    
    // Открываем файл для записи
    std::ofstream file("output.txt");
    if (!file.is_open()) {
        std::cerr << "Cannot create output.txt\n";
        return 1;
    }
    
    file << "Phone numbers processing:\n\n";
    
    int validCount = 0;
    int invalidCount = 0;
    
    for (size_t i = 0; i < phones.size(); i++) {
        file << (i + 1) << ". Original: " << phones[i] << "\n";
        
        bool valid = isValidRussianPhone(phones[i].c_str());
        
        if (valid) {
            validCount++;
            std::string formatted = formatPhone(phones[i]);
            std::string code = extractCode(phones[i]);
            std::string op = getOperatorByCode(code);
            std::string region = getRegionByCode(code);
            
            file << "   Status: Valid\n";
            file << "   Formatted: " << formatted << "\n";
            file << "   Code: " << code << "\n";
            file << "   Operator: " << op << "\n";
            file << "   Region: " << region << "\n";
        } else {
            invalidCount++;
            file << "   Status: Invalid\n";
            
            // Пробуем предложить исправленный вариант
            char cleaned[32];
            removeNonDigits(phones[i].c_str(), cleaned);
            std::string digits(cleaned);
            
            if (digits.length() == 10) {
                file << "   Suggested: +7 (" << digits.substr(0, 3) << ") " 
                     << digits.substr(3, 3) << "-" << digits.substr(6, 2) << "-" 
                     << digits.substr(8, 2) << "\n";
            }
        }
        file << "\n";
    }
    
    // Статистика
    file << "Statistics:\n";
    file << "Valid: " << validCount << "\n";
    file << "Invalid: " << invalidCount << "\n";
    
    file.close();
    
    std::cout << "Processing complete!\n";
    std::cout << validCount << " valid numbers\n";
    std::cout << invalidCount << " invalid numbers\n";
    std::cout << "Check output.txt for details\n";
    
    return 0;
}