#include <iostream>
#include "Rectangle2D.h"

int main() {
    using namespace Geometry;

    // �������� ���������������
    Rectangle2D* rect1 = createRectangle(0.0f, 0.0f, 5.0f, 5.0f);
    Rectangle2D* rect2 = createRectangle(3.0f, 3.0f, 5.0f, 5.0f);

    if (!rect1 || !rect2) {
        std::cerr << "������ �������� ���������������!" << std::endl;
        return -1;
    }

    // �������� �����������
    std::cout << "������������: " << (intersects(rect1, rect2) ? "��" : "���") << std::endl;

    // ������� �����������
    std::cout << "������� �����������: " << intersectionArea(rect1, rect2) << std::endl;

    // ����� ������� ��������������
    moveRectangle(rect1, 2.0f, 2.0f);
    std::cout << "����� ������: " << rect1->x << ", " << rect1->y << std::endl;

    // ������������ ������
    deleteRectangle(rect1);
    deleteRectangle(rect2);

    return 0;
}