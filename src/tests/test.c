#include "test.h"

START_TEST(par_test1) {
  char path[50] = "tests/test.obj";
  int count_index = 0;
  int vertex_count = 0;
  facet *indices = parser_obj(path, &count_index, &vertex_count);
  ck_assert_float_eq(indices[0].v1.x, 0.6134);
  ck_assert_float_eq(indices[0].v1.y, -21.9357);
  ck_assert_float_eq(indices[0].v1.z, 31.4441);

  ck_assert_float_eq(indices[0].v2.x, 0.6205);
  ck_assert_float_eq(indices[0].v2.y, -21.8541);
  ck_assert_float_eq(indices[0].v2.z, 31.4935);

  ck_assert_float_eq(indices[0].v3.x, 0.5534);
  ck_assert_float_eq(indices[0].v3.y, -21.8682);
  ck_assert_float_eq(indices[0].v3.z, 31.5159);

  ck_assert_float_eq(indices[1].v1.x, 0.6205);
  ck_assert_float_eq(indices[1].v1.y, -21.8541);
  ck_assert_float_eq(indices[1].v1.z, 31.4935);

  ck_assert_float_eq(indices[1].v2.x, 0.5534);
  ck_assert_float_eq(indices[1].v2.y, -21.8682);
  ck_assert_float_eq(indices[1].v2.z, 31.5159);

  ck_assert_float_eq(indices[1].v3.x, 0.6134);
  ck_assert_float_eq(indices[1].v3.y, -21.9357);
  ck_assert_float_eq(indices[1].v3.z, 31.4441);

  ck_assert_float_eq(indices[2].v1.x, 0.5534);
  ck_assert_float_eq(indices[2].v1.y, -21.8682);
  ck_assert_float_eq(indices[2].v1.z, 31.5159);

  ck_assert_float_eq(indices[2].v2.x, 0.6134);
  ck_assert_float_eq(indices[2].v2.y, -21.9357);
  ck_assert_float_eq(indices[2].v2.z, 31.4441);

  ck_assert_float_eq(indices[2].v3.x, 0.6205);
  ck_assert_float_eq(indices[2].v3.y, -21.8541);
  ck_assert_float_eq(indices[2].v3.z, 31.4935);

  ck_assert_float_eq(indices[3].v1.x, 0);
  ck_assert_float_eq(indices[3].v1.y, 0);
  ck_assert_float_eq(indices[3].v1.z, 0);

  ck_assert_float_eq(indices[3].v2.x, 0);
  ck_assert_float_eq(indices[3].v2.y, 0);
  ck_assert_float_eq(indices[3].v2.z, 0);

  ck_assert_float_eq(indices[3].v3.x, 0);
  ck_assert_float_eq(indices[3].v3.y, 0);
  ck_assert_float_eq(indices[3].v3.z, 0);

  ck_assert_int_eq(count_index, 3);
  free(indices);
}
END_TEST

START_TEST(par_test2) {
  char path[20] = "./none.obj";
  int count_index = 0;
  int vertex_count = 0;
  parser_obj(path, &count_index, &vertex_count);
  ck_assert_int_eq(count_index, 0);
}
END_TEST

START_TEST(scale_test) {
  Vector3 v = {6.454, -1000, 0};
  float scale = 0.1;
  v = scaleV(v, scale);
  ck_assert_float_eq(v.x, 0.6454);
  ck_assert_float_eq(v.y, -100);
  ck_assert_float_eq(v.z, 0);
}
END_TEST

START_TEST(move_test) {
  Vector3 v = {6.454, -1000, 0};
  Vector3 move = {-6, 0, 0.222};
  v = moveV(v, move);
  ck_assert_float_eq(v.x, 0.454);
  ck_assert_float_eq(v.y, -1000);
  ck_assert_float_eq(v.z, 0.222);
}
END_TEST

START_TEST(center_test) {
  Vector3 v1 = {6.5, -1000, 0};
  Vector3 v2 = {-6, 0, 0.222};
  Vector3 v = centerV(v1, v2);
  ck_assert_float_eq(v.x, 0.25);
  ck_assert_float_eq(v.y, -500);
  ck_assert_float_eq(v.z, 0.111);
}
END_TEST

START_TEST(mult_test) {
  Matrix3 m1 = {-10, 0.25, 666, 0.25, 666, -10, 666, -10, 0.25};
  Matrix3 m2 = {0, 3000, 1.1, 1.1, 0, 3000, 3000, 1.1, 0};
  Matrix3 result = Matrix3Multiply(m1, m2);
  ck_assert_float_eq(0.25, 0.25);
  ck_assert_float_eq(result.m0, 1998000.275);
  ck_assert_float_eq(result.m1, -29267.4);
  ck_assert_float_eq(result.m2, 739);
  ck_assert_float_eq(result.m3, -29267.4);
  ck_assert_float_eq(result.m4, 739);
  ck_assert_float_eq(result.m5, 1998000.275);
  ck_assert_float_eq(result.m6, 739);
  ck_assert_float_eq(result.m7, 1998000.275);
  ck_assert_float_eq(result.m8, -29267.4);
}
END_TEST

START_TEST(rot_test) {
  Vector3 v = {6.5, -1000, 0};
  Vector3 rot = {0, 0, 0};
  v = oper(v, rot);
  ck_assert_float_eq(v.x, 6.5);
  ck_assert_float_eq(v.y, -1000);
  ck_assert_float_eq(v.z, 0);
}
END_TEST

Suite *suite_s21_validate(void) {
  Suite *suite = suite_create("=== PARSING  TEST ===");
  TCase *tc = tcase_create("tc");

  tcase_add_test(tc, par_test1);
  tcase_add_test(tc, par_test2);
  tcase_add_test(tc, scale_test);
  tcase_add_test(tc, move_test);
  tcase_add_test(tc, center_test);
  tcase_add_test(tc, mult_test);
  tcase_add_test(tc, rot_test);

  suite_add_tcase(suite, tc);

  return suite;
}