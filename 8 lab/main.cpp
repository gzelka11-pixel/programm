#include "functions.h"
#include <iostream>

int main() {
    try {
        int studentCount;
        int** data = StudentManager::readData("input.txt", studentCount);
        double* averages = StudentManager::calculateAverages(data, studentCount);
        int maxIndex = StudentManager::findMaxAverage(averages, studentCount);
        int countAbove = StudentManager::countAboveThreshold(averages, studentCount, 4.0);
        StudentManager::writeReport("output.txt", averages, studentCount, maxIndex, countAbove);
        
        // Освобождение памяти
        for (int i = 0; i < studentCount; ++i) {
            delete[] data[i];
        }
        delete[] data;
        delete[] averages;
        
    } catch (const char* error) {
        std::cerr << "Ошибка: " << error << std::endl;
        return 1;
    }
    return 0;
}