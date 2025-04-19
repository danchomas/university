#include "s21_decimal.h"

int compare_decimals(s21_decimal value_1, s21_decimal value_2) {
  int sign1 = check_sign(value_1.bits[3]);
  int sign2 = check_sign(value_2.bits[3]);
  big_decimal big_value_1 = to_big(value_1);
  big_decimal big_value_2 = to_big(value_2);
  normalization(&big_value_1, &big_value_2);
  int comparison_result = 0;
  if (sign1 != sign2) {
    comparison_result = (sign1 > sign2) ? -1 : 1;
  } else {
    int mantissa_comparison = big_mantissa_compare(big_value_1, big_value_2);
    if (sign1 == 1) {
      mantissa_comparison = -mantissa_comparison;
    }
    comparison_result = mantissa_comparison;
  }
  return comparison_result;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  return compare_decimals(value_1, value_2) == 0;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return compare_decimals(value_1, value_2) != 0;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  return compare_decimals(value_1, value_2) > 0;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  return compare_decimals(value_1, value_2) < 0;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return compare_decimals(value_1, value_2) <= 0;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return compare_decimals(value_1, value_2) >= 0;
}
