#ifndef RECTANGLE2D_H
#define RECTANGLE2D_H

namespace Geometry {
    struct Rectangle2D {
        float x;
        float y;
        float width;
        float height;
    };

    // Создание нового прямоугольника
    Rectangle2D* createRectangle(float x, float y, float width, float height);

    // Удаление прямоугольника
    void deleteRectangle(Rectangle2D* rect);

    // Проверка пересечения двух прямоугольников
    bool intersects(const Rectangle2D* rect1, const Rectangle2D* rect2);

    // Вычисление площади пересечения
    float intersectionArea(const Rectangle2D* rect1, const Rectangle2D* rect2);

    // Сдвиг прямоугольника
    void moveRectangle(Rectangle2D* rect, float dx, float dy);
}

#endif
