#include "entities/paddle.h"
#include "components/collision.h"
#include "components/component.h"
#include "components/controller.h"
#include "components/geometry.h"
#include "entities/world.h"
#include "utils/settings.h"

entity_t create_paddle(world_t *world, float x, float y) {
  const entity_t entity = create_entity(world);

  world->mask[entity] = COMPONENT_GEOMETRY | COMPONENT_CONTROLLER | COMPONENT_COLLISION;

  geometry_t *geometry = &(world->geometry[entity]);
  geometry->x = x;
  geometry->y = y;
  geometry->w = PADDLE_WIDTH;
  geometry->h = PADDLE_HEIGHT;

  collision_t *collision = &(world->collision[entity]);
  collision->category = COLLISION_PADDLE;
  collision->mask = COLLISION_BALL | COLLISION_WALL;

  return entity;
}
