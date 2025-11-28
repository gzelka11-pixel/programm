#include "functions.h"
#include <iostream>
#include <iomanip>

namespace StudentManager {
    int** readData(const char* filename, int& studentCount) {
        std::ifstream in(filename);
        if (!in.is_open()) {
            throw "Не удалось открыть входной файл";
        }
        
        in >> studentCount;
        if (studentCount <= 0 || studentCount > 50) {
            throw "Некорректное количество студентов";
        }
        
        int** data = new int*[studentCount];
        for (int i = 0; i < studentCount; ++i) {
            data[i] = new int[5];
            for (int j = 0; j < 5; ++j) {
                in >> data[i][j];
                if (data[i][j] < 1 || data[i][j] > 5) {
                    throw "Некорректная оценка";
                }
            }
        }
        in.close();
        return data;
    }
    
    double* calculateAverages(int** data, int studentCount) {
        double* averages = new double[studentCount];
        for (int i = 0; i < studentCount; ++i) {
            int sum = 0;
            for (int j = 0; j < 5; ++j) {
                sum += data[i][j];
            }
            averages[i] = sum / 5.0;
        }
        return averages;
    }
    
    int findMaxAverage(double* averages, int studentCount) {
        int maxIndex = 0;
        for (int i = 1; i < studentCount; ++i) {
            if (averages[i] > averages[maxIndex]) {
                maxIndex = i;
            }
        }
        return maxIndex;
    }
    
    int countAboveThreshold(double* averages, int studentCount, double threshold) {
        int count = 0;
        for (int i = 0; i < studentCount; ++i) {
            if (averages[i] > threshold) {
                count++;
            }
        }
        return count;
    }
    
    void writeReport(const char* filename, double* averages, int studentCount, int maxIndex, int countAbove) {
        std::ofstream out(filename);
        if (!out.is_open()) {
            throw "Не удалось открыть выходной файл";
        }
        
        out << std::fixed << std::setprecision(2);
        out << "Средние баллы студентов:\n";
        for (int i = 0; i < studentCount; ++i) {
            out << "Студент " << (i + 1) << ": " << averages[i] << '\n';
        }
        
        out << "Студент с максимальным средним баллом: Студент " 
            << (maxIndex + 1) << " (" << averages[maxIndex] << ")\n";
        out << "Количество студентов с средним баллом выше 4.0: " << countAbove << '\n';
        out.close();
    }
}