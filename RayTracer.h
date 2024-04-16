#ifndef RAYTRACING__RAYTRACER_H_
#define RAYTRACING__RAYTRACER_H_

#include "Vector3.h"
#include "Ray.h"
#include "Camera.h"
#include "Sphere.h"

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
  std::vector<Light> lights;
  Camera camera;

  // rendering
  SDL_Texture *texture;
 public:
  RayTracer();
  void addSphere(const Sphere &sphere);
  void addLight(const Light &light);
  void setCamera(const Camera &camera);
  Vector3 trace(const Ray &ray, const Hittable& world, int depth);
  // render method return an array of pixels
  void render(SDL_Texture *texture, size_t SCREEN_HEIGHT, size_t SCREEN_WIDTH, Uint32 pitch, void *pixels);

    // movement
    void move_forward();
    void move_backward();
    void move_left();
    void move_right();
};

#endif //RAYTRACING__RAYTRACER_H_
