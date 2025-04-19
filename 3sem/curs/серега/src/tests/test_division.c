#include "test.h"

START_TEST(test_division_insert_1) {
  s21_decimal a = {{368, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  s21_decimal c = {{0, 0, 0, 0}};
  ck_assert_int_eq(get_scale(c.bits[3]), 0);
  ck_assert_int_eq(s21_div(a, b, &c), 0);
  ck_assert_int_eq(get_scale(c.bits[3]), 1);
  ck_assert_int_eq(c.bits[0], 736);
}
END_TEST

START_TEST(test_division_insert_2) {
  big_decimal a = {{365, 0, 0, 0, 0, 0, 0, 0}};
  big_decimal b = {{5, 0, 0, 0, 0, 0, 0, 0}};
  big_decimal c = {{0, 0, 0, 0, 0, 0, 0, 0}};
  big_decimal d = big_div_big(a, b, &c);
  ck_assert_int_eq(d.bits[0], 0);
  ck_assert_int_eq(c.bits[0], 73);
}
END_TEST

START_TEST(test_division_insert_3) {
  big_decimal a = {{3680, 0, 0, 0, 0, 0, 0, 0}};
  big_decimal b = {{5, 0, 0, 0, 0, 0, 0, 0}};
  big_decimal c = {{0, 0, 0, 0, 0, 0, 0, 0}};
  big_decimal d = big_div_big(a, b, &c);
  ck_assert_int_eq(d.bits[0], 0);
  ck_assert_int_eq(c.bits[0], 736);
}
END_TEST

START_TEST(test_division_insert_4) {
  big_decimal a = {{1000001, 0, 0, 0, 0, 0, 0, 0}};
  big_decimal b = {{100000, 0, 0, 0, 0, 0, 0, 0}};
  big_decimal c = {{0, 0, 0, 0, 0, 0, 0, 0}};
  big_decimal d = big_div_big(a, b, &c);
  ck_assert_int_eq(d.bits[0], 1);
  ck_assert_int_eq(c.bits[0], 10);
}
END_TEST

START_TEST(test_division_insert_5) {
  // -0.00879
  s21_decimal a = {{0x36f, 0x0, 0x0, 0x80050000}};
  // 0.123456
  s21_decimal b = {{0x1e240, 0x0, 0x0, 0x60000}};
  s21_decimal c = {{0, 0, 0, 0}};
  // -0.0711994556765163297045101089
  s21_decimal expected = {{0x10fa3a21, 0x431b186b, 0x24cf2b6, 0x801c0000}};
  ck_assert_int_eq(s21_div(a, b, &c), 0);
  ck_assert_int_eq(c.bits[0], expected.bits[0]);
  ck_assert_int_eq(c.bits[1], expected.bits[1]);
  ck_assert_int_eq(c.bits[2], expected.bits[2]);
}
END_TEST

START_TEST(test_division_insert_6) {
  // -7.9228162514264337593543950335
  s21_decimal a = {{0xffffffff, 0xffffffff, 0xffffffff, 0x801c0000}};
  // 0.00000000000004
  s21_decimal b = {{0x4, 0x0, 0x0, 0xe0000}};
  s21_decimal c = {{0, 0, 0, 0}};
  // -198070406285660.84398385987584
  s21_decimal expected = {{0x0, 0x0, 0x40000000, 0x800e0000}};
  ck_assert_int_eq(s21_div(a, b, &c), 0);
  ck_assert_int_eq(c.bits[0], expected.bits[0]);
  ck_assert_int_eq(c.bits[1], expected.bits[1]);
  ck_assert_int_eq(c.bits[2], expected.bits[2]);
}
END_TEST

START_TEST(test_division_insert_7) {
  // -0.00879
  s21_decimal a = {{0x36f, 0x0, 0x0, 0x80050000}};
  // 0.123456
  s21_decimal b = {{0x1e240, 0x0, 0x0, 0x60000}};
  s21_decimal c = {{0, 0, 0, 0}};
  // -0.0711994556765163297045101089
  s21_decimal expected = {{0x10fa3a21, 0x431b186b, 0x24cf2b6, 0x801c0000}};
  ck_assert_int_eq(s21_div(a, b, &c), 0);
  ck_assert_int_eq(c.bits[0], expected.bits[0]);
  ck_assert_int_eq(c.bits[1], expected.bits[1]);
  ck_assert_int_eq(c.bits[2], expected.bits[2]);
}

START_TEST(test_division_insert_8) {
  // 7.9228162514264337593543950325
  s21_decimal a = {{0xfffffff5, 0xffffffff, 0xffffffff, 0x1c0000}};
  // 10
  s21_decimal b = {{0xa, 0x0, 0x0, 0x0}};
  s21_decimal c = {{0, 0, 0, 0}};
  // 0.7922816251426433759354395032
  s21_decimal expected = {{0x99999998, 0x99999999, 0x19999999, 0x1c0000}};
  ck_assert_int_eq(s21_div(a, b, &c), 0);
  ck_assert_int_eq(c.bits[0], expected.bits[0]);
  ck_assert_int_eq(c.bits[1], expected.bits[1]);
  ck_assert_int_eq(c.bits[2], expected.bits[2]);
}

START_TEST(test_division_insert_9) {
  // 79228162514264337593543950335
  s21_decimal a = {{0xffffffff, 0xffffffff, 0xffffffff, 0x0}};
  // 0
  s21_decimal b = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal c = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_div(a, b, &c), 3);
}

END_TEST
Suite *tests_division(void) {
  Suite *s = suite_create("Division");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_division_insert_1);
  tcase_add_test(tc_core, test_division_insert_2);
  tcase_add_test(tc_core, test_division_insert_3);
  tcase_add_test(tc_core, test_division_insert_4);
  tcase_add_test(tc_core, test_division_insert_5);
  tcase_add_test(tc_core, test_division_insert_6);
  tcase_add_test(tc_core, test_division_insert_7);
  tcase_add_test(tc_core, test_division_insert_8);
  tcase_add_test(tc_core, test_division_insert_9);
  suite_add_tcase(s, tc_core);
  return s;
}