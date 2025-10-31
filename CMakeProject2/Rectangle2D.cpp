#include "Rectangle2D.h"
#include <algorithm>

namespace Geometry {
    Rectangle2D* createRectangle(float x, float y, float width, float height) {
        if (width < 0 || height < 0) return nullptr;

        Rectangle2D* rect = new Rectangle2D;
        rect->x = x;
        rect->y = y;
        rect->width = width;
        rect->height = height;
        return rect;
    }

    void deleteRectangle(Rectangle2D* rect) {
        delete rect;
    }

    bool intersects(const Rectangle2D* rect1, const Rectangle2D* rect2) {
        return (rect1->x < rect2->x + rect2->width) &&
            (rect1->x + rect1->width > rect2->x) &&
            (rect1->y < rect2->y + rect2->height) &&
            (rect1->y + rect1->height > rect2->y);
    }

    float intersectionArea(const Rectangle2D* rect1, const Rectangle2D* rect2) {
        if (!intersects(rect1, rect2)) return 0.0f;

        float left = std::max(rect1->x, rect2->x);
        float right = std::min(rect1->x + rect1->width, rect2->x + rect2->width);
        float top = std::min(rect1->y + rect1->height, rect2->y + rect2->height);
        float bottom = std::max(rect1->y, rect2->y);

        return (right - left) * (top - bottom);
    }

    void moveRectangle(Rectangle2D* rect, float dx, float dy) {
        rect->x += dx;
        rect->y += dy;
    }
}