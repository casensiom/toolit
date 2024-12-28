#pragma once

#include "Constants.hpp"
#include "MathUtil.hpp"

#include <stdint.h>
#include <stdexcept>
#include <type_traits>

namespace cam::math {

class Vector2 {
    double x = 0;
    double y = 0;

public:
    Vector2() {}
    Vector2(double v) : x(v), y(v) {}
    Vector2(double x_, double y_) : x(x_), y(y_) {}

    TMP_SCALAR void  Set(T _v)                { x = (double)_v; y = (double)_v; }
    TMP_SCALAR void  Set(T _x, T _y)          { x = (double)_x; y = (double)_y; }
    void             Set(const Vector2 &rho)  { x = rho.x;      y = rho.y;      }
    bool             IsEqual   (const Vector2 &rho, double error = Float64::EPSILON) const { return cam::math::IsEqual(x, rho.x, error)    && cam::math::IsEqual(y, rho.y, error);    }
    bool             IsNotEqual(const Vector2 &rho, double error = Float64::EPSILON) const { return cam::math::IsNotEqual(x, rho.x, error) && cam::math::IsNotEqual(y, rho.y, error); }
    bool            operator == (const Vector2 &rho) const          { return ((x == rho.x) && (y == rho.y)); }
    bool            operator != (const Vector2 &rho) const          { return ((x != rho.x) || (y != rho.y)); }
    bool            operator < (const Vector2 &rho) const           { return (x < rho.x) && (y < rho.y); }
    bool            operator > (const Vector2 &rho) const           { return (x > rho.x) && (y > rho.y); }
    const Vector2 & operator + () const                             { return *this;                      }
    Vector2         operator - () const                             { return Vector2(-x, -y);            }
    TMP_SCALAR void operator += (T scalar)                          { x += (double)scalar; y += (double)scalar; }
    void            operator += (const Vector2 &rho)                { x += rho.x;          y += rho.y;          }
    TMP_SCALAR void operator -= (T scalar)                          { x -= (double)scalar; y -= (double)scalar; }
    void            operator -= (const Vector2 &rho)                { x -= rho.x;          y -= rho.y;          }
    TMP_SCALAR void operator *= (T scalar)                          { x *= (double)scalar; y *= (double)scalar; }
    void            operator *= (const Vector2 &rho)                { x *= rho.x;          y *= rho.y;          }
    
    TMP_SCALAR void operator /= (T scalar) {
        bool ret = cam::math::IsNotZero(scalar);
        if (ret) {
            x /= scalar;
            y /= scalar;
        }
    }
    void operator /= (const Vector2 &rho) {
        if (cam::math::IsNotZero(rho.x) && cam::math::IsNotZero(rho.y)) {
            x /= rho.x;
            y /= rho.y;
        }
    }

    TMP_SCALAR friend Vector2 operator+(const Vector2& v, T scalar) {
        return Vector2(v.x + scalar, v.y + scalar);
    }
    TMP_SCALAR friend Vector2 operator+(T scalar, const Vector2& v) {
        return Vector2(scalar + v.x, scalar + v.y);
    }
    friend Vector2 operator+(const Vector2& lho, const Vector2& v2) {
        return Vector2(lho.x + v2.x, lho.y + v2.y);
    }

    TMP_SCALAR friend Vector2 operator-(const Vector2& v, T scalar) {
        return Vector2(v.x - scalar, v.y - scalar);
    }
    TMP_SCALAR friend Vector2 operator-(T scalar, const Vector2& v) {
        return Vector2(scalar - v.x, scalar - v.y);
    }
    friend Vector2 operator-(const Vector2& lho, const Vector2& rho) {
        return Vector2(lho.x - rho.x, lho.y - rho.y);
    }

    TMP_SCALAR friend Vector2 operator*(const Vector2& v, T scalar) {
        return Vector2(v.x * scalar, v.y * scalar);
    }
    TMP_SCALAR friend Vector2 operator*(T scalar, const Vector2& v) {
        return Vector2(scalar * v.x, scalar * v.y);
    }
    friend Vector2 operator*(const Vector2& lho, const Vector2& rho) {
        return Vector2(lho.x * rho.x, lho.y * rho.y);
    }

    TMP_SCALAR friend Vector2 operator/(const Vector2& v, T scalar) {
        if (cam::math::IsNotZero(scalar)) {
            return Vector2(v.x / scalar, v.y / scalar);
        }
        return v;
    }
    TMP_SCALAR friend Vector2 operator/(T scalar, const Vector2& v) {
        if (cam::math::IsNotZero(v.x) && cam::math::IsNotZero(v.y)) {
            return Vector2(scalar / v.x, scalar / v.y);
        }
        return Vector2(scalar);
    }
    friend Vector2 operator/(const Vector2& lho, const Vector2& rho) {
        if (cam::math::IsNotZero(rho.x) && cam::math::IsNotZero(rho.y)) {
            return Vector2(lho.x / rho.x, lho.y / rho.y);
        }
        return lho;
    }

    static const Vector2 kZERO;
    static const Vector2 kONE;
    static const Vector2 kUNIT_X;
    static const Vector2 kUNIT_Y;
};

}    // namespace cam::math