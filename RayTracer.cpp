#include "RayTracer.h"

// RayTracer methods
RayTracer::RayTracer() {
  // Initialize with default camera and empty lists for spheres and lights
  camera = Camera();
  spheres = std::vector<Sphere>();
  lights = std::vector<Light>();

}

void RayTracer::addSphere(const Sphere &sphere) {
  spheres.push_back(sphere);
}

void RayTracer::addLight(const Light &light) {
  lights.push_back(light);
}

void RayTracer::setCamera(const Camera &camera) {
  this->camera = camera;
}

Vector3 RayTracer::trace(const Ray &ray, int depth) {
  Vector3 color;
  // Implement ray tracing logic


  return color;
}

void RayTracer::render(SDL_Texture *texture, size_t SCREEN_HEIGHT, size_t SCREEN_WIDTH, Uint32 pitch, void *pixels) {
  // Implement rendering logic
  Uint32 *upixels = (Uint32 *) pixels;

  // loop over every pixel
  for (int y = 0; y < SCREEN_HEIGHT; ++y) {
    for (int x = 0; x < SCREEN_WIDTH; ++x) {
      // for each pixel, cast a ray from the camera to the pixel
      

      // trace the ray to determine the color
      // set the pixel color

      Uint8 red = std::rand() % 256;
      Uint8 green = std::rand() % 256;
      Uint8 blue = std::rand() % 256;
      upixels[y * (pitch / 4) + x] = (0xFF << 24) | (red << 16) | (green << 8) | blue;
    }
  }


  // set the texture
  SDL_UpdateTexture(texture, NULL, pixels, pitch);
}