#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "SDL.h"

#include "config.h"
#include "entities/ball.h"
#include "entities/paddle.h"
#include "entities/wall.h"
#include "entities/world.h"
#include "systems/keyboard.h"
#include "systems/physics.h"
#include "systems/rendering.h"
#include "utils/math.h"
#include "utils/settings.h"

static world_t world;
static entity_t ball;
static entity_t paddle_left;
static entity_t paddle_right;
static entity_t wall_top;
static entity_t wall_bottom;

static bool setup_sdl();
static void teardown_sdl();
static bool create_entities();
static void game_loop();

int main(int argc, char *argv[]) {
  atexit(teardown_sdl);

  if (!setup_sdl() || !create_entities()) {
    return EXIT_FAILURE;
  }

  game_loop();

  return EXIT_SUCCESS;
}

bool setup_sdl() {
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Setting up SDL...\n");

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to initialize SDL:  %s\n", SDL_GetError());
    return false;
  }

  char title[32];
  snprintf(title, sizeof title, "%s v%s", PROJECT_NAME, PROJECT_VERSION);

  world.window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT,
                                  SDL_WINDOW_ALLOW_HIGHDPI);
  if (world.window == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create window: %s\n", SDL_GetError());
    return false;
  }

  world.renderer = SDL_CreateRenderer(world.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (world.renderer == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create renderer: %s\n", SDL_GetError());
    return false;
  }

  if (SDL_RenderSetScale(world.renderer, WINDOW_SCALE, WINDOW_SCALE) != 0) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to set scale: %s\n", SDL_GetError());
    return false;
  }

  return true;
}

void teardown_sdl() {
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Tearing down SDL...\n");

  if (world.renderer != NULL) {
    SDL_DestroyRenderer(world.renderer);
    world.renderer = NULL;
  }

  if (world.window != NULL) {
    SDL_DestroyWindow(world.window);
    world.window = NULL;
  }

  SDL_Quit();
}

bool create_entities() {
  ball = create_ball(&world, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
  paddle_left = create_paddle(&world, PADDLE_WIDTH, WINDOW_HEIGHT / 2);
  paddle_right = create_paddle(&world, WINDOW_WIDTH - PADDLE_WIDTH, WINDOW_HEIGHT / 2);
  wall_top = create_wall(&world, WINDOW_WIDTH / 2, WINDOW_HEIGHT - WALL_HEIGHT / 2);
  wall_bottom = create_wall(&world, WINDOW_WIDTH / 2, WALL_HEIGHT / 2);

  return ball && paddle_left && paddle_right && wall_top && wall_bottom;
}

void game_loop() {
  const float maxFrameTime = 1 / 60.0f;
  float currentTime = SDL_GetTicks() / 1000.0f;

  bool quit = false;
  SDL_Event e;

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }

    SDL_SetRenderDrawColor(world.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(world.renderer);

    const float newTime = SDL_GetTicks() / 1000.0f;
    float frameTime = newTime - currentTime;
    currentTime = newTime;

    while (frameTime > 0) {
      const float deltaTime = min(frameTime, maxFrameTime);
      frameTime -= deltaTime;

      update_keyboard(&world, deltaTime);
      update_physics(&world, deltaTime);
    }

    update_rendering(&world);

    SDL_RenderPresent(world.renderer);
  }
}
