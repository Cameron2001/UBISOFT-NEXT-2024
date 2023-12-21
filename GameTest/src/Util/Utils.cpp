#include "stdafx.h"
#include "Utils.h"



constexpr float Utils::Deg2Rad = 3.14159265359f / 180.0f;
constexpr float Utils::Rad2Deg = 180.0f / 3.14159265359f;
float Utils::Sign(float value)
{
    return (value < 0.0f) ? -1.0f : 1.0f;
}

float Utils::Clamp(float value, float min, float max)
{
    if (value < min) {
        value = min;
    }
    else if (value > max) {
        value = max;
    }
    return value;
}

vec2 Utils::Clamp(const vec2 vector, const float max_length)
{
    const auto sqr_magnitude = Utils::SquaredMagnitude(vector);
    if (sqr_magnitude > max_length * max_length)
    {
        const auto mag = sqrt(sqr_magnitude);
        const auto normalized_x = vector.x / mag;
        const auto normalized_y = vector.y / mag;
        return {normalized_x * max_length, normalized_y * max_length};
    }
    return vector;
}

float Utils::Clamp(float value)
{
    auto result = 0.0f;
    if (value < 0.0f) {
        result = 0.0f;
    }
    else if (value > 1.0f) {
        result = 1.0f;
    }
    else {
        result = value;
    }
    return result;
}

float Utils::Lerp(float a, float b, float t)
{
    return a + (b - a) * Utils::Clamp(t);
}

vec2 Utils::Lerp(vec2 a, vec2 b, float t)
{
    const auto lerp_xs = Lerp(a.x, b.x, t);
    const auto lerp_ys = Lerp(a.y, b.y, t);
    return {lerp_xs, lerp_ys};
}

float Utils::LerpUnclamped(float a, float b, float t)
{
    return a + (b - a) * t;
}

float Utils::LerpAngle(float a, float b, float t)
{
    auto num = Utils::Repeat(b - a, 360.0);
    if (num > 180.0f) 
    {
        num -= 360.0f;
    }
    return a + num * Utils::Clamp(t);
}

float Utils::Repeat(float t, float length)
{
    return Clamp(t - floor(t / length) * length, 0.0f, length);
}

float Utils::Distance(vec2 a, vec2 b)
{
    const auto x = b.x - a.x;
    const auto y = b.y - a.y;
    return sqrt((x * x) + (y * y));
}

float Utils::SquaredDistance(vec2 a, vec2 b)
{
    const auto x = b.x - a.x;
    const auto y = b.y - a.y;
    return (x * x) + (y * y);
}

float Utils::Magnitude(vec2 vector)
{
    const auto x = vector.x;
    const auto y = vector.y;
    return sqrt((x * x) + (y * y));
}

float Utils::SquaredMagnitude(vec2 vector)
{
    const auto x = vector.x;
    const auto y = vector.y;
    return (x * x) + (y * y);
}

vec2 Utils::LimitMagnitude(vec2 vector, float magnitude)
{
    const auto length = Magnitude(vector);
    if (length > magnitude) {
        const auto limiter = magnitude / length;
        vector.x *= limiter;
        vector.y *= limiter;
        return vector;
    }
    return vector;
}

float Utils::Length(vec2 vec)
{
    return sqrtf(vec.x * vec.x + vec.y * vec.y);
}

float Utils::LengthSquared(vec2 vec)
{
    return vec.x * vec.x + vec.y * vec.y;
}

vec2 Utils::Min(vec2 vec_a, vec2 vec_b)
{
    return { min(vec_a.x, vec_b.x) , min(vec_a.y, vec_b.y) };
}

float Utils::Min(float a, float b)
{
    return a < b ? a : b;
}

vec2 Utils::Max(vec2 vec_a, vec2 vec_b)
{
    return { max(vec_a.x, vec_b.x), max(vec_a.y, vec_b.y)};
}

float Utils::Max(float a, float b)
{
    return a > b ? a : b;
}

vec2 Utils::Negate(vec2 vec)
{
    return { -vec.x, -vec.y };
}

vec2 Utils::Inverse(vec2 vec)
{
    return {1.0f / vec.x, 1.0f / vec.y};
}

vec2 Utils::Normalize(vec2 vec)
{
    vec2 dest;
    const auto x = vec.x;
    const auto y = vec.y;
    auto length = (x * x) + (y * y);
    if (length > 0) 
    {
        length = 1.0f / sqrt(length);
        dest.x = vec.x * length;
        dest.y = vec.y * length;
    }
    return dest;
}

float Utils::Angle(vec2 from, vec2 to)
{
    return acos(Clamp(Dot(Normalize(from), Normalize(to)), -1.0f, 1.0f)) * 57.29578f;
}

float Utils::Dot(vec2 lhs, vec2 rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

float Utils::SignedAngle(vec2 from, vec2 to)
{
    const auto unsigned_angle = Utils::Angle(from, to);
    const auto sign = Utils::Sign(from.x * to.y - from.y * to.x);
    return unsigned_angle * sign;
}

vec2 Utils::Project(vec2 a, vec2 b)
{
    return b * (Dot(a, b) / LengthSquared(b));
}

Utils::Utils()
= default;

Utils::~Utils()
= default;
