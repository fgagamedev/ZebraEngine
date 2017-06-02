#ifndef __MATH__
#define __MATH__

#include <math.h>

#include "Math/Vector.h"

class Math {
public:
  static float Distance(float x0, float y0, float x1, float y1);
  static float Distance(Vector &a, Vector &b);
  static float Min(float a, float b) { return a > b ? b : a; };
  static float Max(float a, float b) { return a > b ? a : b; };
  static bool RangeIntersect(float min0, float max0, float min1, float max1);
};

#endif
