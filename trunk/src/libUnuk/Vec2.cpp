#include "Vec2.h"

/// Get a 0.0 vector.
Vec2 Vec2::Zero() { return Vec2(0.0f, 0.0f); }

Vec2::Vec2(void) {
  x = 0;
  y = 0;
}

Vec2::Vec2(float xValue, float yValue) {
  x = xValue;
  y = yValue;
}

Vec2::Vec2(const Vec2 &v) {
  x = v.x;
  y = v.y;
}

Vec2::~Vec2(void) {
  x = 0;
  y = 0;
}

Vec2& Vec2::operator =(const Vec2 &v) {
  x = v.x;
  y = v.y;
  return *this;
}

Vec2& Vec2::operator+=(const Vec2 &v) {
  x += v.x;
  y += v.y;
  return *this;
}

Vec2& Vec2::operator-=(const Vec2 &v) {
  x -= v.x;
  y -= v.y;
  return *this;
}

Vec2& Vec2::operator*=(float c) {
  x *= c;
  y *= c;
  return *this;
}

/// Multiply by a vector2.
Vec2& Vec2::operator*=(const Vec2 &v) {
  x *= v.x;
  y *= v.y;
  return *this;
}
