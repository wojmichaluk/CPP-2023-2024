#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Shapes::Circle : public Shapes::Shape {
public:
    Circle(int xCenter, int yCenter, int radius);
    int radius() const noexcept;

    bool isIn(int x, int y) const override;

private:
    int radius_;
};

#endif // CIRCLE_H
