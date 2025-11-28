#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <fstream>

namespace StudentManager {
    // Чтение данных из файла
    int** readData(const char* filename, int& studentCount);
    
    // Вычисление среднего балла для каждого студента
    double* calculateAverages(int** data, int studentCount);
    
    // Нахождение индекса студента с максимальным средним баллом
    int findMaxAverage(double* averages, int studentCount);
    
    // Подсчет студентов со средним баллом выше порога
    int countAboveThreshold(double* averages, int studentCount, double threshold);
    
    // Запись отчета в файл
    void writeReport(const char* filename, double* averages, int studentCount, int maxIndex, int countAbove);
}

#endif