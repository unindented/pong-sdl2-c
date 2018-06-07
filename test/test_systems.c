#include <stdlib.h>

#include "check.h"
#include "config.h"

#include "entities/ball.h"
#include "entities/world.h"
#include "systems/physics.h"

START_TEST(test_physics) {
  world_t world;
  entity_t ball = create_ball(&world, 0.0f, 0.0f);
  geometry_t *geometry = &(world.geometry[ball]);
  rigid_body_t *rigid_body = &(world.rigid_body[ball]);

  rigid_body->vx = 60.0f;
  rigid_body->vy = 60.0f;
  update_physics(&world, 1 / 60.0f);

  ck_assert_float_eq(geometry->x, 1.0f);
  ck_assert_float_eq(geometry->y, 1.0f);
}
END_TEST

Suite *suite_physics(void) {
  Suite *s;
  TCase *tc_physics;

  s = suite_create("systems");

  tc_physics = tcase_create("physics");
  tcase_add_test(tc_physics, test_physics);
  suite_add_tcase(s, tc_physics);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = suite_physics();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
