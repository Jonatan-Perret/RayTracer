#ifndef RAYTRACING__CAMERA_H_
#define RAYTRACING__CAMERA_H_

#include "Vector3.h"

class Camera {
 public:
  Vector3 position, viewDirection;
  Vector3 up = Vector3(0, 1, 0);
  Vector3 right = Vector3(1, 0, 0);
  Vector3 front = Vector3(0, 0, 1);

    double speed = 0.1;
  Camera() : position(Vector3()), viewDirection(Vector3()) {}

};
#endif //RAYTRACING__CAMERA_H_
