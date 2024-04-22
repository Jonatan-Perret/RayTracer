#ifndef RAYTRACING__SPHERE_H_
#define RAYTRACING__SPHERE_H_

#include "Hittable.h"
#include "Vector3.h"
#include "Ray.h"

class Sphere : public Hittable {
 public:
  Vector3 center;
  double radius;
  Sphere() : center(Vector3()), radius(0) {}
  Sphere(const Vector3 &center, double radius) : center(center), radius(radius) {}
  bool hit(const Ray &ray, double tMin, double tMax, HitRecord &record) const override {
    Vector3 oc = ray.origin - center;
    auto a = ray.direction.lengtheSquared();
    auto half_b = dot(oc, ray.direction);
    auto c = oc.lengtheSquared() - radius * radius;

    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root <= tMin || tMax <= root) {
      root = (-half_b + sqrtd) / a;
      if (root <= tMin || tMax <= root)
        return false;
    }

    record.t = root;
    record.point = ray.at(record.t);
    Vector3 outwardNormal = (record.point - center) / radius;
    record.setFaceNormal(ray, outwardNormal);

    return true;
  }
};

#endif //RAYTRACING__SPHERE_H_
