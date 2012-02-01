#include <math.h>

#include "Vec2.h"

Vec2 Vec2::Zero(0.0f, 0.0f);
Vec2 Vec2::One(1.0f, 1.0f);
Vec2 Vec2::UnitX(1.0f, 0.0f);
Vec2 Vec2::UnitY(0.0f, 1.0f);

Vec2::Vec2(void) : x(0), y(0) {

}

Vec2::Vec2(float xArg, float yArg) : x(xArg), y(yArg) {

}

Vec2::Vec2(float value) : x(value), y(value) {

}

Vec2::Vec2(const Vec2i &copy) : x(copy.x), y(copy.y) {

}
