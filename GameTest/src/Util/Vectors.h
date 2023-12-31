#pragma once

struct vec2
{
    float x;
    float y;
    vec2();
    vec2(float x, float y);
    vec2 operator+(vec2 const& obj) const;
    vec2 operator-(vec2 const& obj) const;
    vec2 operator*(vec2 const& obj) const;
    vec2 operator*(float const& obj) const;
    vec2 operator/(vec2 const& obj) const;
    vec2 operator/(float const& obj) const;
    vec2& operator+=(vec2 const& obj);
    vec2& operator-=(vec2 const& obj);
    vec2& operator*=(vec2 const& obj);
    vec2& operator*=(float const& obj);
    vec2& operator/=(vec2 const& obj);
    vec2& operator/=(float const& obj);
    
};

struct vec3
{
    float x;
    float y;
    float z;
    vec3();
    vec3(float x, float y, float z);
    vec3 operator+(vec3 const& obj) const;
    vec3 operator-(vec3 const& obj) const;
    vec3 operator*(vec3 const& obj) const;
    vec3 operator*(float const& obj) const;
    vec3 operator/(vec3 const& obj) const;
    vec3 operator/(float const& obj) const;
    vec3& operator+=(vec3 const& obj);
    vec3& operator-=(vec3 const& obj);
    vec3& operator*=(vec3 const& obj);
    vec3& operator*=(float const& obj);
    vec3& operator/=(vec3 const& obj);
    vec3& operator/=(float const& obj);
};
struct vec4
{
    float x;
    float y;
    float w;
    float h;
    vec4();
    vec4(float x,float y,float w, float h);
    vec4 operator+(vec4 const& obj) const;
    vec4 operator-(vec4 const& obj) const;
    vec4 operator*(vec4 const& obj) const;
    vec4 operator*(float const& obj) const;
    vec4 operator/(vec4 const& obj) const;
    vec4 operator/(float const& obj) const;
    vec4& operator+=(vec4 const& obj);
    vec4& operator-=(vec4 const& obj);
    vec4& operator*=(vec4 const& obj);
    vec4& operator*=(float const& obj);
    vec4& operator/=(vec4 const& obj);
    vec4& operator/=(float const& obj);
};
