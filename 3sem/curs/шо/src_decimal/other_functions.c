#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_decimal base = {0}, zero = {0}, one = {0};

  s21_from_int_to_decimal(10, &base);
  s21_from_int_to_decimal(0, &zero);
  s21_from_int_to_decimal(1, &one);

  int sign = Get_Sign(value);
  s21_truncate(value, result);

  if (sign == 1 && !s21_is_equal(value, *result))
    Simple_Add(*result, one, result);

  Set_Sign(result, sign);
  return OK;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  s21_decimal base = {0}, mul = {0}, one = {0};

  s21_decimal value_copy = value;
  s21_truncate(value, result);
  s21_from_int_to_decimal(10, &base);
  s21_from_int_to_decimal(1, &one);

  int sign = Get_Sign(value);
  int scale = Get_Scale(value);

  if (scale != 0) scale--;
  while (scale != 0) {
    s21_div(value, base, &value);
    scale--;
  }
  mul = Simple_Div(value, base, &value);

  if (mul.bits[LOW_BIT] >= 5 && !s21_is_equal(value_copy, *result))
    Simple_Add(*result, one, result);

  Set_Sign(result, sign);

  return OK;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  s21_decimal base = {0};
  *result = value;

  int sign = Get_Sign(value);
  int scale = Get_Scale(value);

  s21_from_int_to_decimal(10, &base);

  while (scale != 0) {
    Simple_Div(*result, base, result);
    scale--;
  }

  Set_Sign(result, sign);

  return OK;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  *result = value;

  Set_Sign(result, !Get_Sign(value));

  return OK;
}
