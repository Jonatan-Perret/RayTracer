
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

double &Vector3::operator[](int i) {
  if (i == 0) return x;
  if (i == 1) return y;
  return z;
}

const double &Vector3::operator[](int i) const {
  if (i == 0) return x;
  if (i == 1) return y;
  return z;
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

Vector3 &Vector3::normalize() {
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

Vector3 Vector3::rotate(double angle, const Vector3 &axis) {
  double s = std::sin(angle);
  double c = std::cos(angle);
  double oc = 1.0 - c;
  double x = this->x;
  double y = this->y;
  double z = this->z;
  double ax = axis.x;
  double ay = axis.y;
  double az = axis.z;
  return Vector3(
      (c + oc * ax * ax) * x + (oc * ax * ay - az * s) * y + (oc * ax * az + ay * s) * z,
      (oc * ax * ay + az * s) * x + (c + oc * ay * ay) * y + (oc * ay * az - ax * s) * z,
      (oc * ax * az - ay * s) * x + (oc * ay * az + ax * s) * y + (c + oc * az * az) * z
  );
}