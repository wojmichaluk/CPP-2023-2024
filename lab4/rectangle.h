#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Shapes::Rectangle : public Shapes::Shape {
public:
    Rectangle(int xFrom, int yFrom, int xTo, int yTo);
    int xTo() const noexcept;
    int yTo() const noexcept;

    bool isIn(int x, int y) const override;

private:
    Shapes::Point pointTo;
};

#endif // RECTANGLE_H
