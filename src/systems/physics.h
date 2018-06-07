#pragma once

#include "components/component.h"
#include "entities/world.h"

#define PHYSICS_MASK (COMPONENT_GEOMETRY | COMPONENT_RIGID_BODY | COMPONENT_COLLISION)

void update_physics(world_t *world, float dt);
