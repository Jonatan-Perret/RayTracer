#ifndef RAYTRACING__CAMERA_H_
#define RAYTRACING__CAMERA_H_

#include "Vector3.h"

class Camera {
 public:
  Vector3 position, viewDirection;
  Camera() : position(Vector3()), viewDirection(Vector3()) {}

};
#endif //RAYTRACING__CAMERA_H_
