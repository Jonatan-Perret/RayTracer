#ifndef RAYTRACING__CUBE_H_
#define RAYTRACING__CUBE_H_

#include "Vector3.h"
#include "Ray.h"
#include "Hittable.h"
#include <algorithm>

class Cube : public Hittable {
 public:
  Vector3 center;
  double side;
  Cube(const Vector3 &center, double side) : center(center), side(side) {}

  bool hit(const Ray &ray, double tMin, double tMax, HitRecord &record) const override {
    auto half_side = side / 2;
    auto half_side_vector = Vector3(half_side, half_side, half_side);
    auto min = center - half_side_vector;
    auto max = center + half_side_vector;

    double t1 = (min.x - ray.origin.x) / ray.direction.x;
    double t2 = (max.x - ray.origin.x) / ray.direction.x;

    double tmin = std::min(t1, t2);
    double tmax = std::max(t1, t2);

    for (int i = 1; i < 3; i++) {
      t1 = (min[i] - ray.origin[i]) / ray.direction[i];
      t2 = (max[i] - ray.origin[i]) / ray.direction[i];

      tmin = std::max(tmin, std::min(t1, t2));
      tmax = std::min(tmax, std::max(t1, t2));
    }

    if (tmax < tmin) {
      return false;
    }

    double t = tmin < 0 ? tmax : tmin;
    record.t = t;
    record.point = ray.at(t);
    record.setFaceNormal(ray, Vector3(0, 0, 0));
    return true;
  }
};

#endif //RAYTRACING__CUBE_H_
