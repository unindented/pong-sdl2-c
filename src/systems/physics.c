#include "systems/physics.h"
#include "components/geometry.h"
#include "components/rigid_body.h"
#include "entities/world.h"

void update_physics(world_t *world, float dt) {
  entity_t entity;
  geometry_t *geometry;
  rigid_body_t *rigid_body;

  for (entity = 0; entity < MAX_ENTITIES; ++entity) {
    if ((world->mask[entity] & PHYSICS_MASK) == PHYSICS_MASK) {
      geometry = &(world->geometry[entity]);
      rigid_body = &(world->rigid_body[entity]);

      geometry->x += rigid_body->vx * dt;
      geometry->y += rigid_body->vy * dt;
    }
  }
}
