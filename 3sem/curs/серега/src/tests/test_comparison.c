#include "test.h"

START_TEST(test_is_less) {
  s21_decimal value_1 = {{2, 0, 0, 0}};
  s21_decimal value_2 = {{3, 0, 0, 0}};
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}
END_TEST

START_TEST(test_is_equal) {
  s21_decimal value_1 = {{3, 0, 0, 0}};
  s21_decimal value_2 = {{3, 0, 0, 0}};
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}
END_TEST

START_TEST(test_is_equal_2) {
  s21_decimal value_1 = {{3, 0, 0, 0}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}
END_TEST

START_TEST(test_is_equal_3) {
  s21_decimal value_1 = {{25789375, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal value_2 = {{2578937500, 0x00000000, 0x00000000, 0x00020000}};
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}
END_TEST

START_TEST(test_is_equal_4) {
  s21_decimal value_1 = {{0x0001D4C0, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal value_2 = {{0x0001D4C0, 0x00000000, 0x00000000, 0x00000000}};
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}
END_TEST

START_TEST(test_is_greater) {
  s21_decimal value_1 = {{4, 0, 0, 0}};
  s21_decimal value_2 = {{3, 0, 0, 0}};
  int result = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}
END_TEST

START_TEST(test_is_greater_1) {
  s21_decimal value_1 = {{0x0000000B, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal value_2 = {{0x00000012, 0x00000000, 0x00000000, 0x80000000}};
  int result = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}
END_TEST

START_TEST(test_is_greater_2) {
  // 3838
  s21_decimal src1, src2;
  // src1 = 3;
  // src2 = 2;

  src1.bits[0] = 0b00000000000000000000000000000011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000000000000000010;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(test_is_greater_3) {
  // 4162
  s21_decimal src1, src2;
  // src1 = -12345677.987654345678987654346;
  // src2 = 87654323456.9876545678987653;

  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b10000000000101010000000000000000;
  src2.bits[0] = 0b00010001110011011101000110000101;
  src2.bits[1] = 0b11110101101111000110111111000000;
  src2.bits[2] = 0b00000010110101010000111100111111;
  src2.bits[3] = 0b00000000000100000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 0;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(test_is_greater_4) {
  // 4198
  s21_decimal src1, src2;
  // src1 = -12345677.987654345678987654346;
  // src2 = -87654323456.9876545678987653;
  src1.bits[0] = 0b10010001000010101111010011001010;
  src1.bits[1] = 0b11000000010001011101010111110010;
  src1.bits[2] = 0b00100111111001000001101100000000;
  src1.bits[3] = 0b10000000000101010000000000000000;
  src2.bits[0] = 0b00010001110011011101000110000101;
  src2.bits[1] = 0b11110101101111000110111111000000;
  src2.bits[2] = 0b00000010110101010000111100111111;
  src2.bits[3] = 0b10000000000100000000000000000000;
  int result = s21_is_greater(src1, src2);
  int origin = 1;
  ck_assert_int_eq(result, origin);
}
END_TEST

START_TEST(test_is_not_equal) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 1, 0, 0}};
  set_sign(&(b.bits[3]), 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_is_less_1) {
  s21_decimal small = {{1}};
  set_sign(&(small.bits[3]), 1);
  s21_decimal big_small = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  set_sign(&(big_small.bits[3]), 1);
  ck_assert_int_eq(s21_is_less(big_small, small), 1);
}

START_TEST(test_is_less_or_equal) {
  s21_decimal small = {{1}};
  set_sign(&(small.bits[3]), 1);
  s21_decimal big_small = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  set_sign(&(big_small.bits[3]), 1);
  ck_assert_int_eq(s21_is_less_or_equal(big_small, small), 1);
}

START_TEST(test_is_greater_or_equal) {
  s21_decimal small = {{1}};
  set_sign(&(small.bits[3]), 1);
  s21_decimal big_small = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  set_sign(&(big_small.bits[3]), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(big_small, small), 0);
}

Suite *tests_comparison(void) {
  Suite *s = suite_create("Comparison");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_is_less);
  tcase_add_test(tc_core, test_is_equal);
  tcase_add_test(tc_core, test_is_equal_2);
  tcase_add_test(tc_core, test_is_equal_3);
  tcase_add_test(tc_core, test_is_equal_4);
  tcase_add_test(tc_core, test_is_greater);
  tcase_add_test(tc_core, test_is_greater_1);
  tcase_add_test(tc_core, test_is_greater_2);
  tcase_add_test(tc_core, test_is_greater_3);
  tcase_add_test(tc_core, test_is_greater_4);
  tcase_add_test(tc_core, test_is_not_equal);
  tcase_add_test(tc_core, test_is_less_1);
  tcase_add_test(tc_core, test_is_less_or_equal);
  tcase_add_test(tc_core, test_is_greater_or_equal);
  suite_add_tcase(s, tc_core);
  return s;
}
