#ifndef RAYTRACING__VECTOR3_H_
#define RAYTRACING__VECTOR3_H_

#include <cmath>

class Vector3 {
 public:
  double x, y, z;
  Vector3() : x(0), y(0), z(0) {}
  Vector3(double x, double y, double z) : x(x), y(y), z(z) {}
  Vector3 operator+(const Vector3 &v) const;
  Vector3 operator-(const Vector3 &v) const;
  Vector3 operator-(const int v) const;
  Vector3 operator*(double scalar) const;
  Vector3 operator/(double scalar) const;
  Vector3 operator+=(const Vector3 &v);
  Vector3 operator-=(const Vector3 &v);
  Vector3 operator*=(double scalar);
  Vector3 operator/=(double scalar);
  bool operator==(const Vector3 &v) const;
  bool operator!=(const Vector3 &v) const;
  Vector3 cross(const Vector3 &v) const;
  double length() const;
  double lengtheSquared() const;
  Vector3 &normalizeThis();
  Vector3 normalized() const;
};

inline Vector3 unit_vector(Vector3 v) {
  return v / v.length();
}

inline Vector3 operator*(double t, const Vector3 &v) {
  return Vector3(t * v.x, t * v.y, t * v.z);
}

// dot product
inline double dot(const Vector3 &v1, const Vector3 &v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

#endif //RAYTRACING__VECTOR3_H_
