#include <iostream>
#include <vector>
#include <iomanip>
#include "Rectangle2D.h"

void demonstrateRectangleOperations() {
    using namespace Geometry;

    std::vector<Rectangle2D*> rectangles;

    try {
        // Создаем прямоугольники
        std::cout << "=== Creating Rectangles ===\n";
        rectangles.push_back(createRectangle(1.0f, 1.0f, 4.0f, 3.0f));
        std::cout << "Rectangle 0: x=" << rectangles[0]->x << ", y=" << rectangles[0]->y 
                  << ", width=" << rectangles[0]->width << ", height=" << rectangles[0]->height << "\n";

        rectangles.push_back(createRectangle(3.0f, 2.0f, 5.0f, 4.0f));
        std::cout << "Rectangle 1: x=" << rectangles[1]->x << ", y=" << rectangles[1]->y 
                  << ", width=" << rectangles[1]->width << ", height=" << rectangles[1]->height << "\n";

        rectangles.push_back(createRectangle(10.0f, 10.0f, 2.0f, 2.0f));
        std::cout << "Rectangle 2: x=" << rectangles[2]->x << ", y=" << rectangles[2]->y 
                  << ", width=" << rectangles[2]->width << ", height=" << rectangles[2]->height << "\n";

        // Проверка пересечений
        std::cout << "\n=== Checking Intersections ===\n";
        if (checkIntersection(rectangles[0], rectangles[1])) {
            std::cout << "Rectangle 0 and Rectangle 1 intersect\n";
        } else {
            std::cout << "Rectangle 0 and Rectangle 1 do NOT intersect\n";
        }

        if (checkIntersection(rectangles[0], rectangles[2])) {
            std::cout << "Rectangle 0 and Rectangle 2 intersect\n";
        } else {
            std::cout << "Rectangle 0 and Rectangle 2 do NOT intersect\n";
        }

        // Вычисление площади пересечения
        std::cout << "\n=== Calculating Intersection Area ===\n";
        std::cout << std::fixed << std::setprecision(2);
        float area = intersectionArea(rectangles[0], rectangles[1]);
        std::cout << "Intersection area of Rectangle 0 and Rectangle 1: " << area << "\n";

        // Сдвиг прямоугольника
        std::cout << "\n=== Moving Rectangle ===\n";
        std::cout << "Before moving - Rectangle 0: x=" << rectangles[0]->x << ", y=" << rectangles[0]->y << "\n";
        moveRectangle(rectangles[0], 2.0f, 1.0f);
        std::cout << "After moving (+2, +1) - Rectangle 0: x=" << rectangles[0]->x << ", y=" << rectangles[0]->y << "\n";

        // Проверка пересечения после сдвига
        std::cout << "\n=== Checking Intersection After Move ===\n";
        if (checkIntersection(rectangles[0], rectangles[1])) {
            std::cout << "After moving, Rectangle 0 and Rectangle 1 intersect\n";
            area = intersectionArea(rectangles[0], rectangles[1]);
            std::cout << "New intersection area: " << area << "\n";
        } else {
            std::cout << "After moving, Rectangle 0 and Rectangle 1 do NOT intersect\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    // Очистка памяти
    std::cout << "\n=== Cleaning Up Memory ===\n";
    for (size_t i = 0; i < rectangles.size(); ++i) {
        std::cout << "Deleting Rectangle " << i << "\n";
        deleteRectangle(rectangles[i]);
    }
    rectangles.clear();
}

int main() {
    std::cout << "=== LAB 6: Rectangle2D Operations ===\n\n";
    
    demonstrateRectangleOperations();
    
    std::cout << "\n=== Program Completed Successfully ===\n";
    return 0;
}