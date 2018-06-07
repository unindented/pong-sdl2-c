#include "systems/rendering.h"
#include "components/geometry.h"
#include "entities/world.h"

#include "SDL.h"

void update_rendering(world_t *world) {
  entity_t entity;
  geometry_t *geometry;

  for (entity = 0; entity < MAX_ENTITIES; ++entity) {
    if ((world->mask[entity] & RENDERING_MASK) == RENDERING_MASK) {
      geometry = &(world->geometry[entity]);

      SDL_Rect rect;
      rect.x = geometry->x - (geometry->w / 2.0f);
      rect.y = geometry->y - (geometry->h / 2.0f);
      rect.w = geometry->w;
      rect.h = geometry->h;

      SDL_SetRenderDrawColor(world->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
      SDL_RenderFillRect(world->renderer, &rect);
    }
  }
}
