#pragma once

#include "components/collision.h"
#include "components/controller.h"
#include "components/geometry.h"
#include "components/rigid_body.h"
#include "utils/settings.h"

typedef unsigned int entity_t;

typedef struct {
  void *window;
  void *renderer;

  unsigned int mask[MAX_ENTITIES];

  geometry_t geometry[MAX_ENTITIES];
  rigid_body_t rigid_body[MAX_ENTITIES];
  // controller_t controller[MAX_ENTITIES];
  collision_t collision[MAX_ENTITIES];
} world_t;

entity_t create_entity(world_t *world);
void destroy_entity(world_t *world, entity_t entity);
