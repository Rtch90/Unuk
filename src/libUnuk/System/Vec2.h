#pragma once
#include <vector>
#include <math.h>

#include "MathBox.h"

// A handy structure for passing around 2D integer coords.
struct Vec2i {
	int x, y;
	Vec2i(int xArg, int yArg) : x(xArg), y(yArg) {}
	Vec2i(void) : x(0), y(0) {}
};

struct Vec2 {
	// Initialize a zero-length vector (0, 0).
	Vec2(void);
	// Initialize a vector to a set dimension.
	Vec2(float xArg, float yArg);
	// Initialize a vector to a uniform dimension
	Vec2(float value);
	// Copy from the Vec2i to be converted into a Vec2
	Vec2(const Vec2i& copy);

	// A reference to a zero-length vector (0, 0)
	static Vec2 Zero;

	// A reference to a (1, 1) vector.
	static Vec2 One;

	// A reference to a (1, 0) vecor.
	static Vec2 UnitX;

	// A reference to a (0, 1) vector.
	static Vec2 UnitY;

	// Get the absolute magnitude of the vector. -- Uses a square root.
	float Length(void);

	// Get the squared magnitude of the vector -- Just in case we only care about comparison.
	float LengthSquared(void);

	// Get absolute distance between two points. -- Uses a square root.
	static float Distance(const Vec2& value1, const Vec2& value2);

	// In case we only care about comparison..
	static float DistanceSquared(const Vec2& value1, const Vec2& value2);

	// Get the dot product of two vectors.
	static float Dot(const Vec2& value1, const Vec2& value2);

	/* Get the cross product of two vectors. Note that the \b mathmatical
	 * definition of a cross product results in another vector oeroendicular
	 * to the two inputs, but since both of our vectors are 2D, the returned
	 * vector will always have x and y components of 0. This this function
	 * returns what would be the z component vector.
	 */
	static float Cross(const Vec2& value1, Vec2& value2);

	// Normalize a vector in place.
	void Normalize(void);

	// Get the normalized value for a Vec2 without affecting the original.
	static Vec2 Normalize(const Vec2& value);

	// Reflect the vector around another.
	static Vec2 Reflect(const Vec2& vector, const Vec2& normal);

	// Get a new vector from the minimum x and y.
	static Vec2 Min(const Vec2& value1, const Vec2& value2);

	// Get a new vector from the maximum x and y.
	static Vec2 Max(const Vec2& value1, const Vec2& value2);

	// Clamp a vector to a given min and max.
	static Vec2 Clamp(const Vec2& value, const Vec2& min, const Vec2& max);

	// Perform a linear interplolation between two vectors.
	static Vec2 Lerp(const Vec2& value1, const Vec2& value2, float amount);

	// Get a negated vector.
	static Vec2 Negate(const Vec2& value);

	static Vec2 Rotate(const Vec2& value, const float radians);

	bool operator==(const Vec2& v)		const;
	bool operator!=(const Vec2& v)		const;

	Vec2 operator-(void)							const;
	Vec2 operator-(const Vec2& v)			const;
	Vec2 operator+(const Vec2& v)			const;
	Vec2 operator/(float divider)			const;
	Vec2 operator*(float scaleFactor) const;

	Vec2& operator+=(const Vec2& v);
	Vec2& operator-=(const Vec2& v);
	Vec2& operator*=(float f);
	Vec2& operator/=(float f);

	float x;
	float y;
};

typedef std::vector<Vec2> Vector2List;
