#include "s21_decimal.h"

int s21_is_less(s21_decimal num1, s21_decimal num2) {
  int res;
  int sign_1 = Get_Sign(num1);
  int sign_2 = Get_Sign(num2);

  if (!sign_1 && !sign_2) {
    Normalize(&num1, &num2);
    res = Simple_Is_Less(num1, num2);
  } else if (sign_1 ^ sign_2) {
    res = (sign_1) ? TRUE : FALSE;
  } else {
    Normalize(&num1, &num2);
    res = !Simple_Is_Less(num1, num2);
  }

  return res;
}

int s21_is_equal(s21_decimal num1, s21_decimal num2) {
  int res;
  int sign_1 = Get_Sign(num1);
  int sign_2 = Get_Sign(num2);

  s21_decimal null_decimal;
  s21_from_int_to_decimal(0, &null_decimal);

  if (sign_1 ^ sign_2) {
    res = FALSE;
    if (Simple_Is_Equal(num1, null_decimal) &&
        Simple_Is_Equal(num2, null_decimal)) {
      res = TRUE;
    }
  } else {
    Normalize(&num1, &num2);
    res = Simple_Is_Equal(num1, num2);
  }

  return res;
}

int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2) {
  return s21_is_less(num1, num2) || s21_is_equal(num1, num2);
}

int s21_is_greater(s21_decimal num1, s21_decimal num2) {
  return !s21_is_less_or_equal(num1, num2);
}

int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2) {
  return s21_is_greater(num1, num2) || s21_is_equal(num1, num2);
}

int s21_is_not_equal(s21_decimal num1, s21_decimal num2) {
  return !s21_is_equal(num1, num2);
}