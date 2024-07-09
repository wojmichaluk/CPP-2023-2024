#include "shapecomposite.h"

Shapes::ShapeComposite::ShapeComposite(std::shared_ptr<Shapes::Shape> shape1, std::shared_ptr<Shapes::Shape> shape2, Shapes::ShapeOperation op) : Shapes::Shape(), shape1{shape1}, shape2{shape2}, op{op} {}

bool Shapes::ShapeComposite::isIn(int x, int y) const {
    switch(this->op) {
        case Shapes::ShapeOperation::INTERSECTION:
            return shape1->isIn(x, y) && shape2->isIn(x, y);
            break;

        case Shapes::ShapeOperation::SUM:
            return shape1->isIn(x, y) || shape2->isIn(x, y);
            break;

        case Shapes::ShapeOperation::DIFFERENCE:
            return shape1->isIn(x, y) && !shape2->isIn(x, y);
            break;

        default: //shouldn't happen
            return false;
            break;
    }
}
