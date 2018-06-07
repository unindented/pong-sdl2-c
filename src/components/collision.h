#pragma once

typedef enum {
  COLLISION_WALL = 1 << 0,
  COLLISION_BALL = 1 << 1,
  COLLISION_PADDLE = 1 << 2
} collision_mask_t;

typedef struct {
  // Category masks
  collision_mask_t category;
  unsigned int mask;
} collision_t;
