#include <stdlib.h>

#include "check.h"
#include "config.h"

#include "utils/math.h"

START_TEST(test_min) {
  ck_assert_float_eq(min(1.0f, 2.0f), 1.0f);
  ck_assert_float_eq(min(2.0f, 1.0f), 1.0f);
  ck_assert_float_eq(min(1.0f, 1.0f), 1.0f);
}
END_TEST

START_TEST(test_max) {
  ck_assert_float_eq(max(1.0f, 2.0f), 2.0f);
  ck_assert_float_eq(max(2.0f, 1.0f), 2.0f);
  ck_assert_float_eq(max(1.0f, 1.0f), 1.0f);
}
END_TEST

START_TEST(test_clamp) {
  ck_assert_float_eq(clamp(3.0f, 2.0f, 4.0f), 3.0f);
  ck_assert_float_eq(clamp(2.0f, 2.0f, 4.0f), 2.0f);
  ck_assert_float_eq(clamp(1.0f, 2.0f, 4.0f), 2.0f);
  ck_assert_float_eq(clamp(4.0f, 2.0f, 4.0f), 4.0f);
  ck_assert_float_eq(clamp(5.0f, 2.0f, 4.0f), 4.0f);
}
END_TEST

Suite *suite_utils(void) {
  Suite *s;
  TCase *tc_math;

  s = suite_create("utils");

  tc_math = tcase_create("math");
  tcase_add_test(tc_math, test_min);
  tcase_add_test(tc_math, test_max);
  tcase_add_test(tc_math, test_clamp);
  suite_add_tcase(s, tc_math);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = suite_utils();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
