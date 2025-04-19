#include "test.h"

START_TEST(test_addition_1) {
  s21_decimal a = {{3, 0, 0, 0}};
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal c = {{0, 0, 0, 0}};
  int error = s21_add(a, b, &c);
  s21_decimal expected = {{5, 0, 0, 0}};
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(c.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_addition_2) {
  // 7.9228162514264337593543950335
  s21_decimal a = {{0xffffffff, 0xffffffff, 0xffffffff, 0x1c0000}};
  s21_decimal b = {{0xffffffff, 0xffffffff, 0xffffffff, 0x1c0000}};
  s21_decimal c = {{0, 0, 0, 0}};
  int error = s21_add(a, b, &c);

  s21_decimal expected = {{0x33333333, 0x33333333, 0x33333333, 0x1b0000}};
  // 15.845632502852867518708790067
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(c.bits[i], expected.bits[i]);
  }
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_addition_3) {
  big_decimal a = {{0b10100100110001100111111111111111, 0b111000110101111110, 0,
                    0, 0, 0, 0, 0}};
  big_decimal b = {{0b10100100110001100111111111111111, 0b111000110101111110, 0,
                    0, 0, 0, 0, 0}};
  big_decimal d = big_plus_big(a, b);
  ck_assert_int_eq(d.bits[0], d.bits[0]);
  ck_assert_int_eq(d.bits[1], d.bits[1]);
}
END_TEST

START_TEST(test_addition_4) {
  // 7.9228162514264337593543950335
  s21_decimal a = {{0xffffffff, 0xffffffff, 0xffffffff, 0x1c0000}};
  // 7.9228162514264337593543950335
  s21_decimal b = {{0xffffffff, 0xffffffff, 0xffffffff, 0x1c0000}};
  s21_decimal c = {{0, 0, 0, 0}};
  s21_sub(a, b, &c);
  // 0
  s21_decimal expected = {{0, 0, 0, 0x1b0000}};

  ck_assert_int_eq(c.bits[0], expected.bits[0]);
  ck_assert_int_eq(c.bits[1], expected.bits[1]);
  ck_assert_int_eq(c.bits[2], expected.bits[2]);
}
END_TEST

START_TEST(s21_sub_1) {
  // 19634040493497.9602891
  s21_decimal dec_1 = {{0x45cfc9cb, 0xa4c53e08, 0xa, 0x70000}};
  // -673300849253564.260604732
  s21_decimal dec_2 = {{0x69ccdb3c, 0xb6511754, 0x8e93, 0x80090000}};
  // 692934889747062.220893832
  s21_decimal dec_check = {{0xaef7ae88, 0x135d528f, 0x92bc, 0x90000}};
  s21_decimal result;
  int return_value = s21_sub(dec_1, dec_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_uint_eq(dec_check.bits[0], result.bits[0]);
  ck_assert_uint_eq(dec_check.bits[1], result.bits[1]);
  ck_assert_uint_eq(dec_check.bits[2], result.bits[2]);
  ck_assert_uint_eq(dec_check.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_sub_2) {
  // -2126328550
  s21_decimal dec_1 = {{0x7ebd32e6, 0x0, 0x0, 0x80000000}};
  // 3906302057056796464339
  s21_decimal dec_2 = {{0xf808d4d3, 0xc2d4c06a, 0xd3, 0x0}};
  // -3906302057058922792889
  s21_decimal dec_check = {{0x76c607b9, 0xc2d4c06b, 0xd3, 0x80000000}};
  s21_decimal result;
  int return_value = s21_sub(dec_1, dec_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_uint_eq(dec_check.bits[0], result.bits[0]);
  ck_assert_uint_eq(dec_check.bits[1], result.bits[1]);
  ck_assert_uint_eq(dec_check.bits[2], result.bits[2]);
  ck_assert_uint_eq(dec_check.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_sub_3) {
  // -272
  s21_decimal dec_1 = {{0x110, 0x0, 0x0, 0x80000000}};
  // 9631
  s21_decimal dec_2 = {{0x259f, 0x0, 0x0, 0x0}};
  // -9903
  s21_decimal dec_check = {{0x26af, 0x0, 0x0, 0x80000000}};
  s21_decimal result;
  int return_value = s21_sub(dec_1, dec_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_uint_eq(dec_check.bits[0], result.bits[0]);
  ck_assert_uint_eq(dec_check.bits[1], result.bits[1]);
  ck_assert_uint_eq(dec_check.bits[2], result.bits[2]);
  ck_assert_uint_eq(dec_check.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_sub_4) {
  // -2832729059
  s21_decimal dec_1 = {{0xa8d803e3, 0x0, 0x0, 0x80000000}};
  // 1667314059
  s21_decimal dec_2 = {{0x6361318b, 0x0, 0x0, 0x0}};
  // -4500043118
  s21_decimal dec_check = {{0xc39356e, 0x1, 0x0, 0x80000000}};
  s21_decimal result;
  int return_value = s21_sub(dec_1, dec_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_uint_eq(dec_check.bits[0], result.bits[0]);
  ck_assert_uint_eq(dec_check.bits[1], result.bits[1]);
  ck_assert_uint_eq(dec_check.bits[2], result.bits[2]);
  ck_assert_uint_eq(dec_check.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_sub_5) {
  // -1
  s21_decimal dec_1 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -82912365801323.0370
  s21_decimal dec_2 = {{0xf6c04522, 0xb81a392, 0x0, 0x80040000}};
  // 82912365801322.0370
  s21_decimal dec_check = {{0xf6c01e12, 0xb81a392, 0x0, 0x40000}};
  s21_decimal result;
  int return_value = s21_sub(dec_1, dec_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_uint_eq(dec_check.bits[0], result.bits[0]);
  ck_assert_uint_eq(dec_check.bits[1], result.bits[1]);
  ck_assert_uint_eq(dec_check.bits[2], result.bits[2]);
  ck_assert_uint_eq(dec_check.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_sub_6) {
  // -0.8
  s21_decimal dec_1 = {{0x8, 0x0, 0x0, 0x80010000}};
  // -4580497243
  s21_decimal dec_2 = {{0x1104d75b, 0x1, 0x0, 0x80000000}};
  // 4580497242.2
  s21_decimal dec_check = {{0xaa306986, 0xa, 0x0, 0x10000}};
  s21_decimal result;
  int return_value = s21_sub(dec_1, dec_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_uint_eq(dec_check.bits[0], result.bits[0]);
  ck_assert_uint_eq(dec_check.bits[1], result.bits[1]);
  ck_assert_uint_eq(dec_check.bits[2], result.bits[2]);
  ck_assert_uint_eq(dec_check.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_sub_7) {
  // 18426573947707421.97539686628
  s21_decimal dec_1 = {{0x5c49c8e4, 0x8720e912, 0x5f435e1, 0xb0000}};
  // 6405848028713
  s21_decimal dec_2 = {{0x7a4bd629, 0x5d3, 0x0, 0x0}};
  // 18420168099678708.97539686628
  s21_decimal dec_check = {{0x634ea0e4, 0x5b29515e, 0x5f3ae3b, 0xb0000}};
  s21_decimal result;
  int return_value = s21_sub(dec_1, dec_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_uint_eq(dec_check.bits[0], result.bits[0]);
  ck_assert_uint_eq(dec_check.bits[1], result.bits[1]);
  ck_assert_uint_eq(dec_check.bits[2], result.bits[2]);
  ck_assert_uint_eq(dec_check.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_sub_8) {
  // 7062158905011.8
  s21_decimal dec_1 = {{0xdeba9306, 0x403a, 0x0, 0x10000}};
  // 148268077
  s21_decimal dec_2 = {{0x8d6642d, 0x0, 0x0, 0x0}};
  // 7062010636934.8
  s21_decimal dec_check = {{0x865aa944, 0x403a, 0x0, 0x10000}};
  s21_decimal result;
  int return_value = s21_sub(dec_1, dec_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_uint_eq(dec_check.bits[0], result.bits[0]);
  ck_assert_uint_eq(dec_check.bits[1], result.bits[1]);
  ck_assert_uint_eq(dec_check.bits[2], result.bits[2]);
  ck_assert_uint_eq(dec_check.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_sub_9) {
  // -156062.9406015
  s21_decimal dec_1 = {{0x5cc2e93f, 0x16b, 0x0, 0x80070000}};
  // -914
  s21_decimal dec_2 = {{0x392, 0x0, 0x0, 0x80000000}};
  // -155148.9406015
  s21_decimal dec_check = {{0x3bf9943f, 0x169, 0x0, 0x80070000}};
  s21_decimal result;
  int return_value = s21_sub(dec_1, dec_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_uint_eq(dec_check.bits[0], result.bits[0]);
  ck_assert_uint_eq(dec_check.bits[1], result.bits[1]);
  ck_assert_uint_eq(dec_check.bits[2], result.bits[2]);
  ck_assert_uint_eq(dec_check.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_sub_10) {
  // -35.0194103298510666401431
  s21_decimal dec_1 = {{0xf2a10697, 0xf75061d, 0x4a28, 0x80160000}};
  // 3.44
  s21_decimal dec_2 = {{0x158, 0x0, 0x0, 0x20000}};
  // -38.4594103298510666401431
  s21_decimal dec_check = {{0x10210697, 0xe35b931b, 0x5170, 0x80160000}};
  s21_decimal result;
  int return_value = s21_sub(dec_1, dec_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_uint_eq(dec_check.bits[0], result.bits[0]);
  ck_assert_uint_eq(dec_check.bits[1], result.bits[1]);
  ck_assert_uint_eq(dec_check.bits[2], result.bits[2]);
  ck_assert_uint_eq(dec_check.bits[3], result.bits[3]);
}
END_TEST

Suite *tests_add(void) {
  Suite *s = suite_create("Addition");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_sub_1);
  tcase_add_test(tc_core, s21_sub_2);
  tcase_add_test(tc_core, s21_sub_3);
  tcase_add_test(tc_core, s21_sub_4);
  tcase_add_test(tc_core, s21_sub_5);
  tcase_add_test(tc_core, s21_sub_6);
  tcase_add_test(tc_core, s21_sub_7);
  tcase_add_test(tc_core, s21_sub_8);
  tcase_add_test(tc_core, s21_sub_9);
  tcase_add_test(tc_core, s21_sub_10);
  tcase_add_test(tc_core, test_addition_1);
  tcase_add_test(tc_core, test_addition_2);
  tcase_add_test(tc_core, test_addition_3);
  tcase_add_test(tc_core, test_addition_4);

  suite_add_tcase(s, tc_core);
  return s;
}