#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = OK;
  if (result == NULL) {
    res = 1;
  } else {
    big_decimal tmp_1 = to_big(value_1);
    big_decimal tmp_2 = to_big(value_2);
    big_decimal tmp_res = to_big(*result);
    normalization(&tmp_1, &tmp_2);
    if (check_sign(tmp_1.bits[7]) == check_sign(tmp_2.bits[7])) {
      tmp_res = big_plus_big(tmp_1, tmp_2);
      set_sign(&(tmp_res.bits[7]), check_sign(tmp_1.bits[7]));
    } else {
      if (big_mantissa_is_greater_or_equal(tmp_1, tmp_2)) {
        tmp_res = big_minus_big(tmp_1, tmp_2);
        set_sign(&(tmp_res.bits[7]), check_sign(tmp_1.bits[7]));
      } else if (big_mantissa_is_less(tmp_1, tmp_2)) {
        tmp_res = big_minus_big(tmp_2, tmp_1);
        set_sign(&(tmp_res.bits[7]), check_sign(tmp_2.bits[7]));
      }
    }
    set_scale(&result->bits[3], get_scale(tmp_1.bits[7]));
    res = can_convert(tmp_res);
    if (res == OK) {
      *result = from_big(tmp_res);
    }
  }
  return res;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  set_sign(&(value_2.bits[3]), check_sign(value_2.bits[3]) ? 0 : 1);
  return s21_add(value_1, value_2, result);
}