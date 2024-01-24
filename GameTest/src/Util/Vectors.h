//------------------------------------------------------------------------
// Vectors.h
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
struct vec2
{
    float x;
    float y;
    vec2();
    vec2(float x, float y);
    vec2 operator+(const vec2& obj) const;
    vec2 operator-(const vec2& obj) const;
    vec2 operator*(const vec2& obj) const;
    vec2 operator*(const float& obj) const;
    vec2 operator/(const vec2& obj) const;
    vec2 operator/(const float& obj) const;
    vec2& operator+=(const vec2& obj);
    vec2& operator-=(const vec2& obj);
    vec2& operator*=(const vec2& obj);
    vec2& operator*=(const float& obj);
    vec2& operator/=(const vec2& obj);
    vec2& operator/=(const float& obj);
};

struct vec3
{
    float x;
    float y;
    float z;
    vec3();
    vec3(float x, float y, float z);
    vec3 operator+(const vec3& obj) const;
    vec3 operator-(const vec3& obj) const;
    vec3 operator*(const vec3& obj) const;
    vec3 operator*(const float& obj) const;
    vec3 operator/(const vec3& obj) const;
    vec3 operator/(const float& obj) const;
    vec3& operator+=(const vec3& obj);
    vec3& operator-=(const vec3& obj);
    vec3& operator*=(const vec3& obj);
    vec3& operator*=(const float& obj);
    vec3& operator/=(const vec3& obj);
    vec3& operator/=(const float& obj);
};

struct vec4
{
    float x;
    float y;
    float w;
    float h;
    vec4();
    vec4(float x, float y, float w, float h);
    vec4 operator+(const vec4& obj) const;
    vec4 operator-(const vec4& obj) const;
    vec4 operator*(const vec4& obj) const;
    vec4 operator*(const float& obj) const;
    vec4 operator/(const vec4& obj) const;
    vec4 operator/(const float& obj) const;
    vec4& operator+=(const vec4& obj);
    vec4& operator-=(const vec4& obj);
    vec4& operator*=(const vec4& obj);
    vec4& operator*=(const float& obj);
    vec4& operator/=(const vec4& obj);
    vec4& operator/=(const float& obj);
};
