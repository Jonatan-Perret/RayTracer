#include <thread>
#include "RayTracer.h"
#include "HittableList.h"

#include <iostream>
#include <string>

// utils


// RayTracer methods
RayTracer::RayTracer() {
  // Initialize with default camera and empty lists for spheres and lights
  camera = Camera();
  spheres = std::vector<Sphere>();
  cubes = std::vector<Cube>();
  lights = std::vector<Light>();

}

void RayTracer::addSphere(const Sphere &sphere) {
  spheres.push_back(sphere);
}

void RayTracer::addCube(const Cube &cube) {
  cubes.push_back(cube);
}

void RayTracer::addLight(const Light &light) {
  lights.push_back(light);
}

void RayTracer::setCamera(const Camera &camera) {
  this->camera = camera;
}

Vector3 RayTracer::trace(const Ray &ray, const Hittable &world, int depth) {
  if (depth <= 0) {
    return Vector3(0, 0, 0); // Return black when max depth is reached
  }

  HitRecord record;
  if (world.hit(ray, 0.001, INFINITY, record)) {
    // check if the point is in shadow
    if (is_in_shadow(record.point, world)) {
      return Vector3(0, 0, 0);
    }
    Vector3 target = record.point + record.normal
        + Vector3::randomUnitVector(); // random_unit_vector() should be defined to give diffuse
    Ray new_ray(record.point, target - record.point);
    return 0.5 * trace(new_ray, world, depth - 1); // Recurse with reduced depth
  }
  Vector3 unit_direction = unit_vector(ray.direction);
  auto t = 0.5 * (unit_direction.y + 1.0);
  return Vector3(1.0, 1.0, 1.0) * (1.0 - t) + Vector3(0.5, 0.7, 1.0) * t; // Background gradient
}

void RayTracer::render(SDL_Texture *texture, size_t SCREEN_HEIGHT, size_t SCREEN_WIDTH, Uint32 pitch, void *pixels) {
  Uint32 *upixels = (Uint32 *) pixels;

  // World
  HittableList world;
  world.add(make_shared<Sphere>(Vector3(0, 0, -1), 0.5));
  world.add(make_shared<Sphere>(Vector3(0, -100.5, -1), 100));
  //world.add(make_shared<Light>(Vector3(2, 2, 2)));

  // add a light
  Light light;
  light.position = Vector3(2, 2, 2);
  // empty the lights list
  lights.clear();
  lights.push_back(light);

  auto aspect_ratio = static_cast<double>(SCREEN_WIDTH) / SCREEN_HEIGHT;

  // Camera
  auto focal_length = 1.0;
  auto viewport_height = 2.0;
  auto viewport_width = viewport_height * aspect_ratio;
  auto camera_center = camera.position;

  // Calculate the vectors across the horizontal and down the vertical viewport edges
  auto viewport_u = Vector3(viewport_width, 0, 0);
  auto viewport_v = Vector3(0, -viewport_height, 0);

  // Calculate the horizontal and vertical delta vectors from pixel to pixel
  auto pixel_delta_u = viewport_u / SCREEN_WIDTH;
  auto pixel_delta_v = viewport_v / SCREEN_HEIGHT;

  // Calculate the location of the upper left pixel
  auto viewport_upper_left = camera_center - Vector3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
  auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

  // Multithreading setup
  const size_t num_threads = std::thread::hardware_concurrency();
  std::vector<std::thread> threads;
  threads.reserve(num_threads);

  // Lambda function for rendering parts of the screen
  auto render_segment = [&](int start_y, int end_y) {
    for (int y = start_y; y < end_y; ++y) {
      for (int x = 0; x < SCREEN_WIDTH; ++x) {
        auto pixel_center = pixel00_loc + (x * pixel_delta_u) + (y * pixel_delta_v);
        //auto ray_direction = pixel_center - camera_center;
        // ray direction with camera rotation
        auto ray_direction = (pixel_center - camera_center).rotate(camera.yaw, camera.up);
        Ray ray(camera_center, ray_direction);
        Vector3 color = trace(ray, world, this->maxDepth);

        Uint8 red = static_cast<Uint8>(color.x * 255);
        Uint8 green = static_cast<Uint8>(color.y * 255);
        Uint8 blue = static_cast<Uint8>(color.z * 255);
        upixels[y * (pitch / 4) + x] = (0xFF << 24) | (red << 16) | (green << 8) | blue;
      }
    }
  };

  // Divide the screen into segments and assign each to a thread
  int segment_height = SCREEN_HEIGHT / num_threads;
  for (int i = 0; i < num_threads; ++i) {
    int start_y = i * segment_height;
    int end_y = (i + 1) * segment_height;
    if (i == num_threads - 1) end_y = SCREEN_HEIGHT; // Ensure the last thread covers all remaining lines
    threads.emplace_back(render_segment, start_y, end_y);
  }

  // Join all threads
  for (auto &thread : threads) {
    thread.join();
  }

  // Set the texture
  SDL_UpdateTexture(texture, nullptr, pixels, pitch);
}

// movement
void RayTracer::move_forward() {
  // camera position with camera rotation
  camera.position -= camera.front * camera.speed;

  // move the world instead of the camera
  /*for (auto &sphere : spheres) {
    sphere.center += camera.front * camera.speed;
  }*/
}

void RayTracer::move_backward() {
  camera.position += camera.front * camera.speed;
  // move the world instead of the camera
  /*for (auto &sphere : spheres) {
    sphere.center -= camera.front * camera.speed;
  }*/
}

void RayTracer::move_left() {
  camera.position -= camera.right * camera.speed;
  // move the world instead of the camera
  /*for (auto &sphere : spheres) {
    sphere.center += camera.right * camera.speed;
  }*/
}

void RayTracer::move_right() {
  camera.position += camera.right * camera.speed;
  // move the world instead of the camera
  /*for (auto &sphere : spheres) {
    sphere.center -= camera.right * camera.speed;
  }*/
}

void RayTracer::rotate_left() {
  camera.yaw += camera.rotationSpeed;
  camera.updateVectors();
}

void RayTracer::rotate_right() {
  camera.yaw -= camera.rotationSpeed;
  camera.updateVectors();
}

bool RayTracer::is_in_shadow(const Vector3 &point, const Hittable &world) {

  for (const auto &light : lights) {
    Vector3 light_direction = (light.position - point).normalized();
    Ray shadow_ray(point, light_direction);
    HitRecord record;
    if (world.hit(shadow_ray, 0.001, INFINITY, record)) {
      return true;
    }
  }
  return false;
}

void RayTracer::setMaxDepth(unsigned maxDepth) {
  this->maxDepth = maxDepth;
}