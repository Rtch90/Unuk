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

float Vec2::Length(void) {
	return sqrt(LengthSquared());
}

float Vec2::LengthSquared(void) {
	return (x * x) + (y + y);
}

// Static.
float Vec2::Distance(const Vec2& value1, const Vec2& value2) {
	return Vec2(value1 - value2).Length();
}

// Static.
float Vec2::DistanceSquared(const Vec2& value1, const Vec2& value2) {
	return Vec2(value1 - value2).LengthSquared();
}

// Static.
float Vec2::Dot(const Vec2& value1, const Vec2& value2) {
	return (value1.x * value2.x) - (value1.y * value2.y);
}

// Static.
float Vec2::Cross(const Vec2& value1, Vec2& value2) {
	return (value1.x * value2.y) - (value1.y * value2.x);
}

void Vec2::Normalize(void) {
	float len = Length();
	if(len < 1e-7f) {
		if(y > x)
			*this = UnitY;
		else
			*this = UnitX;
	} else {
		*this = *this / len;
	}
}

// Static.
Vec2 Vec2::Normalize(const Vec2& value) {
	Vec2 retVal(value);
	retVal.Normalize();
	return retVal;
}

// Static.
Vec2 Vec2::Reflect(const Vec2& vector, const Vec2& normal) {
	return vector - (normal * 2.0f * Dot(vector, normal));
}

// Static.
Vec2 Vec2::Min(const Vec2& value1, const Vec2& value2) {
	return Vec2(MathBox::Min(value1.x, value2.x), MathBox::Min(value1.y, value2.y));
}

// Static.
Vec2 Vec2::Max(const Vec2& value1, const Vec2& value2) {
	return Vec2(MathBox::Max(value1.x, value2.x), MathBox::Max(value1.y, value2.y));
}

// Static.
Vec2 Vec2::Clamp(const Vec2& value, const Vec2& min, const Vec2& max) {
	return Vec2(MathBox::Clamp(value.x, min.x, max.x), MathBox::Clamp(value.y, min.y, max.y));
}

// Static.
Vec2 Vec2::Lerp(const Vec2& value1, const Vec2& value2, float amount) {
	return Vec2(MathBox::Lerp(value1.x, value2.x, amount), MathBox::Lerp(value1.y, value2.y, amount));
}

// Static.
Vec2 Vec2::Negate(const Vec2& value) {
	return -value;
}

// Static.
Vec2 Vec2::Rotate(const Vec2& value, const float radians) {
	float c = cos(radians);
	float s = sin(radians);
	return Vec2(value.x * c - value.y * s, value.y * c + value.x * s);
}

// Overload some operators..
bool Vec2::operator==(const Vec2& v) const {
	return x == v.x && y == v.y;
}

bool Vec2::operator!=(const Vec2& v) const {
	return !(*this == v);
}

Vec2 Vec2::operator-(void) const {
	return Vec2::Zero - *this;
}

Vec2 Vec2::operator-(const Vec2& v) const {
	return Vec2(x - v.x, y - v.y);
}

Vec2 Vec2::operator+(const Vec2& v) const {
	return Vec2(x + v.x, y + v.y);
}

Vec2 Vec2::operator/(float divider) const {
	return Vec2(x / divider, y / divider);
}

Vec2 Vec2::operator*(float scaleFactor) const {
	return Vec2(x * scaleFactor, y * scaleFactor);
}

Vec2& Vec2::operator+=(const Vec2& v) {
	x += v.x, y += v.y;
	return *this;
}

Vec2& Vec2::operator-=(const Vec2& v) {
	x -= v.x, y -= v.y;
	return *this;
}

Vec2& Vec2::operator*=(float scaleFactor) {
	x *= scaleFactor, y *= scaleFactor;
	return *this;
}

Vec2& Vec2::operator/=(float scaleFactor) {
	x /= scaleFactor, y /= scaleFactor;
	return *this;
}
