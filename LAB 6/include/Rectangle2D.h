#ifndef RECTANGLE2D_H
#define RECTANGLE2D_H

namespace Geometry {

struct Rectangle2D {
    float x;
    float y;
    float width;
    float height;
};

// Создать прямоугольник
Rectangle2D* createRectangle(float x, float y, float width, float height);

// Удалить прямоугольник
void deleteRectangle(Rectangle2D* rect);

// Проверить пересечение
bool checkIntersection(const Rectangle2D* rect1, const Rectangle2D* rect2);

// Вычислить площадь пересечения
float intersectionArea(const Rectangle2D* rect1, const Rectangle2D* rect2);

// Сдвинуть прямоугольник
void moveRectangle(Rectangle2D* rect, float dx, float dy);

} // namespace Geometry

#endif // RECTANGLE2D_H