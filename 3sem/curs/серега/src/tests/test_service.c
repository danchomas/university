#include "test.h"

START_TEST(test_func_insert_1) {
  big_decimal a = {{0b10000000000000000000000000000001, 0,
                    0b10000000000000000000000000000000, 1, 0, 0, 0, 0}};
  int num_1 = 0;
  int num_2 = 31;
  int num_3 = 95;
  int num_4 = 96;
  ck_assert_int_eq(check_bit(a, num_1), 1);
  ck_assert_int_eq(check_bit(a, num_2), 1);
  ck_assert_int_eq(check_bit(a, num_3), 1);
  ck_assert_int_eq(check_bit(a, num_4), 1);
}
END_TEST

START_TEST(test_func_insert_2) {
  big_decimal a = {{0, 0, 0, 0, 0, 0, 0, 0}};
  int num = 2;
  set_bit(&a, num, true);
  ck_assert_int_eq(a.bits[0], 4);
}
END_TEST

START_TEST(test_func_insert_3) {
  s21_decimal a = {{0, 0, 0, 0b10000000000000000000000000000000}};
  ck_assert_int_eq(check_sign(a.bits[3]), true);
}
END_TEST

START_TEST(test_func_insert_4) {
  s21_decimal a = {{0, 0, 0, 0}};
  ck_assert_int_eq(check_sign(a.bits[3]), false);
  set_sign(&a.bits[3], true);
  ck_assert_int_eq(check_sign(a.bits[3]), true);
}
END_TEST

START_TEST(test_func_insert_5) {
  big_decimal a = {{0, 0, 0, 0, 0, 0, 0, 0b00000000000011000000000000000000}};
  ck_assert_int_eq(get_scale(a.bits[7]), 12);
}
END_TEST

START_TEST(test_func_insert_6) {
  big_decimal a = {{0, 0, 0, 0, 0, 0, 0, 0b00000000000011000000000000000000}};
  ck_assert_int_eq(get_scale(a.bits[7]), 12);
  set_scale(&a.bits[7], 25);
  ck_assert_int_eq(get_scale(a.bits[7]), 25);
}
END_TEST

START_TEST(test_func_insert_7) {
  big_decimal a = {{0, 0, 0, 0, 0, 0, 0, 0}};
  ck_assert_int_eq(is_not_null(a), 0);
  set_bit(&a, 55, true);
  ck_assert_int_eq(is_not_null(a), 1);
}
END_TEST

START_TEST(test_func_insert_8) {
  big_decimal a = {{0b00000000000000000000000000000111, 0, 0, 0, 0, 0, 0, 0}};
  ck_assert_int_eq(a.bits[0], 7);
  ck_assert_int_eq(shift_big_decimal(a, 31, 'L').bits[0], 2147483648);
  ck_assert_int_eq(shift_big_decimal(a, 32, 'L').bits[0], 0);
  ck_assert_int_eq(shift_big_decimal(a, 32, 'L').bits[1], 7);
  ck_assert_int_eq(shift_big_decimal(a, 64, 'L').bits[2], 7);
}
END_TEST

START_TEST(test_func_insert_9) {
  big_decimal value_1 = {{222, 0, 0, 0, 0, 0, 0, 0}};
  big_decimal value_2 = {{111, 0, 0, 0, 0, 0, 0, 0}};
  big_decimal value_3 = {{0, 0, 0, 0, 0, 0, 0, 0}};
  value_3 = big_plus_big(value_1, value_2);
  ck_assert_int_eq(value_3.bits[0], 333);
}
END_TEST

START_TEST(test_func_insert_10) {
  big_decimal value_1 = {{222, 0, 0, 0, 0, 0, 0, 0}};
  big_decimal value_2 = {{111, 0, 0, 0, 0, 0, 0, 0}};
  big_decimal value_3 = {{0, 0, 0, 0, 0, 0, 0, 0}};
  value_3 = big_minus_big(value_1, value_2);
  ck_assert_int_eq(value_3.bits[0], 111);
}
END_TEST

START_TEST(test_func_insert_11) {
  big_decimal value_1 = {{222, 0, 0, 0, 0, 0, 0, 0}};
  big_decimal value_2 = {{111, 0, 0, 0, 0, 0, 0, 0}};
  set_scale(&value_1.bits[7], 4);
  normalization(&value_1, &value_2);
  ck_assert_int_eq(get_scale(value_2.bits[7]), 4);
  ck_assert_int_eq(value_2.bits[0], 1110000);
}
END_TEST

START_TEST(test_func_insert_12) {
  big_decimal value_1 = {{222, 0, 0, 0, 0, 0, 0, 0}};
  big_decimal value_2 = {0};
  big_div10(value_1, &value_2);
  ck_assert_int_eq(value_2.bits[0], 22);
}
END_TEST

START_TEST(test_func_insert_20) {
  big_decimal value_1 = {{0, 0, 0, 222, 0, 0, 0, 0}};
  big_decimal value_2 = {{0, 0, 0, 111, 0, 0, 0, 0}};
  ck_assert_int_eq(big_mantissa_is_less(value_2, value_1), 1);
  ck_assert_int_eq(big_mantissa_is_less(value_1, value_1), 0);
}
END_TEST

START_TEST(test_func_insert_21) {
  big_decimal value_1 = {{222, 0, 0, 0, 0, 0, 0, 0}};
  big_decimal value_2 = {{111, 0, 0, 0, 0, 0, 0, 0}};
  ck_assert_int_eq(big_mantissa_is_less_or_equal(value_2, value_1), 1);
  ck_assert_int_eq(big_mantissa_is_less_or_equal(value_1, value_1), 1);
  ck_assert_int_eq(big_mantissa_is_less_or_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(test_func_insert_22) {
  big_decimal value_1 = {{222, 0, 0, 0, 0, 0, 0, 0}};
  big_decimal value_2 = {{111, 0, 0, 0, 0, 0, 0, 0}};
  ck_assert_int_eq(big_mantissa_is_greater(value_1, value_2), 1);
  ck_assert_int_eq(big_mantissa_is_greater(value_1, value_1), 0);
}
END_TEST

START_TEST(test_func_insert_23) {
  big_decimal value_1 = {{222, 0, 222, 0, 0, 0, 0, 0}};
  big_decimal value_2 = {{111, 0, 111, 0, 0, 0, 0, 0}};
  ck_assert_int_eq(big_mantissa_is_greater_or_equal(value_1, value_2), 1);
  ck_assert_int_eq(big_mantissa_is_greater_or_equal(value_1, value_1), 1);
  ck_assert_int_eq(big_mantissa_is_greater_or_equal(value_2, value_1), 0);
}
END_TEST

START_TEST(test_func_insert_24) {
  big_decimal value_1 = {{222, 0, 222, 0, 0, 0, 0, 0}};
  big_decimal value_2 = {{111, 0, 111, 0, 0, 0, 0, 0}};
  ck_assert_int_eq(big_mantissa_is_equal(value_1, value_2), 0);
  ck_assert_int_eq(big_mantissa_is_equal(value_1, value_1), 1);
  ck_assert_int_eq(big_mantissa_is_equal(value_2, value_1), 0);
}
END_TEST

START_TEST(test_func_insert_25) {
  big_decimal value_1 = {{222, 0, 222, 0, 0, 0, 0, 0}};
  big_decimal value_2 = {{111, 0, 111, 0, 0, 0, 0, 0}};
  ck_assert_int_eq(big_mantissa_is_not_equal(value_1, value_2), 1);
  ck_assert_int_eq(big_mantissa_is_not_equal(value_1, value_1), 0);
  ck_assert_int_eq(big_mantissa_is_not_equal(value_2, value_1), 1);
}
END_TEST

Suite *tests_functions(void) {
  Suite *s = suite_create("Functions");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_func_insert_1);
  tcase_add_test(tc_core, test_func_insert_2);
  tcase_add_test(tc_core, test_func_insert_3);
  tcase_add_test(tc_core, test_func_insert_4);
  tcase_add_test(tc_core, test_func_insert_5);
  tcase_add_test(tc_core, test_func_insert_6);
  tcase_add_test(tc_core, test_func_insert_7);
  tcase_add_test(tc_core, test_func_insert_8);
  tcase_add_test(tc_core, test_func_insert_9);
  tcase_add_test(tc_core, test_func_insert_10);
  tcase_add_test(tc_core, test_func_insert_11);
  tcase_add_test(tc_core, test_func_insert_12);
  tcase_add_test(tc_core, test_func_insert_20);
  tcase_add_test(tc_core, test_func_insert_21);
  tcase_add_test(tc_core, test_func_insert_22);
  tcase_add_test(tc_core, test_func_insert_23);
  tcase_add_test(tc_core, test_func_insert_24);
  tcase_add_test(tc_core, test_func_insert_25);

  suite_add_tcase(s, tc_core);
  return s;
}