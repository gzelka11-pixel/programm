#ifndef TEXT_PROCESSOR_H
#define TEXT_PROCESSOR_H

#include <fstream>

namespace TextProcessor {
    // Функция для чтения файла в динамический массив
    char* readFileToCharArray(const char* filename, int& fileSize);
    
    // Функция для подсчёта гласных и согласных
    void countLetters(const char* text, int size, int& vowels, int& consonants);
    
    // Функция для подсчёта цифр и знаков препинания
    void countDigitsAndPunctuation(const char* text, int size, int& digits, int& punctuation);
    
    // Функция для замены пробелов на подчёркивания
    void replaceSpacesWithUnderscores(char* text, int size);
    
    // Функция для записи результата в файл
    void writeResultsToFile(const char* filename, const char* text, int size, 
                           int vowels, int consonants, int digits, int punctuation);
}

#endif