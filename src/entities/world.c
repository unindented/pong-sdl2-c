#include <stdio.h>

#include "SDL.h"

#include "components/component.h"
#include "entities/world.h"

entity_t create_entity(world_t *world) {
  for (entity_t entity = 1; entity < MAX_ENTITIES; ++entity) {
    if (world->mask[entity] == COMPONENT_NONE) {
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Entity created: %d\n", entity);
      return entity;
    }
  }

  SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "No more entities left!\n");
  return 0;
}

void destroy_entity(world_t *world, entity_t entity) {
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Entity destroyed: %d\n", entity);
  world->mask[entity] = COMPONENT_NONE;
}
