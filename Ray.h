#ifndef RAYTRACING__RAY_H_
#define RAYTRACING__RAY_H_

#include "Vector3.h"

class Ray {
 public:
  Vector3 origin, direction;
  Vector3 color = Vector3();
  Ray() : origin(Vector3()), direction(Vector3()) {}
  Ray(const Vector3 &origin, const Vector3 &direction) : origin(origin), direction(direction) {}
  Vector3 at (double t) const {
    return origin + direction * t;
  }
};

#endif //RAYTRACING__RAY_H_
