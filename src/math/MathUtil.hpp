#pragma once

#include "Constants.hpp"

#include <cmath>

#define TMP_SCALAR(Type) template<typename Type, typename = std::enable_if_t<std::is_arithmetic_v<Type>>>

namespace cam::math {
TMP_SCALAR(T) inline bool isZero(T _val, float _eps = Float32::EPSILON) {
    return ((_val > -_eps) && (_val < _eps));
}
TMP_SCALAR(T) inline bool isNotZero(T _val, float _eps = Float32::EPSILON) {
    return ((_val <= -_eps) || (_val >= _eps));
}
TMP_SCALAR(T) inline bool isEqual(T _v1, T _v2, float _eps = Float32::EPSILON) {
    return (std::fabs(_v2 - _v1) <= _eps);
}
TMP_SCALAR(T) inline bool isNotEqual(T _v1, T _v2, float _eps = Float32::EPSILON) {
    return !(std::fabs(_v2 - _v1) <= _eps);
}
}    // namespace cam::math