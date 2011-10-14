#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_
#include <cmath>

struct TexCoord {
  float s, t;
  TexCoord(void):
    s(0.0f),
    t(0.0f) {}

  TexCoord(float s, float t):
    s(s),
    t(t) {}
};

struct Colour {
  float r, g, b, a;
  Colour(float R, float G, float B, float A):
    r(R),
    g(G),
    b(B),
    a(A) {}

  Colour(void):
    r(0.0f),
    g(0.0f),
    b(0.0f),
    a(0.0f) {}
};

struct Vector2 {
  float x, y;
  Vector2(float X, float Y):
    x(X),
    y(y) {}

  Vector2(void):
    x(0.0f),
    y(0.0f) {}

  Vector2(const Vector2& v):
    x(v.x),
    y(v.y) {}

  Vector2 operator*(const float s) const {
    return Vector2(x*s, y*s);
  }

  Vector2& operator=(const Vector2& v) {
    if(this == &v) {
      return *this;
    }
    x = v.x;
    y = v.y;

    return *this;
  }

  Vector2& operator+=(const Vector2& v) {
    this->x += v.x;
    this->y += v.y;

    return *this;
  }

  const Vector2 operator-(const Vector2& v) const {
    Vector2 result;
    result.x = x - v.x;
    result.y = y - v.y;

    return result;
  }

  float length(void) const {
    return sqrtf(x*x+y*y);
  }

  void normalize(void) {
    float l = 1.0f / length();
    x *= l;
    y *= l;
  }
};

typedef Vector2 Vertex;

inline float degreesToRadians(const float degrees) {
  const float PIOver180 = 3.14159f / 180.0f;
  return degrees * PIOver180;
}

#endif
