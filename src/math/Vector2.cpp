#include "Vector2.hpp"

namespace cam::math {

const Vector2  Vector2::kZERO(0.0f);
const Vector2  Vector2::kONE(1.0f);
const Vector2  Vector2::kUNIT_X(1, 0);
const Vector2  Vector2::kUNIT_Y(0, 1);

double 
Vector2::distance(const Vector2 &other, Distance type) const {
    Vector2 diff = other - *this;
    double ret = 0;
    switch (type)
    {
    case MANHATTAN:
        ret = std::abs(diff.getX()) + std::abs(diff.getY());
        break;
    case EUCLIDEAN:
        ret = std::sqrt(diff.getX() * diff.getX() + diff.getY() * diff.getY());
        break;
    case CHEBYSHEV:
        ret = std::max(std::abs(diff.getX()), std::abs(diff.getY()));
        break;
    }
    return ret;
}

}