#ifndef RAYTRACING__HITTABLE_H_
#define RAYTRACING__HITTABLE_H_

#include "Vector3.h"
#include "Ray.h"

class HitRecord {
 public:
  Vector3 point, normal;
  double t;
  bool frontFace;
  Vector3 color;

  HitRecord() : point(Vector3()), normal(Vector3()), t(0) {}
  HitRecord(const Vector3 &point, const Vector3 &normal, double t, bool frontFace)
      : point(point), normal(normal), t(t) {}
  void setFaceNormal(const Ray &ray, const Vector3 &outwardNormal) {
    frontFace = dot(ray.direction, outwardNormal) < 0;
    normal = frontFace ? outwardNormal : (-1) * outwardNormal;
  }
};

class Hittable {
 public:
  virtual bool hit(const Ray &ray, double tMin, double tMax, HitRecord &record) const = 0;
};

#endif //RAYTRACING__HITTABLE_H_
