#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  Init_Decimal_Num(dst);

  dst->bits[LOW_BIT] = (src >= 0) ? src : -src;

  Set_Sign(dst, src < 0);

  return OK;
}

static int count_str_float(float src, char *str_src) {
  int count_str = 0, flag = 1;
  char str[BUFF_SIZE];

  snprintf(str, sizeof(str), "%f", src);

  for (int i = (int)strlen(str) - 1; i >= 0; i--) {
    if (str[i] == '0' && flag == 1) {
      str[i] = '\0';
      continue;
    } else
      flag = -1;

    if (str[i] == '.') break;

    count_str++;
  }

  strncpy(str_src, str, strlen(str) + 1);

  return count_str;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  Init_Decimal_Num(dst);

  if (fabsf(src) < 1e-28 && fabsf(src) > 0) return ERROR;

  char str_src[BUFF_SIZE];
  int count_str = count_str_float(src, str_src), is_overfull = 0;

  s21_decimal ten;
  s21_from_int_to_decimal(10, &ten);

  for (size_t i = 0; i < strlen(str_src); i++) {
    if (str_src[i] != '.' && str_src[i] != '-') {
      s21_decimal add;
      s21_from_int_to_decimal(str_src[i] - '0', &add);
      Simple_Add(*dst, add, dst);
      is_overfull = s21_mul(*dst, ten, dst);
    }
  }

  if (!is_overfull) Simple_Div(*dst, ten, dst);

  Set_Sign(dst, src < 0);
  Set_Scale(dst, count_str);

  return OK;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (!dst) return ERROR;

  int exp = Get_Scale(src);

  s21_decimal ten;
  s21_from_int_to_decimal(10, &ten);

  while (exp > 0) {
    Simple_Div(src, ten, &src);
    exp--;
  }

  Set_Bit(&src, HIGHEST_BIT_IN_32_BIT_PART, 0);

  *dst = src.bits[LOW_BIT];
  int sign = (Get_Sign(src)) ? -1 : 1;
  *dst *= sign;

  return OK;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int sign_flag = Get_Sign(src);
  long double temp = 0;

  s21_decimal res = {0}, ten = {0};

  s21_from_int_to_decimal(10, &ten);
  s21_truncate(src, &res);

  int sign;

  for (int i = 0; i < MAX_HIGHT_BIT + 1; i++) {
    sign = Get_Bit(res, i);
    temp += sign * pow(2, i);
  }

  s21_decimal float_part = {0};
  s21_sub(src, res, &float_part);

  int scale = Get_Scale(src);
  long double lf_part = 0;
  int count = 0;

  for (int i = 0; i < MAX_HIGHT_BIT + 1; i++) {
    sign = Get_Bit(float_part, i);
    count++;
    lf_part += sign * pow(2, i);
  }

  *dst = lf_part / pow(10, scale) + temp;

  if (sign_flag) *dst = -(*dst);

  return OK;
}
