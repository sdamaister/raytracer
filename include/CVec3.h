#ifndef _VEC_H_
#define _VEC_H_

#include <math.h>
#include <stdlib.h>
#include <iostream>

class CVec3
{
public:
    CVec3() {}
    CVec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }

    inline float x() const { return e[0]; }
    inline float y() const { return e[1]; }
    inline float z() const { return e[2]; }
    inline float r() const { return e[0]; }
    inline float g() const { return e[1]; }
    inline float b() const { return e[2]; }

    inline const CVec3& operator+ ()      const { return *this;      }
    inline CVec3        operator- ()      const { return CVec3(-e[0], -e[1], -e[2]); }
    inline float        operator[](int i) const { return e[i]; }
    inline float&       operator[](int i)       { return e[i]; }

    inline CVec3&       operator+=(const CVec3& v);
    inline CVec3&       operator-=(const CVec3& v);
    inline CVec3&       operator*=(const CVec3& v);
    inline CVec3&       operator/=(const CVec3& v);
    inline CVec3&       operator*=(float t);
    inline CVec3&       operator/=(float t);

    inline float SquaredLength () const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
    inline float Length        () const { return sqrt(SquaredLength()); }
    inline void  MakeUnitVector();

    float e[3];
};

inline std::istream& operator>>(std::istream& is, CVec3& t)
{
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}

inline std::ostream& operator>>(std::ostream& os, const CVec3& t)
{
    os << t.e[0] << " " << t.e[1] << " " << t.e[2];
    return os;
}

inline void CVec3::MakeUnitVector()
{
    const float k = 1.0f / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
}

inline CVec3 operator+(const CVec3 a, const CVec3 b)
{
    return CVec3(a.x() + b.x(), a.y() + b.y(), a.z() + b.z());
}

inline CVec3 operator-(const CVec3 a, const CVec3 b)
{
    return CVec3(a.x() - b.x(), a.y() - b.y(), a.z() - b.z());
}
inline CVec3 operator*(const CVec3 a, const CVec3 b)
{
    return CVec3(a.x() * b.x(), a.y() * b.y(), a.z() * b.z());
}
inline CVec3 operator/(const CVec3 a, const CVec3 b)
{
    return CVec3(a.x() / b.x(), a.y() / b.y(), a.z() / b.z());
}

inline CVec3 operator*(const CVec3 a, float t)
{
    return CVec3(a.x()*t, a.y()*t, a.z()*t);
}

inline CVec3 operator*(float t, const CVec3 a)
{
    return a * t;
}

inline CVec3 operator/(const CVec3 a, float t)
{
    return CVec3(a.x()/t, a.y()/t, a.z()/t);
}

inline float dot(const CVec3& a, const CVec3& b)
{
    return a.e[0] * b.e[0] + a.e[1] * b.e[1] + a.e[2] * b.e[2];
}

inline CVec3 cross(const CVec3& a, const CVec3& b)
{
    return CVec3( (a.e[1] * b.e[2] - a.e[2] * b.e[1]),
                 -(a.e[0] * b.e[2] - a.e[2] * b.e[0]),
                  (a.e[0] * b.e[1] - a.e[1] * b.e[0]) );
}

inline CVec3& CVec3::operator+=(const CVec3& v)
{
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

inline CVec3& CVec3::operator-=(const CVec3& v)
{
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this;
}

inline CVec3& CVec3::operator*=(const CVec3& v)
{
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];
    return *this;
}

inline CVec3& CVec3::operator/=(const CVec3& v)
{
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    e[2] /= v.e[2];
    return *this;
}

inline CVec3& CVec3::operator*=(float t)
{
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

inline CVec3& CVec3::operator/=(float t)
{
const float k = 1.0f/t;

    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
    return *this;
}

inline CVec3 UnitVector(const CVec3& v)
{
    return v / v.Length(); 
}


#endif // _VEC_H_