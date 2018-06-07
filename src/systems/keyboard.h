#pragma once

#include "components/component.h"
#include "entities/world.h"

#define KEYBOARD_MASK (COMPONENT_CONTROLLER)

void update_keyboard(world_t *world, float dt);
