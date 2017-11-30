#pragma once

template <class T = float> class MathHelpers
{
public:
    
    static constexpr T minus160dB = T (1e-8);
    
    static inline T tanhlimpoly (const T a)
    {
        const T x1 = T (0.5) * (std::fabsf (a + T (2.0)) - std::fabsf (a - T (2.0)));
        return x1 * (T (1.0) + (x1 * x1) * (T (-0.25) + std::fabsf (x1) * T (0.0625)));
    }
    
    static inline T minimum (const T b, const T x)
    {
        return T (0.5) * (x + b - std::fabsf (x - b));
    }
    
    static inline T clip (const T x, const T b)
    {
        return T (0.5) * (std::fabsf (x) + b - std::fabsf (x - b));
    }
    
    static inline T clip01 (const T x)
    {
        return std::max<T> (0.0f, std::min<T> (1.0f, x));
    }
    
    static inline T convertRange (const T x01, const T theMin, const T theMax)
    {
        return (x01 * (theMax - theMin)) + theMin;
    }
    
    static inline bool areEqual (const T a, const T b)
    {
        return std::fabsf (a - b) < 1e-6f;
    }
};
