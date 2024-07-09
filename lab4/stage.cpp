#include "stage.h"
#include <iomanip>

Stage::Stage(int width, int height) : width{width}, height{height} {}

void Stage::drawShape2Stream(const Shapes::Shape* shape, std::ostream& os) const {
    for (int y = height; y >= 0; y--) {
        os << std::right << std::setw(2) << y << ": ";

        for (int x = 0; x <= width; x++) {
            os << shape->isIn(x, y);
        }

        os << std::endl;
    }
}
