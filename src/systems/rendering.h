#pragma once

#include "components/component.h"
#include "entities/world.h"

#define RENDERING_MASK (COMPONENT_GEOMETRY)

void update_rendering(world_t *world);
