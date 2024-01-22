#ifndef RAYTRACING__RAYTRACER_H_
#define RAYTRACING__RAYTRACER_H_

// Vector3.h
class Vector3 {
 public:
  float x, y, z;
  Vector3() : x(0), y(0), z(0) {}
  Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
};

// Ray.h
class Ray {
 public:
  Vector3 origin, direction;
  Ray() : origin(Vector3()), direction(Vector3()) {}
};

// Sphere.h
class Sphere {
 public:
  Vector3 center;
  float radius;
  Sphere() : center(Vector3()), radius(0) {}
};

// Light.h
class Light {
 public:
  Vector3 position;
  Light() : position(Vector3()) {}
};

// Camera.h
class Camera {
 public:
  Vector3 position, viewDirection;
  Camera() : position(Vector3()), viewDirection(Vector3()) {}

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
  Vector3 trace(const Ray &ray, int depth);
  // render method return an array of pixels
  void render(SDL_Texture *texture, size_t SCREEN_HEIGHT, size_t SCREEN_WIDTH, Uint32 pitch, void *pixels);
};

#endif //RAYTRACING__RAYTRACER_H_
