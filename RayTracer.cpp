#include "RayTracer.h"
#include "HittableList.h"

// utils


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

Vector3 RayTracer::trace(const Ray &ray, const Hittable &world, int depth) {
  HitRecord record;
  if (world.hit(ray, 0, INFINITY, record)) {
    return 0.5 * (record.normal + Vector3(1, 1, 1));
  }
  Vector3 unit_direction = unit_vector(ray.direction);
  auto a = 0.5 * (unit_direction.y + 1.0);
  return Vector3(1.0, 1.0, 1.0) * (1.0 - a) + Vector3(0.5, 0.7, 1.0) * a;
}

void RayTracer::render(SDL_Texture *texture, size_t SCREEN_HEIGHT, size_t SCREEN_WIDTH, Uint32 pitch, void *pixels) {
  // Implement rendering logic
  Uint32 *upixels = (Uint32 *) pixels;

  // World
  HittableList world;
  world.add(make_shared<Sphere>(Vector3(0, 0, -1), 0.5));
  world.add(make_shared<Sphere>(Vector3(0, -100.5, -1), 100));

  auto aspect_ratio = SCREEN_WIDTH / SCREEN_HEIGHT;

  // Camera

  auto focal_length = 1.0;
  auto viewport_height = 2.0;
  auto viewport_width = viewport_height * (static_cast<double>(SCREEN_WIDTH) / SCREEN_HEIGHT);
  auto camera_center = camera.position;

  // Calculate the vectors across the horizontal and down the vertical viewport edges.
  auto viewport_u = Vector3(viewport_width, 0, 0);
  auto viewport_v = Vector3(0, -viewport_height, 0);

  // Calculate the horizontal and vertical delta vectors from pixel to pixel.
  auto pixel_delta_u = viewport_u / SCREEN_WIDTH;
  auto pixel_delta_v = viewport_v / SCREEN_HEIGHT;

  // Calculate the location of the upper left pixel.
  auto viewport_upper_left = camera_center
      - Vector3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
  auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

  // loop over every pixel
  for (int y = 0; y < SCREEN_HEIGHT; ++y) {
    for (int x = 0; x < SCREEN_WIDTH; ++x) {

      auto pixel_center = pixel00_loc + (x * pixel_delta_u) + (y * pixel_delta_v);
      auto ray_direction = pixel_center - camera_center;
      Ray ray = Ray(camera_center, ray_direction);
      Vector3 color = trace(ray, world, 0);

      Uint8 red = color.x * 255;
      Uint8 green = color.y * 255;
      Uint8 blue = color.z * 255;
      upixels[y * (pitch / 4) + x] = (0xFF << 24) | (red << 16) | (green << 8) | blue;
    }
  }


  // set the texture
  SDL_UpdateTexture(texture, nullptr, pixels, pitch);
}

// movement
void RayTracer::move_forward() {
  camera.position -= camera.front * camera.speed;
}

void RayTracer::move_backward() {
  camera.position += camera.front * camera.speed;
}

void RayTracer::move_left() {
  camera.position -= camera.right * camera.speed;
}

void RayTracer::move_right() {
  camera.position += camera.right * camera.speed;
}