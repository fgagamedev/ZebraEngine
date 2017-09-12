#ifndef __VECTOR__
#define __VECTOR__

#include <math.h>

class Vector {
public:
  // x and y position
  float m_x, m_y,m_w,m_h;
  // constructor
  Vector() : m_x(0), m_y(0),m_w(0),m_h(0){};
  Vector(float x, float y) : m_x(x), m_y(y){};
  Vector(float x, float y,float w,float h) : m_x(x), m_y(y),m_w(w),m_h(h){};
  // operator overloads
  Vector operator+(const Vector &vec);
  Vector operator+=(const Vector &vec);
  Vector operator-(const Vector &vec);
  Vector operator-=(const Vector &vec);
  Vector operator*(float scalar);
  Vector operator/(float scalar);
  // vector maths
  float GetDistance(Vector vec);
  float GetLength();
  float GetLength(Vector &vec);
  float GetAngleDegrees(Vector &vec);
  float GetAngleRadians(Vector &vec);
  Vector GetNormalized();
};

#endif // __VECTOR__
