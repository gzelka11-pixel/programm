#include <iostream>
#include "Rectangle2D.h"

int main() {
    using namespace Geometry;

    // Создание прямоугольников
    Rectangle2D* rect1 = createRectangle(0.0f, 0.0f, 5.0f, 5.0f);
    Rectangle2D* rect2 = createRectangle(3.0f, 3.0f, 5.0f, 5.0f);

    if (!rect1 || !rect2) {
        std::cerr << "Ошибка создания прямоугольников!" << std::endl;
        return -1;
    }

    // Проверка пересечения
    std::cout << "Пересекаются: " << (intersects(rect1, rect2) ? "Да" : "Нет") << std::endl;

    // Площадь пересечения
    std::cout << "Площадь пересечения: " << intersectionArea(rect1, rect2) << std::endl;

    // Сдвиг первого прямоугольника
    moveRectangle(rect1, 2.0f, 2.0f);
    std::cout << "После сдвига: " << rect1->x << ", " << rect1->y << std::endl;

    // Освобождение памяти
    deleteRectangle(rect1);
    deleteRectangle(rect2);

    return 0;
}