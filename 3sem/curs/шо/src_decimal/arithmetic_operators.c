#include "s21_decimal.h"

void Normalize(s21_decimal* num1, s21_decimal* num2) {
  int scale1 = Get_Scale(*num1);
  int scale2 = Get_Scale(*num2);

  int temp1 = num1->bits[SCALE];
  int temp2 = num2->bits[SCALE];

  int min_scale = (scale1 < scale2) ? scale1 : scale2;
  int max_scale = (scale1 > scale2) ? scale1 : scale2;

  s21_decimal* min_value = (scale1 < scale2) ? num1 : num2;
  s21_decimal* max_value = (scale1 > scale2) ? num1 : num2;
  s21_decimal ten;

  s21_from_int_to_decimal(10, &ten);

  while (min_scale != max_scale) {
    if (min_scale < MAX_POWER && !Simple_Mul(*min_value, ten, min_value)) {
      min_scale++;

      Set_Scale(min_value, min_scale);

    } else {
      Bank_Round(max_value, max_scale - min_scale);

      break;
    }
  }

  num1->bits[SCALE] = temp1;
  num2->bits[SCALE] = temp2;

  Set_Scale(min_value, min_scale);
  Set_Scale(max_value, min_scale);
}

int s21_add(s21_decimal value1, s21_decimal value2, s21_decimal* result) {
  ARITHMETHIC_RES res = ARITHMETHIC_OK;

  Normalize(&value1, &value2);

  int scale1 = Get_Scale(value1);
  int sign1 = Get_Sign(value1);
  int sign2 = Get_Sign(value2);

  if (!(sign1 ^ sign2)) {
    res = Simple_Add(value1, value2, result);

    Set_Sign(result, sign1);

    if (res) {
      if (sign1)
        res = ARITHMETHIC_SMALL_INFINITY;

      else
        res = ARITHMETHIC_BIG_INFINITY;
    }
  } else if (Simple_Is_Less_Or_Equal(value1, value2)) {
    Simple_Sub(value2, value1, result);
    Set_Sign(result, sign2);
  } else {
    Simple_Sub(value1, value2, result);
    Set_Sign(result, sign1);
  }

  if (res && scale1 > 0) {
    Bank_Round(&value1, 1);
    Bank_Round(&value2, 1);

    res = s21_add(value1, value2, result);

  } else
    Set_Scale(result, scale1);

  return res;
}

int s21_sub(s21_decimal value1, s21_decimal value2, s21_decimal* result) {
  ARITHMETHIC_RES res = ARITHMETHIC_OK;

  Set_Sign(&value2, !Get_Sign(value2));

  res = s21_add(value1, value2, result);

  return res;
}

int s21_mul(s21_decimal value1, s21_decimal value2, s21_decimal* result) {
  ARITHMETHIC_RES res = Simple_Mul(value1, value2, result);

  return res;
}

int s21_div(s21_decimal value1, s21_decimal value2, s21_decimal* result) {
  s21_decimal null_decimal = {0};

  if (s21_is_equal(value2, null_decimal)) return ARITHMETHIC_ZERO_DIV;

  Simple_Div(value1, value2, result);

  return ARITHMETHIC_OK;
}
