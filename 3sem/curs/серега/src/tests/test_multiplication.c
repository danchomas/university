#include "test.h"

START_TEST(mul_null) {
  s21_decimal value_1 = {{2, 0, 0, 0}};
  s21_decimal value_2 = {{3, 0, 0, 0}};
  int error = s21_mul(value_1, value_2, NULL);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(simple_mul) {
  s21_decimal value_1 = {{2, 0, 0, 0}};
  s21_decimal value_2 = {{3, 0, 0, 0}};
  s21_decimal result = {{0}};
  int error = s21_mul(value_1, value_2, &result);
  s21_decimal expected = {{6, 0, 0, 0}};
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(simple_mul_negative) {
  s21_decimal value_1 = {{14, 0, 0, 1 << 31}};
  s21_decimal value_2 = {{22, 0, 0, 0}};
  s21_decimal result = {{0}};
  int error = s21_mul(value_1, value_2, &result);
  s21_decimal expected = {{308, 0, 0, 1 << 31}};
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(simple_mul_zero) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int error = s21_mul(value_1, value_2, &result);
  s21_decimal expected = {{0, 0, 0, 0}};
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(simple_mul_zero_1) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 1, 0, 0}};
  s21_decimal result = {{0}};
  int error = s21_mul(value_1, value_2, &result);
  s21_decimal expected = {{0, 0, 0, 0}};
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(mul_negative) {
  s21_decimal value_1 = {{0, 1, 0, 1 << 31}};
  s21_decimal value_2 = {{100, 0, 0, 1 << 31}};
  s21_decimal result = {{0}};
  int error = s21_mul(value_1, value_2, &result);
  s21_decimal expected = {{0, 100, 0, 0}};
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(mul_negative_2) {
  s21_decimal value_1 = {{0, 0, 4, 1 << 31}};
  s21_decimal value_2 = {{1024, 0, 0, 1 << 31}};
  s21_decimal result = {{0}};
  int error = s21_mul(value_1, value_2, &result);
  s21_decimal expected = {{0, 0, 4096, 0}};
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}

END_TEST

START_TEST(mul_negative_overword) {
  s21_decimal value_1 = {{1073741824, 0, 0, 1 << 31}};
  s21_decimal value_2 = {{8, 0, 0, 0}};
  s21_decimal result = {{0}};
  int error = s21_mul(value_1, value_2, &result);
  s21_decimal expected = {{0, 2, 0, 1 << 31}};
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(mul_overflow) {
  s21_decimal value_1 = {{0, 0, 1, 0}};
  s21_decimal value_2 = {{4294967295, 1, 0, 0}};
  s21_decimal result = {{0}};

  int error = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(error, 1);

  s21_decimal value_3 = {{0, 0, 4294967295, 0}};
  s21_decimal value_4 = {{11, 0, 0, 0}};
  s21_decimal result2 = {{0}};

  error = s21_mul(value_3, value_4, &result2);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(mul_with_scale) {
  s21_decimal value_1 = {{100, 0, 0, 2 << 16}};
  s21_decimal value_2 = {{50, 0, 0, 1 << 16}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{5000, 0, 0, 3 << 16}};

  int error = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(error, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }

  s21_decimal value_3 = {{1000, 0, 0, 12 << 16}};
  s21_decimal value_4 = {{0, 0, 123, 8 << 16}};
  s21_decimal result2 = {{0}};
  s21_decimal expected2 = {{0, 0, 123000, 20 << 16}};

  error = s21_mul(value_3, value_4, &result2);
  ck_assert_int_eq(error, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result2.bits[i], expected2.bits[i]);
  }
}
END_TEST

START_TEST(mul_big) {
  s21_decimal value_1 = {
      {0b00101010010100101001001010100101, 0b1001010100101, 0, 0}};
  s21_decimal value_2 = {{0b1001010100101001010100101001010, 0, 0, 0}};
  s21_decimal result = {{0}};
  int error = s21_mul(value_1, value_2, &result);
  s21_decimal expected = {{0b00111000000100010101000010110010,
                           0b10010010000011001100001011001111, 0b10101101110,
                           0}};
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(mul_big_2) {
  s21_decimal value_1 = {
      {0b11101010110100101001001010100101, 0b1111111011101, 0, 3 << 16}};
  s21_decimal value_2 = {{0b1111111111110111001011010111010, 0, 0, 6 << 16}};
  s21_decimal result = {{0}};
  int error = s21_mul(value_1, value_2, &result);
  s21_decimal expected = {{0b10100001101100100011100111100010,
                           0b01101000110101101110001000001001, 0b111111101110,
                           9 << 16}};
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(mul_big_3) {
  s21_decimal value_1 = {{0b11111111111111111111111111111111,
                          0b11111111111111111111111111111111,
                          0b11111111111111111111111111111111, 0}};
  s21_decimal value_2 = {{1000000001, 0, 0, 9 << 16}};
  s21_decimal result = {{0}};
  int error = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(mul_big_4) {
  s21_decimal value_1 = {{0b11111111111111111111111111111111,
                          0b11111111111111111111111111111111,
                          0b11111111111111111111111111111111, 0}};
  s21_decimal value_2 = {{0b11111111111111111111111111111111,
                          0b11111111111111111111111111111111,
                          0b11111111111111111111111111111111, 1 << 31}};
  s21_decimal result = {{0}};
  int error = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(error, 2);
}
END_TEST

START_TEST(mul_small) {
  s21_decimal value_1 = {{0b101010100001010101101010110100, 0, 0, 21 << 16}};
  s21_decimal value_2 = {{0b110101010101001001001010100101, 0, 0, 7 << 16}};
  s21_decimal result = {{0}};
  int error = s21_mul(value_1, value_2, &result);
  s21_decimal expected = {{0b01111100101111100001111000000100,
                           0b1000110110111010011111100100, 0, 28 << 16}};
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(mul_bank_round) {
  s21_decimal value_1 = {{15, 0, 0, 27 << 16}};
  s21_decimal value_2 = {{1, 0, 0, 2 << 16}};
  s21_decimal result = {{0}};
  int error = s21_mul(value_1, value_2, &result);
  s21_decimal expected = {{2, 0, 0, 28 << 16}};
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(mul_bank_round_2) {
  s21_decimal value3 = {{2469, 0, 0, 15 << 16}};
  s21_decimal value4 = {{50, 0, 0, 15 << 16}};
  s21_decimal result2 = {{0}};
  s21_decimal expected2 = {{1234, 0, 0, 28 << 16}};

  int error = s21_mul(value3, value4, &result2);
  ck_assert_int_eq(error, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result2.bits[i], expected2.bits[i]);
  }

  s21_decimal value5 = {{1717986917, 1717986918, 1717986918, 0}};
  s21_decimal value6 = {{25, 0, 0, 1 << 16}};
  s21_decimal result3 = {{0}};
  s21_decimal expected3 = {{0xFFFFFFFF - 3, 0xFFFFFFFF, 0xFFFFFFFF, 0}};

  error = s21_mul(value5, value6, &result3);
  ck_assert_int_eq(error, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result3.bits[i], expected3.bits[i]);
  }
}
END_TEST

Suite *tests_mul(void) {
  Suite *s = suite_create("Mul");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, mul_null);
  tcase_add_test(tc_core, simple_mul);
  tcase_add_test(tc_core, simple_mul_negative);
  tcase_add_test(tc_core, simple_mul_zero);
  tcase_add_test(tc_core, simple_mul_zero_1);
  tcase_add_test(tc_core, mul_negative);
  tcase_add_test(tc_core, mul_negative_2);
  tcase_add_test(tc_core, mul_negative_overword);
  tcase_add_test(tc_core, mul_overflow);
  tcase_add_test(tc_core, mul_with_scale);
  tcase_add_test(tc_core, mul_big);
  tcase_add_test(tc_core, mul_big_2);
  tcase_add_test(tc_core, mul_big_3);
  tcase_add_test(tc_core, mul_big_4);
  tcase_add_test(tc_core, mul_small);
  tcase_add_test(tc_core, mul_bank_round);
  tcase_add_test(tc_core, mul_bank_round_2);

  suite_add_tcase(s, tc_core);
  return s;
}