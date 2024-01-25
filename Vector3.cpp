
#include "Vector3.h"

Vector3 Vector3::operator+(const Vector3 &v) const {
  return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator-(const Vector3 &v) const {
  return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator-(const int v) const {
  return Vector3(x - v, y - v, z - v);
}

Vector3 Vector3::operator*(double scalar) const {
  return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3 Vector3::operator/(double scalar) const {
  return Vector3(x / scalar, y / scalar, z / scalar);
}

Vector3 Vector3::operator+=(const Vector3 &v) {
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}

Vector3 Vector3::operator-=(const Vector3 &v) {
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return *this;
}

Vector3 Vector3::operator*=(double scalar) {
  x *= scalar;
  y *= scalar;
  z *= scalar;
  return *this;
}

Vector3 Vector3::operator/=(double scalar) {
  x /= scalar;
  y /= scalar;
  z /= scalar;
  return *this;
}

bool Vector3::operator==(const Vector3 &v) const {
  return x == v.x && y == v.y && z == v.z;
}

bool Vector3::operator!=(const Vector3 &v) const {
  return x != v.x || y != v.y || z != v.z;
}



Vector3 Vector3::cross(const Vector3 &v) const {
  return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

double Vector3::length() const {
  return std::sqrt(x * x + y * y + z * z);
}

double Vector3::lengtheSquared() const {
  return x * x + y * y + z * z;
}

Vector3 &Vector3::normalizeThis() {
  double length = this->length();
  if (length > 0.0f) {
    double invLength = 1.0f / length;
    x *= invLength;
    y *= invLength;
    z *= invLength;
  }
  return *this;
}

Vector3 Vector3::normalized() const {
  double length = this->length();
  if (length > 0.0f) {
    double invLength = 1.0f / length;
    return Vector3(x * invLength, y * invLength, z * invLength);
  }
  return *this;
}