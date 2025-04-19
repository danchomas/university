#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  big_decimal big_value = to_big(value);
  bool source_sign = check_sign(value.bits[3]);
  int scale = get_scale(big_value.bits[7]);
  if (scale > 0) {
    for (int i = 0; i < scale; i++) {
      big_div10(big_value, &big_value);
    }
  }
  set_scale(&big_value.bits[7], 0);
  *result = from_big(big_value);
  set_sign(&result->bits[3], source_sign);
  return OK;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  *result = value;
  set_sign(&result->bits[3], !check_sign(result->bits[3]));
  return OK;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  bool sign = check_sign(value.bits[3]);
  int error = s21_truncate(value, result);
  if (error == OK) {
    s21_decimal sub_res = {0};
    error = s21_sub(value, *result, &sub_res);
    if (error == OK) {
      if (sign &&
          !(sub_res.bits[0] == sub_res.bits[1] &&
            sub_res.bits[1] == sub_res.bits[2] && sub_res.bits[2] == 0)) {
        error = s21_sub(*result, ((s21_decimal){{1, 0, 0, 0}}), result);
      }
    }
  }
  return error;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  bool sign = check_sign(value.bits[3]);
  int error = s21_truncate(value, result);
  if (error == OK) {
    s21_decimal sub_res = {0};
    error = s21_sub(value, *result, &sub_res);
    if (error == OK) {
      if (sub_res.bits[0] != 0 || sub_res.bits[1] != 0 ||
          sub_res.bits[2] != 0) {
        big_decimal big_ostatok = to_big(sub_res);
        big_decimal pol_litra = {{5, 0, 0, 0, 0, 0, 0, 1 << 16}};
        normalization(&big_ostatok, &pol_litra);
        if (big_mantissa_is_equal(big_ostatok, pol_litra) ||
            big_mantissa_is_greater(big_ostatok, pol_litra)) {
          if (sign == false) {
            s21_add(*result, ((s21_decimal){{1, 0, 0, 0}}), result);
          } else {
            s21_sub(*result, ((s21_decimal){{1, 0, 0, 0}}), result);
          }
        }
      }
    }
  }
  return error;
}