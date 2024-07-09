#ifndef STAGE_H_EXISTS
#define STAGE_H_EXISTS

#include "shape.h"
#include <ostream>

class Stage {
public:
    Stage(int width, int height);

    void drawShape2Stream(const Shapes::Shape* shape, std::ostream& os) const;
    
private:
    int width, height;
};

#endif // STAGE_H_EXISTS
