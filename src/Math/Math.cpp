#include "Math/Math.h"

float Math::Distance(float x0, float y0, float x1, float y1) {
  return sqrt(pow(x0 - x1, 2) + pow(y1 - y0, 2));
}

float Math::Distance(Vector &a, Vector &b) {
  return sqrt(pow(a.m_x - b.m_x, 2) + pow(a.m_y - b.m_y, 2));
}

bool RangeIntersect(float min0, float max0, float min1, float max1) {
  return max0 >= min1 && min0 <= max1;
}
