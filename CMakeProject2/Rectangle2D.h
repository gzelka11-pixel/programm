#ifndef RECTANGLE2D_H
#define RECTANGLE2D_H

namespace Geometry {
    struct Rectangle2D {
        float x;
        float y;
        float width;
        float height;
    };

    // �������� ������ ��������������
    Rectangle2D* createRectangle(float x, float y, float width, float height);

    // �������� ��������������
    void deleteRectangle(Rectangle2D* rect);

    // �������� ����������� ���� ���������������
    bool intersects(const Rectangle2D* rect1, const Rectangle2D* rect2);

    // ���������� ������� �����������
    float intersectionArea(const Rectangle2D* rect1, const Rectangle2D* rect2);

    // ����� ��������������
    void moveRectangle(Rectangle2D* rect, float dx, float dy);
}

#endif
