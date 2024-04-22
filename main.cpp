#include <SDL.h>
#include <iostream>

#include "RayTracer.h"

// constants
const size_t SCREEN_WIDTH = 400;
const size_t SCREEN_HEIGHT = 300;

void handle_wasd_keys(RayTracer &engine) {
  const Uint8 *keystate = SDL_GetKeyboardState(nullptr);
  if (keystate[SDL_SCANCODE_W]) {
    engine.move_forward();
  }
  if (keystate[SDL_SCANCODE_S]) {
    engine.move_backward();
  }
  if (keystate[SDL_SCANCODE_A]) {
    engine.move_left();
  }
  if (keystate[SDL_SCANCODE_D]) {
    engine.move_right();
  }
}

void handle_qe_keys(RayTracer &engine) {
  const Uint8 *keystate = SDL_GetKeyboardState(nullptr);
  if (keystate[SDL_SCANCODE_Q]) {
    engine.rotate_left();
  }
  if (keystate[SDL_SCANCODE_E]) {
    engine.rotate_right();
  }
}

int main() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    return EXIT_FAILURE;
  }

  // Create Window
  SDL_Window *window = SDL_CreateWindow(
      "SDL2 RayTracer",       // window title
      SDL_WINDOWPOS_UNDEFINED,// initial x position
      SDL_WINDOWPOS_UNDEFINED,// initial y position
      SCREEN_WIDTH,           // width, in pixels
      SCREEN_HEIGHT,          // height, in pixels
      SDL_WINDOW_SHOWN        // flags
  );

  if (window == nullptr) {
    std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return EXIT_FAILURE;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  // Create a texture we can draw to
  SDL_Texture *texture = SDL_CreateTexture(renderer,
                                           SDL_PIXELFORMAT_ARGB8888,
                                           SDL_TEXTUREACCESS_STREAMING,
                                           SCREEN_WIDTH, SCREEN_HEIGHT);


  // create a raytracing engine
  RayTracer engine;

  bool running = true;
  SDL_Event event;

  // running loop
  while (running) {
    while (SDL_PollEvent(&event)) {
      // switch to handle events
      switch (event.type) {
        case SDL_QUIT:running = false;
          break;
        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:running = false;
              break;
            default:break;
          }
          break;
        default:break;
      }
      handle_wasd_keys(engine);
      handle_qe_keys(engine);
    }


    // timer for rendering time
    Uint32 start_time = SDL_GetTicks();

    // Prepare to update texture
    void *pixels;
    int pitch;
    SDL_LockTexture(texture, nullptr, &pixels, &pitch);

    engine.render(texture, SCREEN_HEIGHT, SCREEN_WIDTH, pitch, pixels);

    Uint32 end_time = SDL_GetTicks();
    Uint32 render_time = end_time - start_time;

    // fps
    Uint32 fps = 1000 / render_time;
    // clear the console
    system("clear");
    std::cout << "FPS: " << fps << std::endl;

    // Unlock the texture
    SDL_UnlockTexture(texture);

    // Copy the texture to the renderer
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);

    // Update screen
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS;
}
