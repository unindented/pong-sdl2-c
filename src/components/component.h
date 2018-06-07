#pragma once

typedef enum {
  COMPONENT_NONE = 0,
  COMPONENT_GEOMETRY = 1 << 0,
  COMPONENT_RIGID_BODY = 1 << 1,
  COMPONENT_CONTROLLER = 1 << 2,
  COMPONENT_COLLISION = 1 << 3
} component_mask_t;
