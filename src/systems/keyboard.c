#include "systems/keyboard.h"
#include "components/controller.h"
#include "components/geometry.h"
#include "entities/world.h"
#include "utils/settings.h"

#include "SDL.h"

void update_keyboard(world_t *world, float dt) {
  const uint8_t *keyboard_state = SDL_GetKeyboardState(NULL);

  entity_t entity;
  geometry_t *geometry;

  for (entity = 0; entity < MAX_ENTITIES; ++entity) {
    if ((world->mask[entity] & KEYBOARD_MASK) == KEYBOARD_MASK) {
      geometry = &(world->geometry[entity]);

      if (keyboard_state[SDL_SCANCODE_UP]) {
        geometry->y -= KEYBOARD_SPEED * dt;
      }
      if (keyboard_state[SDL_SCANCODE_DOWN]) {
        geometry->y += KEYBOARD_SPEED * dt;
      }
    }
  }
}
