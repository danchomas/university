#include "s21_decimal.h"

big_decimal big_div_big(big_decimal divisible, big_decimal divider,
                        big_decimal *result) {
  big_decimal remainder = {{0, 0, 0, 0, 0, 0, 0, 0}};
  int delta = get_width(divisible) + 1;
  for (int i = 0; i < 7; i++) {
    result->bits[i] = 0;
  }
  while (delta) {
    remainder = shift_big_decimal(remainder, 1, 'L');
    set_bit(&remainder, 0, check_bit(divisible, --delta));

    if (big_mantissa_is_greater_or_equal(remainder, divider)) {
      remainder = big_minus_big(remainder, divider);
      *result = shift_big_decimal(*result, 1, 'L');
      set_bit(result, 0, 1);
    } else {
      *result = shift_big_decimal(*result, 1, 'L');
    }
  }
  return remainder;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  big_decimal divisible = to_big(value_1);
  big_decimal divider = to_big(value_2);
  big_decimal tmp_res = {{0, 0, 0, 0, 0, 0, 0, 0}};
  int res = OK;
  if (!is_not_null(divisible) && is_not_null(divider)) {
    res = TOO_BIG;
  } else if (!is_not_null(divider)) {
    res = DIV_BY_ZERO;
  } else if (result == NULL) {
    res = 1;
  } else {
    int width_1 = 0;
    int width_2 = 0;
    while ((width_2 > width_1 || big_mantissa_is_less(divisible, divider)) &&
           get_scale(divisible.bits[7]) < 35) {
      divisible = big_x10(divisible);
      set_scale(&divisible.bits[7], (get_scale(divisible.bits[7]) + 1));
      width_1 = get_width(divisible);
    }
    int scale = get_scale(divisible.bits[7]);
    while (is_not_null(big_div_big(divisible, divider, &tmp_res)) &&
           scale < 35) {
      divisible = big_x10(divisible);
      scale++;
      set_scale(&(divisible.bits[7]), scale);
    }

    scale = get_scale(divisible.bits[7]) - get_scale(divider.bits[7]);
    if (scale >= 0) {
      set_scale(&(tmp_res.bits[7]), scale);
    } else {
      while (scale++ < 0) tmp_res = big_x10(tmp_res);
    }
    if (check_sign(value_1.bits[3]) == check_sign(value_2.bits[3])) {
      set_sign(&(tmp_res.bits[7]), 0);
    } else {
      set_sign(&(tmp_res.bits[7]), 1);
    }
    res = can_convert(tmp_res);
    if (res == OK) {
      *result = from_big(tmp_res);
    }
  }
  return res;
}