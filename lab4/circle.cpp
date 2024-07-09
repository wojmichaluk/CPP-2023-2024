#include "circle.h"

Shapes::Circle::Circle(int xCenter, int yCenter, int radius) : Shapes::Shape(xCenter, yCenter), radius_{radius} {}

int Shapes::Circle::radius() const noexcept { 
    return radius_; 
}

bool Shapes::Circle::isIn(int x, int y) const {
    return (this->x() - x) * (this->x() - x) + (this->y() - y) * (this->y() - y) <= this->radius() * this->radius();
}
