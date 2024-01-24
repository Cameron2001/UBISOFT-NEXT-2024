//------------------------------------------------------------------------
// Vectors.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include "Vectors.h"
//------------------------------------------------------------------------

vec2::vec2()
{
    this->x = 0.0f;
    this->y = 0.0f;
}

vec2::vec2(const float x, const float y)
{
    this->x = x;
    this->y = y;
}

vec2 vec2::operator+(const vec2& obj) const
{
    vec2 vector;
    vector.x = x + obj.x;
    vector.y = y + obj.y;
    return vector;
}

vec2 vec2::operator-(const vec2& obj) const
{
    vec2 vector;
    vector.x = x - obj.x;
    vector.y = y - obj.y;
    return vector;
}


vec2 vec2::operator*(const vec2& obj) const
{
    vec2 vector;
    vector.x = x * obj.x;
    vector.y = y * obj.y;
    return vector;
}

vec2 vec2::operator*(const float& obj) const
{
    vec2 vector;
    vector.x = x * obj;
    vector.y = y * obj;
    return vector;
}

vec2 vec2::operator/(const vec2& obj) const
{
    vec2 vector;
    vector.x = x / obj.x;
    vector.y = y / obj.y;
    return vector;
}

vec2 vec2::operator/(const float& obj) const
{
    vec2 vector;
    vector.x = x / obj;
    vector.y = y / obj;
    return vector;
}

vec2& vec2::operator+=(const vec2& obj)
{
    x += obj.x;
    y += obj.y;
    return *this;
}


vec2& vec2::operator-=(const vec2& obj)
{
    x -= obj.x;
    y -= obj.y;
    return *this;
}

vec2& vec2::operator*=(const vec2& obj)
{
    x *= obj.x;
    y *= obj.y;
    return *this;
}

vec2& vec2::operator*=(const float& obj)
{
    x *= obj;
    y *= obj;
    return *this;
}

vec2& vec2::operator/=(const vec2& obj)
{
    x /= obj.x;
    y /= obj.y;
    return *this;
}

vec2& vec2::operator/=(const float& obj)
{
    x /= obj;
    y /= obj;
    return *this;
}


vec3::vec3()
{
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
}

vec3::vec3(const float x, const float y, const float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

vec3 vec3::operator+(const vec3& obj) const
{
    vec3 vector;
    vector.x = x + obj.x;
    vector.y = y + obj.y;
    vector.z = z + obj.z;
    return vector;
}

vec3 vec3::operator-(const vec3& obj) const
{
    vec3 vector;
    vector.x = x - obj.x;
    vector.y = y - obj.y;
    vector.z = z - obj.z;
    return vector;
}

vec3 vec3::operator*(const vec3& obj) const
{
    vec3 vector;
    vector.x = x * obj.x;
    vector.y = y * obj.y;
    vector.z = z * obj.z;
    return vector;
}

vec3 vec3::operator*(const float& obj) const
{
    vec3 vector;
    vector.x = x * obj;
    vector.y = y * obj;
    vector.z = z * obj;
    return vector;
}

vec3 vec3::operator/(const vec3& obj) const
{
    vec3 vector;
    vector.x = x / obj.x;
    vector.y = y / obj.y;
    vector.z = z / obj.z;
    return vector;
}

vec3 vec3::operator/(const float& obj) const
{
    vec3 vector;
    vector.x = x / obj;
    vector.y = y / obj;
    vector.z = z / obj;
    return vector;
}

vec3& vec3::operator+=(const vec3& obj)
{
    x += obj.x;
    y += obj.y;
    z += obj.z;
    return *this;
}

vec3& vec3::operator-=(const vec3& obj)
{
    x -= obj.x;
    y -= obj.y;
    z -= obj.z;
    return *this;
}

vec3& vec3::operator*=(const vec3& obj)
{
    x *= obj.x;
    y *= obj.y;
    z *= obj.z;
    return *this;
}

vec3& vec3::operator*=(const float& obj)
{
    x *= obj;
    y *= obj;
    z *= obj;
    return *this;
}

vec3& vec3::operator/=(const vec3& obj)
{
    x /= obj.x;
    y /= obj.y;
    z /= obj.z;
    return *this;
}

vec3& vec3::operator/=(const float& obj)
{
    x /= obj;
    y /= obj;
    z /= obj;
    return *this;
}


vec4::vec4()
{
    this->x = 0.0f;
    this->y = 0.0f;
    this->w = 0.0f;
    this->h = 0.0f;
}

vec4::vec4(const float x, const float y, const float w, const float h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

vec4 vec4::operator+(const vec4& obj) const
{
    vec4 vector;
    vector.x = x + obj.x;
    vector.y = y + obj.y;
    vector.w = w + obj.w;
    vector.h = h + obj.h;
    return vector;
}

vec4 vec4::operator-(const vec4& obj) const
{
    vec4 vector;
    vector.x = x - obj.x;
    vector.y = y - obj.y;
    vector.w = w - obj.w;
    vector.h = h - obj.h;
    return vector;
}

vec4 vec4::operator*(const vec4& obj) const
{
    vec4 vector;
    vector.x = x * obj.x;
    vector.y = y * obj.y;
    vector.w = w * obj.w;
    vector.h = h * obj.h;
    return vector;
}

vec4 vec4::operator*(const float& obj) const
{
    vec4 vector;
    vector.x = x * obj;
    vector.y = y * obj;
    vector.w = w * obj;
    vector.h = h * obj;
    return vector;
}

vec4 vec4::operator/(const vec4& obj) const
{
    vec4 vector;
    vector.x = x / obj.x;
    vector.y = y / obj.y;
    vector.w = w / obj.w;
    vector.h = h / obj.h;
    return vector;
}

vec4 vec4::operator/(const float& obj) const
{
    vec4 vector;
    vector.x = x / obj;
    vector.y = y / obj;
    vector.w = w / obj;
    vector.h = h / obj;
    return vector;
}

vec4& vec4::operator+=(const vec4& obj)
{
    x += obj.x;
    y += obj.y;
    w += obj.w;
    h += obj.h;
    return *this;
}

vec4& vec4::operator-=(const vec4& obj)
{
    x -= obj.x;
    y -= obj.y;
    w -= obj.w;
    h -= obj.h;
    return *this;
}

vec4& vec4::operator*=(const vec4& obj)
{
    x *= obj.x;
    y *= obj.y;
    w *= obj.w;
    h *= obj.h;
    return *this;
}

vec4& vec4::operator*=(const float& obj)
{
    x *= obj;
    y *= obj;
    w *= obj;
    h *= obj;
    return *this;
}

vec4& vec4::operator/=(const vec4& obj)
{
    x /= obj.x;
    y /= obj.y;
    w /= obj.w;
    h /= obj.h;
    return *this;
}

vec4& vec4::operator/=(const float& obj)
{
    x /= obj;
    y /= obj;
    w /= obj;
    h /= obj;
    return *this;
}
