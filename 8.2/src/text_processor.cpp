#include "text_processor.h"
#include <iostream>
#include <cctype>
#include <cstring>

namespace TextProcessor {

char* readFileToCharArray(const char* filename, int& fileSize) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    
    if (!file.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл " << filename << std::endl;
        return nullptr;
    }
    
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    
    char* buffer = new char[fileSize + 1];
    file.read(buffer, fileSize);
    buffer[fileSize] = '\0';
    
    file.close();
    return buffer;
}

void countLetters(const char* text, int size, int& vowels, int& consonants) {
    vowels = 0;
    consonants = 0;
    
    const std::string vowelChars = "aeiouAEIOU";
    const std::string consonantChars = "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ";
    
    for (int i = 0; i < size; ++i) {
        char c = text[i];
        if (vowelChars.find(c) != std::string::npos) {
            vowels++;
        } else if (consonantChars.find(c) != std::string::npos) {
            consonants++;
        }
    }
}

void countDigitsAndPunctuation(const char* text, int size, int& digits, int& punctuation) {
    digits = 0;
    punctuation = 0;
    
    const std::string punctuationChars = ".,!?;:-()\"'";
    
    for (int i = 0; i < size; ++i) {
        char c = text[i];
        if (std::isdigit(c)) {
            digits++;
        } else if (punctuationChars.find(c) != std::string::npos) {
            punctuation++;
        }
    }
}

void replaceSpacesWithUnderscores(char* text, int size) {
    for (int i = 0; i < size; ++i) {
        if (text[i] == ' ') {
            text[i] = '_';
        }
    }
}

void writeResultsToFile(const char* filename, const char* text, int size, 
                       int vowels, int consonants, int digits, int punctuation) {
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Ошибка: Не удалось создать файл " << filename << std::endl;
        return;
    }
    
    file << "Статистика:\n";
    file << "Гласные буквы: " << vowels << "\n";
    file << "Согласные буквы: " << consonants << "\n";
    file << "Цифры: " << digits << "\n";
    file << "Знаки препинания: " << punctuation << "\n\n";
    file << "Модифицированный текст:\n";
    file.write(text, size);
    
    file.close();
}

} // namespace TextProcessor