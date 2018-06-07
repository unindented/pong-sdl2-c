#include "components/collision.h"
#include "components/component.h"
#include "components/controller.h"
#include "components/geometry.h"
#include "entities/paddle.h"
#include "entities/world.h"
#include "utils/settings.h"

entity_t create_wall(world_t *world, float x, float y) {
  const entity_t entity = create_entity(world);

  world->mask[entity] = COMPONENT_GEOMETRY | COMPONENT_COLLISION;

  geometry_t *geometry = &(world->geometry[entity]);
  geometry->x = x;
  geometry->y = y;
  geometry->w = WALL_WIDTH;
  geometry->h = WALL_HEIGHT;

  collision_t *collision = &(world->collision[entity]);
  collision->category = COLLISION_WALL;
  collision->mask = COLLISION_BALL | COLLISION_PADDLE;

  return entity;
}
