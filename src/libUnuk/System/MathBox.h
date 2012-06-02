#pragma once
#include "Vec2.h"

class MathBox {
public:
  // A templated max function that returns none other than the max of two values.
  template<typename T>
  static T Max(T value1, T value2) {
    return value1 > value2 ? value1 : value2;
  }

  // A templated min function that returns none other than the min of two values.
  template<typename T>
  static T Min(T value1, T value2) {
    return value1 < value2 ? value1 : value2;
  }

  // Linear interpolation between two values.
  template<typename T>
  static T Lerp(T value1, T value2, float amount) {
    return T(value1 + ((T)(value2 - value1) * amount));
  }

  // Clamp an integer to a specified range.
  static int Clamp(int value, int min, int max) {
    return Max(min, Min(max, value));
  }

  // Clamp a float to a specified range.
  static float Clamp(float value, float min, float max) {
    return Max(min, Min(max, value));
  }

  // Clamp a double-precision to a specified range.
  static double Clamp(double value, double min, double max) {
    return Max(min, Min(max, value));
  }
};
