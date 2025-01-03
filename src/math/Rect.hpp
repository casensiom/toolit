#pragma once

#include "Constants.hpp"
#include "MathUtil.hpp"
#include "Vector2.hpp"

#include <type_traits>
#include <vector>

namespace cam::math {

TMP_SCALAR(U)
class RectBase {
    Vector2Base<U> pos;
    Vector2Base<U> size;

public:
    RectBase() = default;
    RectBase(U x, U y, U width, U height) : pos(x, y), size(width, height) {
    }

    inline Vector2Base<U>
    getPos() const {
        return pos;
    }
    inline Vector2Base<U>
    getSize() const {
        return size;
    }
    inline U
    getWidth() const {
        return size.getX();
    }
    inline U
    getHeight() const {
        return size.getY();
    }

    inline Vector2Base<U>
    tl() const {
        return pos;
    }
    inline Vector2Base<U>
    tr() const {
        return pos + Vector2Base<U>(size.getX(), 0);
    }
    inline Vector2Base<U>
    br() const {
        return pos + size;
    }
    inline Vector2Base<U>
    bl() const {
        return pos + Vector2Base<U>(0, size.getY());
    }

    TMP_SCALAR(T)
    static RectBase<T>
    wrap(const std::vector<Vector2Base<T>> &points) {
        if(points.empty()) {
            return RectBase<T>();
        }

        T minX = std::numeric_limits<T>::max();
        T maxX = std::numeric_limits<T>::min();
        T minY = std::numeric_limits<T>::max();
        T maxY = std::numeric_limits<T>::min();

        for(const auto &e : points) {
            minX = std::min(minX, e.getX());
            maxX = std::max(maxX, e.getX());
            minY = std::min(minY, e.getY());
            maxY = std::max(maxY, e.getY());
        }

        return RectBase<T>(minX, minY, maxX - minX, maxY - minY);
    }

    inline U
    area() const {
        return size.getX() * size.getY();
    }
};

using Rect  = RectBase<double>;
using Recti = RectBase<int>;
using Rectf = RectBase<float>;

}    // namespace cam::math
