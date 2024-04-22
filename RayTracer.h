#ifndef RAYTRACING__RAYTRACER_H_
#define RAYTRACING__RAYTRACER_H_

#include "Vector3.h"
#include "Ray.h"
#include "Camera.h"
#include "Sphere.h"
#include "Cube.h"

// Light.h
class Light {
 public:
  Vector3 position;
  Light() : position(Vector3()) {}
};

// RayTracer.h
#include <vector>
#include <SDL.h>
class RayTracer {
 private:
  std::vector<Sphere> spheres;
  std::vector<Cube> cubes;
  std::vector<Light> lights;
  Camera camera;
  unsigned maxDepth = 1;

  // rendering
  SDL_Texture *texture;
 public:
  RayTracer();
  void addSphere(const Sphere &sphere);
  void addCube(const Cube &cube);
  void addLight(const Light &light);
  void setCamera(const Camera &camera);
  Vector3 trace(const Ray &ray, const Hittable &world, int depth);
  // render method return an array of pixels
  void render(SDL_Texture *texture, size_t SCREEN_HEIGHT, size_t SCREEN_WIDTH, Uint32 pitch, void *pixels);
  bool is_in_shadow(const Vector3 &point, const Hittable &world);

  // movement
  void move_forward();
  void move_backward();
  void move_left();
  void move_right();
  void rotate_left();
  void rotate_right();

  void setMaxDepth(unsigned maxDepth);

};

#endif //RAYTRACING__RAYTRACER_H_
