#include "rectangle.h"

Shapes::Rectangle::Rectangle(int xFrom, int yFrom, int xTo, int yTo) : Shapes::Shape{xFrom, yFrom}, pointTo{xTo, yTo} {}

int Shapes::Rectangle::xTo() const noexcept { 
    return pointTo.x_; 
}

int Shapes::Rectangle::yTo() const noexcept { 
    return pointTo.y_; 
}

bool Shapes::Rectangle::isIn(int x, int y) const {
    return x >= this->x() && x <= this->xTo() && y >= this->y() && y <= this->yTo();
}
