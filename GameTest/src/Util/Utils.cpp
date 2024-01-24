//------------------------------------------------------------------------
// Utils.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include "Utils.h"
//------------------------------------------------------------------------


constexpr float utils::deg2Rad = 3.14159265359f / 180.0f;
constexpr float utils::rad2Deg = 180.0f / 3.14159265359f;

float utils::sign(const float value)
{
    return value < 0.0f ? -1.0f : 1.0f;
}

float utils::clamp(float value, const float min, const float max)
{
    if (value < min)
    {
        value = min;
    }
    else if (value > max)
    {
        value = max;
    }
    return value;
}

vec2 utils::clamp(const vec2 vector, const float max_length)
{
    const auto sqr_magnitude = squaredMagnitude(vector);
    if (sqr_magnitude > max_length * max_length)
    {
        const auto mag = sqrt(sqr_magnitude);
        const auto normalized_x = vector.x / mag;
        const auto normalized_y = vector.y / mag;
        return {normalized_x * max_length, normalized_y * max_length};
    }
    return vector;
}

float utils::clamp(const float value)
{
    auto result = 0.0f;
    if (value < 0.0f)
    {
        result = 0.0f;
    }
    else if (value > 1.0f)
    {
        result = 1.0f;
    }
    else
    {
        result = value;
    }
    return result;
}

float utils::lerp(const float a, const float b, const float t)
{
    return a + (b - a) * clamp(t);
}

vec2 utils::lerp(const vec2 a, const vec2 b, const float t)
{
    const auto lerp_xs = lerp(a.x, b.x, t);
    const auto lerp_ys = lerp(a.y, b.y, t);
    return {lerp_xs, lerp_ys};
}


float utils::distance(const vec2 a, const vec2 b)
{
    const auto x = b.x - a.x;
    const auto y = b.y - a.y;
    return sqrt(x * x + y * y);
}

float utils::squaredDistance(const vec2 a, const vec2 b)
{
    const auto x = b.x - a.x;
    const auto y = b.y - a.y;
    return x * x + y * y;
}

float utils::magnitude(const vec2 vector)
{
    const auto x = vector.x;
    const auto y = vector.y;
    return sqrt(x * x + y * y);
}

float utils::squaredMagnitude(const vec2 vector)
{
    const auto x = vector.x;
    const auto y = vector.y;
    return x * x + y * y;
}


float utils::length(const vec2 vector)
{
    return sqrtf(vector.x * vector.x + vector.y * vector.y);
}

float utils::lengthSquared(const vec2 vector)
{
    return vector.x * vector.x + vector.y * vector.y;
}


vec2 utils::normalize(const vec2 vector)
{
    vec2 dest;
    const auto x = vector.x;
    const auto y = vector.y;
    auto length = x * x + y * y;
    if (length > 0.0f)
    {
        length = 1.0f / sqrt(length);
        dest.x = vector.x * length;
        dest.y = vector.y * length;
    }
    return dest;
}


float utils::dot(const vec2 a, const vec2 b)
{
    return a.x * b.x + a.y * b.y;
}


vec2 utils::project(const vec2 a, const vec2 b)
{
    return b * (dot(a, b) / lengthSquared(b));
}


utils::utils()
= default;

utils::~utils()
= default;
