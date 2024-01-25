#ifndef RAYTRACING__HITTABLELIST_H_
#define RAYTRACING__HITTABLELIST_H_

#include "Hittable.h"
#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class HittableList : public Hittable {
 public:
  std::vector<shared_ptr<Hittable>> objects;

  HittableList() {}
  HittableList(shared_ptr<Hittable> object) { add(object); }

  void clear() { objects.clear(); }
  void add(shared_ptr<Hittable> object) { objects.push_back(object); }

  virtual bool hit(const Ray &ray, double tMin, double tMax, HitRecord &record) const override{
    HitRecord temp_rec;
    bool hit_anything = false;
    auto closest_so_far = tMax;

    for (const auto& object : objects) {
      if (object->hit(ray, tMin, closest_so_far, temp_rec)) {
        hit_anything = true;
        closest_so_far = temp_rec.t;
        record = temp_rec;
      }
    }

    return hit_anything;
  }
};

#endif //RAYTRACING__HITTABLELIST_H_
