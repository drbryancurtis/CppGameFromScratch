#pragma once
#include <cmath>
#include <bit>
#include <cstdint>

namespace Math {
    inline float Q_rsqrt(float number) {
        const float x2 = number * 0.5F;
        const float threehalfs = 1.5F;
        uint32_t i = std::bit_cast<uint32_t>(number);
        i = 0x5f3759df - (i >> 1);
        float y = std::bit_cast<float>(i);
        y = y * (threehalfs - (x2 * y * y));
        return y;
    }
}

struct Vector2 {
    float x, y;
    void Normalize() {
        float lengthSq = x * x + y * y;
        if (lengthSq > 0.0001f) {
            float invLength = Math::Q_rsqrt(lengthSq);
            x *= invLength;
            y *= invLength;
        }
    }
};