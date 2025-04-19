#include <check.h>
#include <limits.h>
#include <stdio.h>

#include "../s21_decimal.h"
// add
START_TEST(test_s21_add_1) {  // с положительными числами
  s21_decimal value_1, value_2, result;
  value_1 = (s21_decimal){.bits = {4, 0, 0, 0}};
  value_2 = (s21_decimal){.bits = {91, 0, 0, 0}};
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  s21_decimal expected_result = {.bits = {95, 0, 0, 0}};
  ck_assert_mem_eq(&result, &expected_result, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_add_2) {  // с отрицательными числами
  s21_decimal value_1 = {.bits = {4, 0, 0, 0x80000000}};
  s21_decimal value_2 = {.bits = {2, 0, 0, 0x80000000}};
  s21_decimal result;
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  s21_decimal expected_result = {.bits = {6, 0, 0, 0x80000000}};
  ck_assert_mem_eq(&result, &expected_result, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_add_3) {  // с нулём и положительным числом
  s21_decimal value_1 = {.bits = {0, 0, 0, 0}};
  s21_decimal value_2 = {.bits = {11, 0, 0, 0}};
  s21_decimal result;
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  s21_decimal expected_result = {.bits = {11, 0, 0, 0}};
  ck_assert_mem_eq(&result, &expected_result, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_add_4) {  // с нулём и отрицательным числом
  s21_decimal value_1 = {.bits = {0, 0, 0, 0}};
  s21_decimal value_2 = {.bits = {25, 0, 0, 0x80000000}};
  s21_decimal result;
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  s21_decimal expected_result = {.bits = {25, 0, 0, 0x80000000}};
  ck_assert_mem_eq(&result, &expected_result, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_add_9) {  // c десятичной точностью
  s21_decimal value_1 = {.bits = {100000000, 0, 0, 0}};
  s21_decimal value_2 = {.bits = {200000000, 0, 0, 0}};
  s21_decimal result;
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  s21_decimal expected = {.bits = {300000000, 0, 0, 0}};
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_add_10) {
  s21_decimal value_1 = {.bits = {1, 1, 1, 65536}};
  s21_decimal value_2 = {.bits = {1, 1, 1, 65536}};
  s21_decimal result;
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  s21_decimal expected = {.bits = {2, 2, 2, 65536}};
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_add_11) {
  s21_decimal value_1 = {.bits = {1, 1, 1, 65536}};
  s21_decimal value_2 = {.bits = {1, 1, 1, 655360}};
  s21_decimal result;
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  s21_decimal expected = {.bits = {1000000001, 1000000001, 1000000001, 655360}};
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_add_12) {
  s21_decimal value_1 = {.bits = {24, 1, 1, -2147418112}};
  s21_decimal value_2 = {.bits = {1, 15, 1, 655360}};
  s21_decimal result;
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  s21_decimal expected = {
      .bits = {-1769803777, 999999990, 999999999, -2146828288}};
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_add_13) {
  s21_decimal value_1 = {.bits = {1, 1, 1, 655360}};
  s21_decimal value_2 = {.bits = {1, 1, 1, -2147418112}};
  s21_decimal result;
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  s21_decimal expected = {
      .bits = {999999999, 999999999, 999999999, -2146828288}};
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

// sub
START_TEST(test_s21_sub_1) {  // 5 - 3 = 2
  s21_decimal value_1 = {.bits = {5, 0, 0, 0}};
  s21_decimal value_2 = {.bits = {3, 0, 0, 0}};
  s21_decimal result;
  int status = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 2);
}
END_TEST

START_TEST(test_s21_sub_2) {  // 3 - 5 = -2
  s21_decimal value_1 = {.bits = {3, 0, 0, 0}};
  s21_decimal value_2 = {.bits = {5, 0, 0, 0}};
  s21_decimal result;
  int status = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[3] & 0x80000000,
                   0x80000000);  // Проверка на отрицательный знак
}
END_TEST

START_TEST(test_s21_sub_3) {  // 0 - 0 = 0
  s21_decimal value_1 = {.bits = {0, 0, 0, 0}};
  s21_decimal value_2 = {.bits = {0, 0, 0, 0}};
  s21_decimal result;
  int status = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
}
END_TEST

START_TEST(test_s21_sub_4) {  // 10 - 5 = 5
  s21_decimal value_1 = {.bits = {10, 0, 0, 0}};
  s21_decimal value_2 = {.bits = {5, 0, 0, 0}};
  s21_decimal result;
  int status = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 5);
}
END_TEST

START_TEST(test_s21_sub_5) {  // 5 - 10 = -5
  s21_decimal value_1 = {.bits = {5, 0, 0, 0}};
  s21_decimal value_2 = {.bits = {10, 0, 0, 0}};
  s21_decimal result;
  int status = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(result.bits[3] & 0x80000000,
                   0x80000000);  // Проверка на отрицательный знак
}
END_TEST

START_TEST(test_s21_sub_6) {  // -5 - -3 = -2
  s21_decimal value_1 = {.bits = {5, 0, 0, 0x80000000}};
  s21_decimal value_2 = {.bits = {3, 0, 0, 0x80000000}};
  s21_decimal result;
  int status = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 2);
  // Проверка на отрицательный знак с использованием маски
  ck_assert_int_eq(result.bits[3] & 0x80000000, 0x80000000);
}
END_TEST

START_TEST(test_s21_sub_7) {  // 5 - -5 = 10
  s21_decimal value_1 = {.bits = {5, 0, 0, 0}};
  s21_decimal value_2 = {.bits = {5, 0, 0, 0x80000000}};
  s21_decimal result;
  int status = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 10);
}
END_TEST

START_TEST(test_s21_sub_10) {  // Проверка вычитания с учетом масштаба и знака
  s21_decimal val1 = {.bits = {1, 1, 1, 65536}};  // 1844674407800451891.3
  s21_decimal val2 = {
      .bits = {1, 1, 1, 0x80000000 | 65536}};  // -1844674407800451891.3
  s21_decimal result;
  int status = s21_sub(val1, val2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 2);
  // Проверка на правильный масштаб
  ck_assert_int_eq(result.bits[2], 2);
  ck_assert_int_eq(result.bits[3] & 0xFFFF0000, 65536);  // Проверка масштаба
}
END_TEST

START_TEST(test_s21_sub_11) {  // Проверка обратного вычитания с учетом знака
  s21_decimal val1 = {.bits = {1, 1, 1, 65536}};  // 1844674407800451891.3
  s21_decimal val2 = {
      .bits = {1, 1, 1, 0x80000000 | 65536}};  // -1844674407800451891.3
  s21_decimal result;
  int status = s21_sub(val2, val1, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 2);
  // Проверка на отрицательный знак и правильный масштаб
  ck_assert_int_eq(result.bits[2], 2);
  ck_assert_int_eq(result.bits[3] & 0xFFFF0000, 0x80000000 | 65536);
}
END_TEST

START_TEST(test_s21_sub_12) {
  s21_decimal val1 = {
      .bits = {1, 1, 1, -2147418112}};  // -1844674407800451891.3
  s21_decimal val2 = {
      .bits = {1, 1, 1, -2147418112}};  // -1844674407800451891.3
  s21_decimal result;
  int status = s21_sub(val1, val2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);  // {0, 0, 0, -2147418112}
}
END_TEST

START_TEST(test_s21_sub_13) {
  s21_decimal val1 = {
      .bits = {1, 1, 1, -2147418112}};  // -1844674407800451891.3
  s21_decimal val2 = {
      .bits = {1, 1, 1, -2147418112}};  // -1844674407800451891.3
  s21_decimal result;
  int status = s21_sub(val2, val1, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);  // {0, 0, 0, -2147418112}
}
END_TEST

START_TEST(test_s21_sub_14) {
  s21_decimal val1 = {
      .bits = {1, 1, 1, -2147418112}};            // -1844674407800451891.3
  s21_decimal val2 = {.bits = {1, 1, 1, 65536}};  // 1844674407800451891.3
  s21_decimal result;
  int status = s21_sub(val1, val2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 2);  // {-2, -2, -2, -2147418112}
}
END_TEST

START_TEST(test_s21_sub_15) {
  s21_decimal val1 = {
      .bits = {1, 1, 1, -2147418112}};            // -1844674407800451891.3
  s21_decimal val2 = {.bits = {1, 1, 1, 65536}};  // 1844674407800451891.3
  s21_decimal result;
  int status = s21_sub(val2, val1, &result);
  ck_assert_int_eq(status, 0);          //
  ck_assert_int_eq(result.bits[0], 2);  // {2, 2, 2, 65536}
}
END_TEST

// mul
START_TEST(test_s21_mul_1) {
  s21_decimal value_1 = {.bits = {5, 0, 0, 0}};
  s21_decimal value_2 = {.bits = {3, 0, 0, 0}};
  s21_decimal result;
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 15);
}
END_TEST

START_TEST(test_s21_mul_2) {
  s21_decimal value_1 = {.bits = {3, 0, 0, 0}};
  s21_decimal value_2 = {.bits = {0, 0, 0, 0}};
  s21_decimal result;
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
}
END_TEST

START_TEST(test_s21_mul_3) {
  s21_decimal value_1 = {.bits = {0, 0, 0, 0}};
  s21_decimal value_2 = {.bits = {5, 0, 0, 0}};
  s21_decimal result;
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
}
END_TEST

START_TEST(test_s21_mul_4) {
  s21_decimal value_1 = {.bits = {10, 0, 0, 0}};
  s21_decimal value_2 = {.bits = {5, 0, 0, 0}};
  s21_decimal result;
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 50);
}
END_TEST

START_TEST(test_s21_mul_5) {
  s21_decimal value_1 = {.bits = {5, 0, 0, 0}};
  s21_decimal value_2 = {.bits = {2, 0, 0, 0}};
  s21_decimal result;
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 10);
  ck_assert_int_eq(result.bits[3], 0);  // Проверяем правильность знака
}
END_TEST

START_TEST(test_s21_mul_6) {
  s21_decimal value_1 = {.bits = {3, 0, 0, 0x80000000}};
  s21_decimal value_2 = {.bits = {2, 0, 0, 0x80000000}};
  s21_decimal result;
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 6);
}
END_TEST

START_TEST(test_s21_mul_8) {
  s21_decimal value_1 = {.bits = {0, 0, 0, 0}};
  s21_decimal value_2 = {.bits = {5, 0, 0, 0x80000000}};
  s21_decimal result;
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
}
END_TEST

START_TEST(test_s21_mul_9) {
  s21_decimal value_1 = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {.bits = {2, 0, 0, 0}};
  s21_decimal result;
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, 1);  // Ожидаем переполнение
}
END_TEST

START_TEST(test_s21_mul_10) {
  s21_decimal value_1 = {.bits = {1, 0, 0, 0}};
  s21_decimal value_2 = {.bits = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result;
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_s21_mul_12) {
  s21_decimal val1 = {.bits = {1, 0, 0, 655360}};  // 0.0000000001
  s21_decimal val2 = {.bits = {1, 0, 0, 655360}};  // 0.0000000001
  s21_decimal result;
  int status = s21_mul(val1, val2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 1);  // {1, 0, 0, 1310720}
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_s21_mul_13) {
  s21_decimal val1 = {.bits = {1, 0, 0, 655360}};       // 0.0000000001
  s21_decimal val2 = {.bits = {1, 0, 0, -2146828288}};  // -0.0000000001
  s21_decimal result;
  int status = s21_mul(val1, val2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 1);  // {1, 0, 0, -2146172928}
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_s21_mul_14) {
  s21_decimal val1 = {.bits = {1, 0, 1, 917504}};       // 184467.44073709551617
  s21_decimal val2 = {.bits = {1, 0, 0, -2146828288}};  // -0.0000000001
  s21_decimal result;
  int status = s21_mul(val1, val2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 1);  // {1, 0, 1, -2145910784}
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 1);
}
END_TEST

// div
START_TEST(test_s21_div_1) {
  s21_decimal value_1 = {.bits = {15, 0, 0, 0}};
  s21_decimal value_2 = {.bits = {3, 0, 0, 0}};
  s21_decimal result;
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 5);
}
END_TEST

START_TEST(test_s21_div_2) {
  s21_decimal value_1 = {.bits = {0, 0, 0, 0}};
  s21_decimal value_2 = {.bits = {5, 0, 0, 0}};
  s21_decimal result;
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
}
END_TEST

START_TEST(test_s21_div_3) {  // Деление на 0
  s21_decimal value_1 = {.bits = {5, 0, 0, 0}};
  s21_decimal value_2 = {.bits = {0, 0, 0, 0}};
  s21_decimal result;
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(status, 3);
}
END_TEST

START_TEST(test_s21_div_4) {
  s21_decimal value_1 = {.bits = {10, 0, 0, 0}};
  s21_decimal value_2 = {.bits = {2, 0, 0, 0}};
  s21_decimal result;
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 5);
}
END_TEST

START_TEST(test_s21_div_6) {
  s21_decimal value_1 = {.bits = {10, 0, 0, 0x80000000}};
  s21_decimal value_2 = {.bits = {2, 0, 0, 0x80000000}};
  s21_decimal result;
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 5);
}
END_TEST

START_TEST(test_s21_div_8) {
  s21_decimal value_1 = {.bits = {0, 0, 0, 0}};
  s21_decimal value_2 = {.bits = {5, 0, 0, 0x80000000}};
  s21_decimal result;
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
}
END_TEST

START_TEST(test_s21_div_11) {
  s21_decimal val1 = {.bits = {1, 1, 1, 655360}};  // 1844674407.8004518913
  s21_decimal val2 = {.bits = {1, 1, 1, 655360}};  // 1844674407.8004518913
  s21_decimal result;
  int status = s21_div(val1, val2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 1);  // {1, 0, 0, 0}
}
END_TEST

START_TEST(test_s21_div_12) {
  s21_decimal val1 = {.bits = {1, 1, 1, 655360}};  // 1844674407.8004518913
  s21_decimal val2 = {.bits = {1, 1, 1, 655360}};  // 1844674407.8004518913
  s21_decimal result;
  int status = s21_div(val2, val1, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 1);  // {1, 0, 0, 0}
}
END_TEST

START_TEST(test_s21_div_14) {
  s21_decimal val1 = {.bits = {1, 1, 1, 655360}};  // 1844674407.8004518913
  s21_decimal val2 = {.bits = {1, 1, 1, 983040}};  // 18446.744078004518913
  s21_decimal result;
  int status = s21_div(val2, val1, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 1);  // {1, 0, 0, 327680}
}
END_TEST

START_TEST(test_s21_div_15) {
  s21_decimal val1 = {.bits = {1, 1, 1, 655360}};  // 1844674407.8004518913
  s21_decimal val2 = {
      .bits = {1, 10, 1, -2146500608}};  // -18446.744116659224577
  s21_decimal result;
  int status = s21_div(val1, val2, &result);
  ck_assert_int_eq(status, 0);
  // {1019311944, 458670364, 542101085, -2145976320}
}
END_TEST

START_TEST(test_s21_div_16) {
  s21_decimal val1 = {.bits = {1, 1, 1, 655360}};  // 1844674407.8004518913
  s21_decimal val2 = {
      .bits = {1, 10, 1, -2146500608}};  // -18446.744116659224577
  s21_decimal result;
  int status = s21_div(val2, val1, &result);
  ck_assert_int_eq(status, 0);
  // {260451598, 46702560, 5421, -2145648640}
}
END_TEST

START_TEST(test_s21_div_18) {
  s21_decimal val1 = {.bits = {1, 1, 1, 655360}};  // 1844674407.8004518913
  s21_decimal val2 = {
      .bits = {1, 10, 1, -2146500608}};  // -18446.744116659224577
  s21_decimal result;
  int status = s21_div(val2, val1, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 1);  // {1, 0, 0, -2147483648}
}
END_TEST

// is less

START_TEST(test_s21_is_less_1) {
  s21_decimal val1 = {.bits = {1, 2, 3, 655360}};  // 5534023222.9718589441
  s21_decimal val2 = {
      .bits = {3, 2, 1, -2146828288}};  // -1844674408.2299486211
  int result = s21_is_less(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_less_2) {
  s21_decimal val1 = {
      .bits = {1, 2, 3, -2146828288}};  // -5534023222.9718589441
  s21_decimal val2 = {
      .bits = {3, 2, 1, -2146828288}};  // -1844674408.2299486211
  int result = s21_is_less(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_less_3) {
  s21_decimal val1 = {
      .bits = {1, 2, 3, -2146566144}};  // -553402.32229718589441
  s21_decimal val2 = {
      .bits = {3, 2, 1, -2146959360}};  // -184467440822.99486211
  int result = s21_is_less(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_less_4) {
  s21_decimal val1 = {
      .bits = {10, 2, 3, -2146566144}};            // -553402.32229718589450
  s21_decimal val2 = {.bits = {3, 2, 1, 524288}};  // 184467440822.99486211
  int result = s21_is_less(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_less_5) {
  s21_decimal val1 = {.bits = {1, 2, 3, 917504}};  // 553402.32229718589441
  s21_decimal val2 = {.bits = {1, 2, 3, 917504}};  // 553402.32229718589441
  int result = s21_is_less(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

// is less or equal

START_TEST(test_s21_is_less_or_equal_1) {
  s21_decimal val1 = {.bits = {1, 2, 3, 655360}};  // 5534023222.9718589441
  s21_decimal val2 = {
      .bits = {3, 2, 1, -2146828288}};  // -1844674408.2299486211
  int result = s21_is_less_or_equal(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_less_or_equal_2) {
  s21_decimal val1 = {
      .bits = {1, 2, 3, -2146828288}};  // -5534023222.9718589441
  s21_decimal val2 = {
      .bits = {3, 2, 1, -2146828288}};  // -1844674408.2299486211
  int result = s21_is_less_or_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal_3) {
  s21_decimal val1 = {
      .bits = {1, 2, 3, -2146566144}};  // -553402.32229718589441
  s21_decimal val2 = {
      .bits = {3, 2, 1, -2146959360}};  // -184467440822.99486211
  int result = s21_is_less_or_equal(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_less_or_equal_4) {
  s21_decimal val1 = {
      .bits = {10, 2, 3, -2146566144}};            // -553402.32229718589450
  s21_decimal val2 = {.bits = {3, 2, 1, 524288}};  // 184467440822.99486211
  int result = s21_is_less_or_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal_5) {
  s21_decimal val1 = {.bits = {1, 2, 3, 917504}};  // 553402.32229718589441
  s21_decimal val2 = {.bits = {1, 2, 3, 917504}};  // 553402.32229718589441
  int result = s21_is_less_or_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

// is greater
START_TEST(test_s21_is_greater_1) {
  s21_decimal val1 = {.bits = {1, 2, 3, 655360}};  // 5534023222.9718589441
  s21_decimal val2 = {
      .bits = {3, 2, 1, -2146828288}};  // -1844674408.2299486211
  int result = s21_is_greater(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_greater_2) {
  s21_decimal val1 = {
      .bits = {1, 2, 3, -2146828288}};  // -5534023222.9718589441
  s21_decimal val2 = {
      .bits = {3, 2, 1, -2146828288}};  // -1844674408.2299486211
  int result = s21_is_greater(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_greater_3) {
  s21_decimal val1 = {
      .bits = {1, 2, 3, -2146566144}};  // -553402.32229718589441
  s21_decimal val2 = {
      .bits = {3, 2, 1, -2146959360}};  // -184467440822.99486211
  int result = s21_is_greater(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_greater_4) {
  s21_decimal val1 = {
      .bits = {10, 2, 3, -2146566144}};            // -553402.32229718589450
  s21_decimal val2 = {.bits = {3, 2, 1, 524288}};  // 184467440822.99486211
  int result = s21_is_greater(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_greater_5) {
  s21_decimal val1 = {.bits = {1, 2, 3, 917504}};  // 553402.32229718589441
  s21_decimal val2 = {.bits = {1, 2, 3, 917504}};  // 553402.32229718589441
  int result = s21_is_greater(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

// is greater or equal

START_TEST(test_s21_is_greater_or_equal_1) {
  s21_decimal val1 = {.bits = {1, 2, 3, 655360}};  // 5534023222.9718589441
  s21_decimal val2 = {
      .bits = {3, 2, 1, -2146828288}};  // -1844674408.2299486211
  int result = s21_is_greater_or_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_2) {
  s21_decimal val1 = {
      .bits = {1, 2, 3, -2146828288}};  // -5534023222.9718589441
  s21_decimal val2 = {
      .bits = {3, 2, 1, -2146828288}};  // -1844674408.2299486211
  int result = s21_is_greater_or_equal(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_3) {
  s21_decimal val1 = {
      .bits = {1, 2, 3, -2146566144}};  // -553402.32229718589441
  s21_decimal val2 = {
      .bits = {3, 2, 1, -2146959360}};  // -184467440822.99486211
  int result = s21_is_greater_or_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_4) {
  s21_decimal val1 = {
      .bits = {10, 2, 3, -2146566144}};            // -553402.32229718589450
  s21_decimal val2 = {.bits = {3, 2, 1, 524288}};  // 184467440822.99486211
  int result = s21_is_greater_or_equal(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_5) {
  s21_decimal val1 = {.bits = {1, 2, 3, 917504}};  // 553402.32229718589441
  s21_decimal val2 = {.bits = {1, 2, 3, 917504}};  // 553402.32229718589441
  int result = s21_is_greater_or_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

// is equal

START_TEST(test_s21_is_equal_1) {
  s21_decimal val1 = {.bits = {1, 2, 3, 655360}};  // 5534023222.9718589441
  s21_decimal val2 = {
      .bits = {3, 2, 1, -2146828288}};  // -1844674408.2299486211
  int result = s21_is_equal(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_equal_2) {
  s21_decimal val1 = {
      .bits = {1, 2, 3, -2146828288}};  // -5534023222.9718589441
  s21_decimal val2 = {
      .bits = {3, 2, 1, -2146828288}};  // -1844674408.2299486211
  int result = s21_is_equal(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_equal_3) {
  s21_decimal val1 = {
      .bits = {1, 2, 3, -2146566144}};  // -553402.32229718589441
  s21_decimal val2 = {
      .bits = {3, 2, 1, -2146959360}};  // -184467440822.99486211
  int result = s21_is_equal(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_equal_4) {
  s21_decimal val1 = {
      .bits = {10, 2, 3, -2146566144}};            // -553402.32229718589450
  s21_decimal val2 = {.bits = {3, 2, 1, 524288}};  // 184467440822.99486211
  int result = s21_is_equal(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_equal_5) {
  s21_decimal val1 = {.bits = {1, 2, 3, 917504}};  // 553402.32229718589441
  s21_decimal val2 = {.bits = {1, 2, 3, 917504}};  // 553402.32229718589441
  int result = s21_is_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

// is not equal

START_TEST(test_s21_is_not_equal_1) {
  s21_decimal val1 = {.bits = {1, 2, 3, 655360}};  // 5534023222.9718589441
  s21_decimal val2 = {
      .bits = {3, 2, 1, -2146828288}};  // -1844674408.2299486211
  int result = s21_is_not_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_not_equal_2) {
  s21_decimal val1 = {
      .bits = {1, 2, 3, -2146828288}};  // -5534023222.9718589441
  s21_decimal val2 = {
      .bits = {3, 2, 1, -2146828288}};  // -1844674408.2299486211
  int result = s21_is_not_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_not_equal_3) {
  s21_decimal val1 = {
      .bits = {1, 2, 3, -2146566144}};  // -553402.32229718589441
  s21_decimal val2 = {
      .bits = {3, 2, 1, -2146959360}};  // -184467440822.99486211
  int result = s21_is_not_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_not_equal_4) {
  s21_decimal val1 = {
      .bits = {10, 2, 3, -2146566144}};            // -553402.32229718589450
  s21_decimal val2 = {.bits = {3, 2, 1, 524288}};  // 184467440822.99486211
  int result = s21_is_not_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_not_equal_5) {
  s21_decimal val1 = {.bits = {1, 2, 3, 917504}};  // 553402.32229718589441
  s21_decimal val2 = {.bits = {1, 2, 3, 917504}};  // 553402.32229718589441
  int result = s21_is_not_equal(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

// from int to decimal
START_TEST(test_s21_from_int_to_decimal_1) {
  int src = 12345;
  s21_decimal dst;
  int result = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst.bits[0], 12345);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_2) {
  int src = 0;
  s21_decimal dst;
  int result = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst.bits[0], 0);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_3) {
  int src = -54321;
  s21_decimal dst;
  int result = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst.bits[0], 54321);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_4) {
  int src = INT_MAX;
  s21_decimal dst;
  int result = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst.bits[0], INT_MAX);
}
END_TEST

START_TEST(test_s21_from_int_to_decimal_5) {
  int src = INT_MIN;
  s21_decimal dst;
  int result = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst.bits[0], INT_MIN);
}
END_TEST

// from float to decimal
START_TEST(test_s21_from_float_to_decimal_1) {
  float src = 123.45f;
  s21_decimal dst;
  int result = s21_from_float_to_decimal(src, &dst);
  Bank_Round(&dst, 4);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(
      dst.bits[0],
      12345);  // Значение 123.45 представлено как 12345 с масштабом 2
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq((dst.bits[3] >> 16) & 0xFF, 2);  // Масштаб 2
  ck_assert_int_eq((dst.bits[3] >> 31) & 1, 0);  // Положительный знак
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_2) {
  float src = 0.0f;
  s21_decimal dst;
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst.bits[0], 0);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq((dst.bits[3] >> 16) & 0xFF, 0);  // Масштаб 0
  ck_assert_int_eq((dst.bits[3] >> 31) & 1, 0);  // Положительный знак
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_3) {
  float src = -543.21f;
  s21_decimal dst;
  int result = s21_from_float_to_decimal(src, &dst);
  Bank_Round(&dst, 4);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(
      dst.bits[0],
      54321);  // Значение 543.21 представлено как 54321 с масштабом 2
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq((dst.bits[3] >> 16) & 0xFF, 2);  // Масштаб 2
  ck_assert_int_eq((dst.bits[3] >> 31) & 1, 1);  // Отрицательный знак
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_4) {
  float src = 1e5f;
  s21_decimal dst;
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst.bits[0], 100000);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq((dst.bits[3] >> 16) & 0xFF, 0);  // Масштаб 0
  ck_assert_int_eq((dst.bits[3] >> 31) & 1, 0);  // Положительный знак
}
END_TEST

START_TEST(test_s21_from_float_to_decimal_5) {
  float src = 0.001f;
  s21_decimal dst;
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst.bits[0],
                   1);  // Значение 0.0001 представлено как 1 с масштабом 4
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq((dst.bits[3] >> 16) & 0xFF, 3);  // Масштаб 4
  ck_assert_int_eq((dst.bits[3] >> 31) & 1, 0);  // Положительный знак
}

// from decimal to int
START_TEST(test_s21_from_decimal_to_int_1) {
  s21_decimal src;
  int dst;
  src.bits[0] = 12345;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  int result = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst, 12345);
}
END_TEST

START_TEST(test_s21_from_decimal_to_int_2) {
  s21_decimal src;
  int dst;
  src.bits[0] = 0;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  int result = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst, 0);
}
END_TEST

// from decimal to float
START_TEST(test_s21_from_decimal_to_float_1) {
  s21_decimal src;
  src.bits[0] = 12345;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 2 << 16;  // Масштаб 2, знак положительный
  float dst;
  int result = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_float_eq(dst, 123.45f);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_2) {
  s21_decimal src;
  src.bits[0] = 0;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;  // Масштаб 0, знак положительный
  float dst;
  int result = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_float_eq(dst, 0.0f);
}
END_TEST

START_TEST(test_s21_from_decimal_to_float_5) {
  s21_decimal src;
  src.bits[0] = 1;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 4 << 16;  // Масштаб 4, знак положительный
  float dst;
  int result = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_float_eq(dst, 0.0001f);
}
END_TEST

START_TEST(test_s21_floor_1) {
  s21_decimal val1 = {.bits = {1, 2, 3, 917504}};  // 553402.32229718589441
  s21_decimal result;
  int status = s21_floor(val1, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 553402);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_floor_2) {
  s21_decimal val2 = {
      .bits = {1, 2, 3, -2146566144}};  // -553402.32229718589441
  s21_decimal result;
  int status = s21_floor(val2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 553403);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], -2147483648);
}
END_TEST

START_TEST(test_s21_floor_3) {
  s21_decimal val3 = {
      .bits = {33, 2, 3000, -2146107392}};  // -55.340232221137244782625
  s21_decimal result;
  int status = s21_floor(val3, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 56);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], -2147483648);
}
END_TEST

// round
START_TEST(test_s21_round_1) {
  s21_decimal val1 = {.bits = {1, 2, 3, 917504}};  // 553402.32229718589441
  s21_decimal result;
  int status = s21_round(val1, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 553402);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_round_2) {
  s21_decimal val2 = {
      .bits = {10, 100, 3, 1376256}};  // 0.055340232650625384458
  s21_decimal result;
  int status = s21_round(val2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_round_3) {
  s21_decimal val3 = {.bits = {16, 100, 3, 851968}};  // 5534023.2650625384464
  s21_decimal result;
  int status = s21_round(val3, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 5534023);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

// truncate
START_TEST(test_s21_truncate_1) {
  s21_decimal val1 = {.bits = {32444, 100, 343253,
                               -2145976320}};  // -63.31900243533454217608892
  s21_decimal result;
  int status = s21_truncate(val1, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 63);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], -2147483648);
}
END_TEST

START_TEST(test_s21_truncate_2) {
  s21_decimal val2 = {.bits = {1, 1, 1, 917504}};  // 184467.44078004518913
  s21_decimal result;
  int status = s21_truncate(val2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 184467);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_truncate_3) {
  s21_decimal val3 = {.bits = {0, 0, 0, 851968}};  // 0.0000000000000
  s21_decimal result;
  int status = s21_truncate(val3, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

// negate
START_TEST(test_s21_negate_1) {
  s21_decimal val1 = {.bits = {32444, 100, 343253,
                               -2145976320}};  // -63.31900243533454217608892
  s21_decimal result;
  int status = s21_negate(val1, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 32444);
  ck_assert_int_eq(result.bits[1], 100);
  ck_assert_int_eq(result.bits[2], 343253);
  ck_assert_int_eq(result.bits[3], 1507328);
}
END_TEST

START_TEST(test_s21_negate_2) {
  s21_decimal val2 = {.bits = {1, 1, 1, 917504}};  // 184467.44078004518913
  s21_decimal result;
  int status = s21_negate(val2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 1);
  ck_assert_int_eq(result.bits[2], 1);
  ck_assert_int_eq(result.bits[3], -2146566144);
}
END_TEST

START_TEST(test_s21_negate_3) {
  s21_decimal val3 = {.bits = {0, 0, 0, 917504}};  // 0.00000000000000
  s21_decimal result;
  int status = s21_negate(val3, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], -2146566144);
}
END_TEST

Suite *s21_add_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Decimal Function");
  tc_core = tcase_create("Core");

  // s21_add
  tcase_add_test(tc_core, test_s21_add_1);
  tcase_add_test(tc_core, test_s21_add_2);
  tcase_add_test(tc_core, test_s21_add_3);
  tcase_add_test(tc_core, test_s21_add_4);
  // tcase_add_test(tc_core, test_s21_add_5);
  // tcase_add_test(tc_core, test_s21_add_6);
  tcase_add_test(tc_core, test_s21_add_9);
  tcase_add_test(tc_core, test_s21_add_10);
  tcase_add_test(tc_core, test_s21_add_11);
  tcase_add_test(tc_core, test_s21_add_12);
  tcase_add_test(tc_core, test_s21_add_13);

  // s21_sub
  tcase_add_test(tc_core, test_s21_sub_1);
  tcase_add_test(tc_core, test_s21_sub_2);
  tcase_add_test(tc_core, test_s21_sub_3);
  tcase_add_test(tc_core, test_s21_sub_4);
  tcase_add_test(tc_core, test_s21_sub_5);
  tcase_add_test(tc_core, test_s21_sub_6);
  tcase_add_test(tc_core, test_s21_sub_7);
  tcase_add_test(tc_core, test_s21_sub_10);
  tcase_add_test(tc_core, test_s21_sub_11);
  tcase_add_test(tc_core, test_s21_sub_12);
  tcase_add_test(tc_core, test_s21_sub_13);
  tcase_add_test(tc_core, test_s21_sub_14);
  tcase_add_test(tc_core, test_s21_sub_15);

  // s21_mul
  tcase_add_test(tc_core, test_s21_mul_1);
  tcase_add_test(tc_core, test_s21_mul_2);
  tcase_add_test(tc_core, test_s21_mul_3);
  tcase_add_test(tc_core, test_s21_mul_4);
  tcase_add_test(tc_core, test_s21_mul_5);
  tcase_add_test(tc_core, test_s21_mul_6);
  tcase_add_test(tc_core, test_s21_mul_8);
  tcase_add_test(tc_core, test_s21_mul_9);
  tcase_add_test(tc_core, test_s21_mul_10);
  tcase_add_test(tc_core, test_s21_mul_12);
  tcase_add_test(tc_core, test_s21_mul_13);
  tcase_add_test(tc_core, test_s21_mul_14);
  // tcase_add_test(tc_core, test_s21_mul_15);

  // s21_div
  tcase_add_test(tc_core, test_s21_div_1);
  tcase_add_test(tc_core, test_s21_div_2);
  tcase_add_test(tc_core, test_s21_div_3);
  tcase_add_test(tc_core, test_s21_div_4);
  tcase_add_test(tc_core, test_s21_div_6);
  tcase_add_test(tc_core, test_s21_div_8);
  tcase_add_test(tc_core, test_s21_div_11);
  tcase_add_test(tc_core, test_s21_div_12);
  tcase_add_test(tc_core, test_s21_div_14);
  tcase_add_test(tc_core, test_s21_div_15);
  tcase_add_test(tc_core, test_s21_div_16);
  tcase_add_test(tc_core, test_s21_div_18);

  // s21_is_less
  tcase_add_test(tc_core, test_s21_is_less_1);
  tcase_add_test(tc_core, test_s21_is_less_2);
  tcase_add_test(tc_core, test_s21_is_less_3);
  tcase_add_test(tc_core, test_s21_is_less_4);
  tcase_add_test(tc_core, test_s21_is_less_5);

  // s21_is_less_or_equal
  tcase_add_test(tc_core, test_s21_is_less_or_equal_1);
  tcase_add_test(tc_core, test_s21_is_less_or_equal_2);
  tcase_add_test(tc_core, test_s21_is_less_or_equal_3);
  tcase_add_test(tc_core, test_s21_is_less_or_equal_4);
  tcase_add_test(tc_core, test_s21_is_less_or_equal_5);

  // s21_is_greater
  tcase_add_test(tc_core, test_s21_is_greater_1);
  tcase_add_test(tc_core, test_s21_is_greater_2);
  tcase_add_test(tc_core, test_s21_is_greater_3);
  tcase_add_test(tc_core, test_s21_is_greater_4);
  tcase_add_test(tc_core, test_s21_is_greater_5);

  // s21_is_greater_or_equal
  tcase_add_test(tc_core, test_s21_is_greater_or_equal_1);
  tcase_add_test(tc_core, test_s21_is_greater_or_equal_2);
  tcase_add_test(tc_core, test_s21_is_greater_or_equal_3);
  tcase_add_test(tc_core, test_s21_is_greater_or_equal_4);
  tcase_add_test(tc_core, test_s21_is_greater_or_equal_5);

  // s21_is_equal
  tcase_add_test(tc_core, test_s21_is_equal_1);
  tcase_add_test(tc_core, test_s21_is_equal_2);
  tcase_add_test(tc_core, test_s21_is_equal_3);
  tcase_add_test(tc_core, test_s21_is_equal_4);
  tcase_add_test(tc_core, test_s21_is_equal_5);

  // s21_is_not_equal
  tcase_add_test(tc_core, test_s21_is_not_equal_1);
  tcase_add_test(tc_core, test_s21_is_not_equal_2);
  tcase_add_test(tc_core, test_s21_is_not_equal_3);
  tcase_add_test(tc_core, test_s21_is_not_equal_4);
  tcase_add_test(tc_core, test_s21_is_not_equal_5);

  // s21_from_int_to_decimal
  tcase_add_test(tc_core, test_s21_from_int_to_decimal_1);
  tcase_add_test(tc_core, test_s21_from_int_to_decimal_2);
  tcase_add_test(tc_core, test_s21_from_int_to_decimal_3);
  tcase_add_test(tc_core, test_s21_from_int_to_decimal_4);
  tcase_add_test(tc_core, test_s21_from_int_to_decimal_5);

  // s21_from_float_to_decimal
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_1);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_2);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_3);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_4);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal_5);

  // s21_from_decimal_to_int
  tcase_add_test(tc_core, test_s21_from_decimal_to_int_1);
  tcase_add_test(tc_core, test_s21_from_decimal_to_int_2);

  // s21_from_decimal_to_float
  tcase_add_test(tc_core, test_s21_from_decimal_to_float_1);
  tcase_add_test(tc_core, test_s21_from_decimal_to_float_2);
  tcase_add_test(tc_core, test_s21_from_decimal_to_float_5);

  // s21_floor
  tcase_add_test(tc_core, test_s21_floor_1);
  tcase_add_test(tc_core, test_s21_floor_2);
  tcase_add_test(tc_core, test_s21_floor_3);

  // s21_round
  tcase_add_test(tc_core, test_s21_round_1);
  tcase_add_test(tc_core, test_s21_round_2);
  tcase_add_test(tc_core, test_s21_round_3);

  // s21_truncate
  tcase_add_test(tc_core, test_s21_truncate_1);
  tcase_add_test(tc_core, test_s21_truncate_2);
  tcase_add_test(tc_core, test_s21_truncate_3);

  // s21_negate
  tcase_add_test(tc_core, test_s21_negate_1);
  tcase_add_test(tc_core, test_s21_negate_2);
  tcase_add_test(tc_core, test_s21_negate_3);

  suite_add_tcase(s, tc_core);
  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = s21_add_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? 0 : 1;
}
