#include <limits.h>

#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = OK;
  if (result) {
    bool result_sign =
        check_sign(value_1.bits[3]) ^ check_sign(value_2.bits[3]);
    int result_exponent =
        get_scale(value_1.bits[3]) + get_scale(value_2.bits[3]);

    big_decimal temp_result = {{0}};
    unsigned long long overflow_word = 0;
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        unsigned long long temp =
            (unsigned long long)value_1.bits[i] * value_2.bits[j] +
            overflow_word + temp_result.bits[i + j];
        temp_result.bits[i + j] = temp & UINT_MAX;
        overflow_word = temp >> 32;
      }
      temp_result.bits[i + 3] += overflow_word;
      overflow_word = 0;
    }

    set_scale(&temp_result.bits[7], result_exponent);
    set_sign(&temp_result.bits[7], result_sign);
    res = can_convert(temp_result);
    if (res == OK) {
      *result = from_big(temp_result);
    }
  } else
    res = 1;
  return res;
}