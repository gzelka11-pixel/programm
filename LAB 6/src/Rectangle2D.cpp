#include "Rectangle2D.h"
#include <algorithm>
#include <stdexcept>

namespace Geometry {

Rectangle2D* createRectangle(float x, float y, float width, float height) {
    // Прямая проверка вместо вызова isValidRectangle
    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Width and height must be positive values");
    }
    
    Rectangle2D* rect = new Rectangle2D;
    rect->x = x;
    rect->y = y;
    rect->width = width;
    rect->height = height;
    
    return rect;
}

void deleteRectangle(Rectangle2D* rect) {
    if (rect) {
        delete rect;
    }
}

bool checkIntersection(const Rectangle2D* rect1, const Rectangle2D* rect2) {
    if (!rect1 || !rect2) {
        throw std::invalid_argument("Null pointer passed to checkIntersection");
    }
    
    bool overlapX = (rect1->x < rect2->x + rect2->width) && 
                    (rect1->x + rect1->width > rect2->x);
    
    bool overlapY = (rect1->y < rect2->y + rect2->height) && 
                    (rect1->y + rect1->height > rect2->y);
    
    return overlapX && overlapY;
}

float intersectionArea(const Rectangle2D* rect1, const Rectangle2D* rect2) {
    if (!rect1 || !rect2) {
        throw std::invalid_argument("Null pointer passed to intersectionArea");
    }
    
    if (!checkIntersection(rect1, rect2)) {
        return 0.0f;
    }
    
    float left = std::max(rect1->x, rect2->x);
    float right = std::min(rect1->x + rect1->width, rect2->x + rect2->width);
    float bottom = std::max(rect1->y, rect2->y);
    float top = std::min(rect1->y + rect1->height, rect2->y + rect2->height);
    
    float width = right - left;
    float height = top - bottom;
    
    return width * height;
}

void moveRectangle(Rectangle2D* rect, float dx, float dy) {
    if (!rect) {
        throw std::invalid_argument("Null pointer passed to moveRectangle");
    }
    
    rect->x += dx;
    rect->y += dy;
}

} // namespace Geometry