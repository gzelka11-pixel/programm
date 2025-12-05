#include "text_processor.h"
#include <iostream>

int main() {
    const char* inputFilename = "input.txt";
    const char* outputFilename = "output.txt";
    
    int fileSize = 0;
    
    // Чтение файла в динамический массив
    char* text = TextProcessor::readFileToCharArray(inputFilename, fileSize);
    
    if (!text) {
        std::cerr << "Программа завершена из-за ошибки чтения файла." << std::endl;
        return 1;
    }
    
    std::cout << "Файл успешно прочитан. Размер: " << fileSize << " байт" << std::endl;
    
    // Подсчёт статистики
    int vowels, consonants, digits, punctuation;
    
    TextProcessor::countLetters(text, fileSize, vowels, consonants);
    TextProcessor::countDigitsAndPunctuation(text, fileSize, digits, punctuation);
    
    // Замена пробелов на подчёркивания
    TextProcessor::replaceSpacesWithUnderscores(text, fileSize);
    
    // Запись результатов в файл
    TextProcessor::writeResultsToFile(outputFilename, text, fileSize, 
                                     vowels, consonants, digits, punctuation);
    
    // Вывод статистики в консоль
    std::cout << "\nСтатистика обработки:\n";
    std::cout << "Гласные буквы: " << vowels << "\n";
    std::cout << "Согласные буквы: " << consonants << "\n";
    std::cout << "Цифры: " << digits << "\n";
    std::cout << "Знаки препинания: " << punctuation << std::endl;
    std::cout << "Результат записан в файл: " << outputFilename << std::endl;
    
    // Освобождение памяти
    delete[] text;
    
    return 0;
}