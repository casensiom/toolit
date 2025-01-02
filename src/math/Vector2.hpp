#pragma once

#include "Constants.hpp"
#include "MathUtil.hpp"

#include <stdint.h>
#include <stdexcept>
#include <type_traits>
#include <algorithm>

namespace cam::math {

TMP_SCALAR(U)
class Vector2Base {
    U x = 0;
    U y = 0;

public:
    Vector2Base() = default;
    Vector2Base(U v) : x(v), y(v) {
    }
    Vector2Base(U x_, U y_) : x(x_), y(y_) {
    }

    inline U
    getX() const {
        return x;
    }
    inline U
    getY() const {
        return y;
    }

    U
    distance(const Vector2Base &other, Distance type = EUCLIDEAN) const {
        Vector2Base diff = other - *this;
        double      ret  = 0;
        switch(type) {
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

    TMP_SCALAR(T) void set(T _v) {
        x = static_cast<U>(_v);
        y = static_cast<U>(_v);
    }
    TMP_SCALAR(T) void set(T _x, T _y) {
        x = static_cast<U>(_x);
        y = static_cast<U>(_y);
    }
    void
    set(const Vector2Base &rho) {
        x = rho.x;
        y = rho.y;
    }
    bool
    isEqual(const Vector2Base &rho, double error = Float64::EPSILON) const {
        return cam::math::isEqual(x, rho.x, error) && cam::math::isEqual(y, rho.y, error);
    }
    bool
    isNotEqual(const Vector2Base &rho, double error = Float64::EPSILON) const {
        return cam::math::isNotEqual(x, rho.x, error) && cam::math::isNotEqual(y, rho.y, error);
    }

    bool
    operator==(const Vector2Base &rho) const {
        return ((x == rho.x) && (y == rho.y));
    }
    bool
    operator!=(const Vector2Base &rho) const {
        return ((x != rho.x) || (y != rho.y));
    }
    bool
    operator<(const Vector2Base &rho) const {
        return (x < rho.x) && (y < rho.y);
    }
    bool
    operator>(const Vector2Base &rho) const {
        return (x > rho.x) && (y > rho.y);
    }
    const Vector2Base &
    operator+() const {
        return *this;
    }
    Vector2Base
    operator-() const {
        return Vector2Base(-x, -y);
    }
    TMP_SCALAR(T)
    void
    operator+=(T scalar) {
        x += static_cast<U>(scalar);
        y += static_cast<U>(scalar);
    }
    void
    operator+=(const Vector2Base &rho) {
        x += rho.x;
        y += rho.y;
    }
    TMP_SCALAR(T)
    void
    operator-=(T scalar) {
        x -= static_cast<U>(scalar);
        y -= static_cast<U>(scalar);
    }
    void
    operator-=(const Vector2Base &rho) {
        x -= rho.x;
        y -= rho.y;
    }
    TMP_SCALAR(T)
    void
    operator*=(T scalar) {
        x *= static_cast<U>(scalar);
        y *= static_cast<U>(scalar);
    }
    void
    operator*=(const Vector2Base &rho) {
        x *= rho.x;
        y *= rho.y;
    }

    TMP_SCALAR(T)
    void
    operator/=(T scalar) {
        bool ret = cam::math::isNotZero(scalar);
        if(ret) {
            x /= scalar;
            y /= scalar;
        }
    }
    void
    operator/=(const Vector2Base &rho) {
        if(cam::math::isNotZero(rho.x) && cam::math::isNotZero(rho.y)) {
            x /= rho.x;
            y /= rho.y;
        }
    }

    TMP_SCALAR(T)
    friend Vector2Base
    operator+(const Vector2Base &v, T scalar) {
        return Vector2Base(v.x + scalar, v.y + scalar);
    }
    TMP_SCALAR(T)
    friend Vector2Base
    operator+(T scalar, const Vector2Base &v) {
        return Vector2Base(scalar + v.x, scalar + v.y);
    }
    friend Vector2Base
    operator+(const Vector2Base &lho, const Vector2Base &v2) {
        return Vector2Base(lho.x + v2.x, lho.y + v2.y);
    }

    TMP_SCALAR(T)
    friend Vector2Base
    operator-(const Vector2Base &v, T scalar) {
        return Vector2Base(v.x - scalar, v.y - scalar);
    }
    TMP_SCALAR(T)
    friend Vector2Base
    operator-(T scalar, const Vector2Base &v) {
        return Vector2Base(scalar - v.x, scalar - v.y);
    }
    friend Vector2Base
    operator-(const Vector2Base &lho, const Vector2Base &rho) {
        return Vector2Base(lho.x - rho.x, lho.y - rho.y);
    }

    TMP_SCALAR(T)
    friend Vector2Base
    operator*(const Vector2Base &v, T scalar) {
        return Vector2Base(v.x * scalar, v.y * scalar);
    }
    TMP_SCALAR(T)
    friend Vector2Base
    operator*(T scalar, const Vector2Base &v) {
        return Vector2Base(scalar * v.x, scalar * v.y);
    }
    friend Vector2Base
    operator*(const Vector2Base &lho, const Vector2Base &rho) {
        return Vector2Base(lho.x * rho.x, lho.y * rho.y);
    }

    TMP_SCALAR(T)
    friend Vector2Base
    operator/(const Vector2Base &v, T scalar) {
        if(cam::math::isNotZero(scalar)) {
            return Vector2Base(v.x / scalar, v.y / scalar);
        }
        return v;
    }
    TMP_SCALAR(T)
    friend Vector2Base
    operator/(T scalar, const Vector2Base &v) {
        if(cam::math::isNotZero(v.x) && cam::math::isNotZero(v.y)) {
            return Vector2Base(scalar / v.x, scalar / v.y);
        }
        return Vector2Base(scalar);
    }
    friend Vector2Base
    operator/(const Vector2Base &lho, const Vector2Base &rho) {
        if(cam::math::isNotZero(rho.x) && cam::math::isNotZero(rho.y)) {
            return Vector2Base(lho.x / rho.x, lho.y / rho.y);
        }
        return lho;
    }

    static inline const Vector2Base kZERO{static_cast<U>(0.0f)};
    static inline const Vector2Base kONE{static_cast<U>(1.0f)};
    static inline const Vector2Base kUNIT_X{static_cast<U>(1), static_cast<U>(0)};
    static inline const Vector2Base kUNIT_Y{static_cast<U>(0), static_cast<U>(1)};
};

using Vector2  = Vector2Base<double>;
using Vector2i = Vector2Base<int>;
using Vector2f = Vector2Base<float>;

}    // namespace cam::math