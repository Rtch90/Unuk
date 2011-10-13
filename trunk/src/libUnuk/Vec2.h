#ifndef _VEC2_H_
#define _VEC2_H_

class Vec2
{
public:
  static Vec2 Zero();
  Vec2(void);
  Vec2(float xValue, float yValue);
  Vec2(const Vec2 &v);
  ~Vec2(void);

  // the operators are required to allow the system to understand how to compute mathematical problems
  // Copy operator
  Vec2& operator=(const Vec2 &v);

  // Addition operator
  Vec2& operator+=(const Vec2 &v);

  // Subtraction operator
  Vec2& operator-=(const Vec2 &v);

  // Multiply by a scalar
  Vec2& operator*=(float c);

  // Multiply by a vector2.
  Vec2& operator*=(const Vec2 &v);

  float x;
  float y;
};

#endif
