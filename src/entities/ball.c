#include "entities/ball.h"
#include "components/collision.h"
#include "components/component.h"
#include "components/geometry.h"
#include "components/rigid_body.h"
#include "entities/world.h"
#include "utils/settings.h"

entity_t create_ball(world_t *world, float x, float y) {
  const entity_t entity = create_entity(world);

  world->mask[entity] = COMPONENT_GEOMETRY | COMPONENT_RIGID_BODY | COMPONENT_COLLISION;

  geometry_t *geometry = &(world->geometry[entity]);
  geometry->x = x;
  geometry->y = y;
  geometry->w = BALL_WIDTH;
  geometry->h = BALL_HEIGHT;

  rigid_body_t *rigid_body = &(world->rigid_body[entity]);
  rigid_body->vx = BALL_SPEED_INITIAL;
  rigid_body->vy = BALL_SPEED_INITIAL;

  collision_t *collision = &(world->collision[entity]);
  collision->category = COLLISION_BALL;
  collision->mask = COLLISION_PADDLE | COLLISION_WALL;

  return entity;
}
