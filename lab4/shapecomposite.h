#ifndef SHAPECOMPOSITE_H
#define SHAPECOMPOSITE_H

#include "shape.h"
#include <memory>

class Shapes::ShapeComposite : public Shapes::Shape {
public:
    ShapeComposite(std::shared_ptr<Shapes::Shape> shape1, std::shared_ptr<Shapes::Shape> shape2, Shapes::ShapeOperation op);

    bool isIn(int x, int y) const override;

private:
    std::shared_ptr<Shapes::Shape> shape1;
    std::shared_ptr<Shapes::Shape> shape2;
    Shapes::ShapeOperation op; 
};

#endif // SHAPECOMPOSITE_H
