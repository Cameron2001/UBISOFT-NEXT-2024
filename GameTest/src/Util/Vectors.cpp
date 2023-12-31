#include "stdafx.h"
#include "Vectors.h"

vec2::vec2()
{
    this->x = 0.0f;
    this->y = 0.0f;
}

vec2::vec2(float x, float y)
{
    this->x = x;
    this->y = y;
}

vec2 vec2::operator+(vec2 const& obj) const
{
    vec2 vector;
    vector.x = x + obj.x;
    vector.y = y + obj.y;
    return vector;
    
}

vec2 vec2::operator-(vec2 const& obj) const
{
    vec2 vector;
    vector.x = x - obj.x;
    vector.y = y - obj.y;
    return vector;
}


vec2 vec2::operator*(vec2 const& obj) const
{
    vec2 vector;
    vector.x = x * obj.x;
    vector.y = y * obj.y;
    return vector;
}

vec2 vec2::operator*(float const& obj) const
{
    vec2 vector;
    vector.x = x * obj;
    vector.y = y * obj;
    return vector;
}

vec2 vec2::operator/(vec2 const& obj) const
{
    vec2 vector;
    vector.x = x / obj.x;
    vector.y = y / obj.y;
    return vector;
}

vec2 vec2::operator/(float const& obj) const
{
    vec2 vector;
    vector.x = x / obj;
    vector.y = y / obj;
    return vector;
}

vec2& vec2::operator+=(vec2 const& obj)
{
    x+=obj.x;
    y+=obj.y;
    return *this;
}


vec2& vec2::operator-=(vec2 const& obj)
{
    x-=obj.x;
    y-=obj.y;
    return *this;
}

vec2& vec2::operator*=(vec2 const& obj)
{
    x*=obj.x;
    y*=obj.y;
    return *this;
}

vec2& vec2::operator*=(float const& obj)
{
    x*=obj;
    y*=obj;
    return *this;
}

vec2& vec2::operator/=(vec2 const& obj)
{
    x/=obj.x;
    y/=obj.y;
    return *this;
}

vec2& vec2::operator/=(float const& obj)
{
    x/=obj;
    y/=obj;
    return *this;
}


vec3::vec3()
{
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
}

vec3::vec3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

vec3 vec3::operator+(vec3 const& obj) const
{
    vec3 vector;
    vector.x = x + obj.x;
    vector.y = y + obj.y;
    vector.z = z + obj.z;
    return vector;
}

vec3 vec3::operator-(vec3 const& obj) const
{
    vec3 vector;
    vector.x = x - obj.x;
    vector.y = y - obj.y;
    vector.z = z - obj.z;
    return vector;
}

vec3 vec3::operator*(vec3 const& obj) const
{
    vec3 vector;
    vector.x = x * obj.x;
    vector.y = y * obj.y;
    vector.z = z * obj.z;
    return vector;
}

vec3 vec3::operator*(float const& obj) const
{
    vec3 vector;
    vector.x = x * obj;
    vector.y = y * obj;
    vector.z = z * obj;
    return vector;
}

vec3 vec3::operator/(vec3 const& obj) const
{
    vec3 vector;
    vector.x = x / obj.x;
    vector.y = y / obj.y;
    vector.z = z / obj.z;
    return vector;
}

vec3 vec3::operator/(float const& obj) const
{
    vec3 vector;
    vector.x = x / obj;
    vector.y = y / obj;
    vector.z = z / obj;
    return vector;
}

vec3& vec3::operator+=(vec3 const& obj)
{
    x+=obj.x;
    y+=obj.y;
    z+=obj.z;
    return *this;
}

vec3& vec3::operator-=(vec3 const& obj)
{
    x-=obj.x;
    y-=obj.y;
    z-=obj.z;
    return *this;
}

vec3& vec3::operator*=(vec3 const& obj)
{
    x*=obj.x;
    y*=obj.y;
    z*=obj.z;
    return *this;
}

vec3& vec3::operator*=(float const& obj)
{
    x*=obj;
    y*=obj;
    z*=obj;
    return *this;
}

vec3& vec3::operator/=(vec3 const& obj)
{
    x/=obj.x;
    y/=obj.y;
    z/=obj.z;
    return *this;
}

vec3& vec3::operator/=(float const& obj)
{
    x/=obj;
    y/=obj;
    z/=obj;
    return *this;
}


vec4::vec4()
{
    this->x = 0.0f;
    this->y = 0.0f;
    this->w = 0.0f;
    this->h = 0.0f;
}

vec4::vec4(float x, float y, float w, float h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

vec4 vec4::operator+(vec4 const& obj) const
{
    vec4 vector;
    vector.x = x + obj.x;
    vector.y = y + obj.y;
    vector.w = w + obj.w;
    vector.h = h + obj.h;
    return vector;
}

vec4 vec4::operator-(vec4 const& obj) const
{
    vec4 vector;
    vector.x = x - obj.x;
    vector.y = y - obj.y;
    vector.w = w - obj.w;
    vector.h = h - obj.h;
    return vector;
}

vec4 vec4::operator*(vec4 const& obj) const
{
    vec4 vector;
    vector.x = x * obj.x;
    vector.y = y * obj.y;
    vector.w = w * obj.w;
    vector.h = h * obj.h;
    return vector;
}

vec4 vec4::operator*(float const& obj) const
{
    vec4 vector;
    vector.x = x * obj;
    vector.y = y * obj;
    vector.w = w * obj;
    vector.h = h * obj;
    return vector;
}

vec4 vec4::operator/(vec4 const& obj) const
{
    vec4 vector;
    vector.x = x / obj.x;
    vector.y = y / obj.y;
    vector.w = w / obj.w;
    vector.h = h / obj.h;
    return vector;
}

vec4 vec4::operator/(float const& obj) const
{
    vec4 vector;
    vector.x = x / obj;
    vector.y = y / obj;
    vector.w = w / obj;
    vector.h = h / obj;
    return vector;
}

vec4& vec4::operator+=(vec4 const& obj)
{
    x+=obj.x;
    y+=obj.y;
    w+=obj.w;
    h+=obj.h;
    return *this;
}

vec4& vec4::operator-=(vec4 const& obj)
{
    x-=obj.x;
    y-=obj.y;
    w-=obj.w;
    h-=obj.h;
    return *this;
}

vec4& vec4::operator*=(vec4 const& obj)
{
    x*=obj.x;
    y*=obj.y;
    w*=obj.w;
    h*=obj.h;
    return *this;
}

vec4& vec4::operator*=(float const& obj)
{
    x*=obj;
    y*=obj;
    w*=obj;
    h*=obj;
    return *this;
}

vec4& vec4::operator/=(vec4 const& obj)
{
    x/=obj.x;
    y/=obj.y;
    w/=obj.w;
    h/=obj.h;
    return *this;
}

vec4& vec4::operator/=(float const& obj)
{
    x/=obj;
    y/=obj;
    w/=obj;
    h/=obj;
    return *this;
}

