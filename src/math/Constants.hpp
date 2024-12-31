#pragma once

#include <stdint.h>

namespace cam::math {

enum Distance {
    MANHATTAN,
    EUCLIDEAN,
    CHEBYSHEV
};

namespace Float64 {
    static constexpr double PI        = 3.14159265358979323846264338327950288;
    static constexpr double RADTODEG  = (180.0 / PI);
    static constexpr double DEGTORAD  = (PI / 180.0);
    static constexpr double E         = 2.7182818284590452353602874713527;
    static constexpr double EPSILON   = (1.0 / 65536.0);
}

namespace Float32 {
    static constexpr float PI        = (float)Float64::PI;
    static constexpr float RADTODEG  = (float)Float64::RADTODEG;
    static constexpr float DEGTORAD  = (float)Float64::DEGTORAD;
    static constexpr float E         = (float)Float64::E;
    static constexpr float EPSILON   = (float)Float64::EPSILON;
}

}