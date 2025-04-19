#include <limits.h>
#include <math.h>
#include <string.h>

#include "s21_decimal.h"

s21_decimal increase_scale_to_zero(s21_decimal src, int *source_scale,
                                   bool *res);

s21_decimal decrease_scale_to_zero(s21_decimal src, int *source_scale,
                                   bool *res);

int is_nan(float src);

int is_inf(float src);

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  bool res = OK;
  if (dst) {
    for (int i = 0; i < 4; i++) {
      dst->bits[i] = 0;
    }
    if (src < 0) {
      bool result_sign = CONVERT_ERROR;
      set_sign(&dst->bits[3], result_sign);
      src = -src;
    }
    dst->bits[0] = src;
  } else
    res = CONVERT_ERROR;

  return res;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  bool res = OK;
  bool scale_sign = OK;
  int source_scale = 0;
  char string_source[16] = {0};
  if (is_inf(src) || is_nan(src) || !dst) {
    res = CONVERT_ERROR;
  }
  if (!res) {
    snprintf(string_source, 16, "%e", src);
    for (int i = 0; string_source[i]; i++) {
      if (string_source[i] == '-') {
        bool result_sign = true;
        set_sign(&dst->bits[3], result_sign);
        i++;
      }
      if (string_source[i] != 'e' && string_source[i] != '.') {
        dst->bits[0] = dst->bits[0] * 10 + (string_source[i] - '0');
      } else if (string_source[i] == 'e') {
        i++;
        if (string_source[i] == '-') {
          scale_sign = true;
        }
        i++;
        if ((string_source[i] >= '0' && string_source[i] <= '9')) {
          source_scale = (string_source[i] - '0') * 10;
          i++;
          source_scale += (string_source[i] - '0');
          i++;
        }
      }
    }
    if (!scale_sign) source_scale = -source_scale;
    source_scale += 6;
    *dst = increase_scale_to_zero(*dst, &source_scale, &res);
    *dst = decrease_scale_to_zero(*dst, &source_scale, &res);
    if (dst->bits[2] == 0 && dst->bits[1] == 0 && dst->bits[0] == 0 &&
        source_scale > 0) {
      res = CONVERT_ERROR;
    }
    if (source_scale >= 0 && source_scale <= 28) {
      set_scale(&dst->bits[3], source_scale);
    } else {
      res = CONVERT_ERROR;
      for (int i = 0; i < 4; i++) dst->bits[i] = 0;
    }
  }
  return res;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  bool res = OK;
  if (dst) {
    bool source_sign = check_sign(src.bits[3]);
    unsigned int exponent = get_scale(src.bits[3]);
    if (exponent > 28) res = CONVERT_ERROR;

    for (int i = exponent; i > 0; --i) {
      unsigned long long int temp = src.bits[2] % 10;
      src.bits[2] /= 10;

      temp = (temp << 32) | src.bits[1];
      src.bits[1] = temp / 10;

      temp = ((temp % 10) << 32) | src.bits[0];
      src.bits[0] = temp / 10;
    }

    if (src.bits[2] != 0 || src.bits[1] != 0 ||
        src.bits[0] > (unsigned)(INT_MAX + source_sign)) {
      res = CONVERT_ERROR;
      *dst = 0;
    }

    *dst = source_sign ? -src.bits[0] : src.bits[0];
  } else
    res = CONVERT_ERROR;
  return res;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  bool res = OK;
  if (dst) {
    double temp_result = 0.0;
    for (int i = 0; i < 3; i++) {
      temp_result += (double)(src.bits[i]) * pow(2, 32 * i);
    }
    int source_scale = get_scale(src.bits[3]);
    temp_result *= pow(10, -source_scale);
    if (check_sign(src.bits[3])) temp_result *= -1;
    *dst = (float)temp_result;
  } else
    res = CONVERT_ERROR;
  return res;
}

s21_decimal increase_scale_to_zero(s21_decimal src, int *source_scale,
                                   bool *res) {
  while (*source_scale < 0 && !(*res)) {
    s21_decimal multiplier = {{10, 0, 0, 0}};
    *res = s21_mul(src, multiplier, &src);
    (*source_scale)++;
  }
  return src;
}

s21_decimal decrease_scale_to_zero(s21_decimal src, int *source_scale,
                                   bool *res) {
  big_decimal temp = to_big(src);
  big_decimal remainder = {{0}};
  big_decimal junk = {{0}};

  while (*source_scale > 28) {
    remainder = big_div10(temp, &temp);
    if (temp.bits[2] == 0 && temp.bits[1] == 0 && temp.bits[0] == 0) {
      *res = CONVERT_ERROR;
    } else if (remainder.bits[0] > 5) {
      temp.bits[0]++;
    }
    (*source_scale)--;
  }

  remainder = big_div10(temp, &junk);
  while ((*source_scale > 0) && (remainder.bits[0] == 0)) {
    remainder = big_div10(temp, &temp);
    (*source_scale)--;
  }

  for (int i = 0; i < 3; i++) {
    src.bits[i] = temp.bits[i];
  }

  return src;
}

int is_nan(float src) {
  union {
    float source;
    unsigned int bits;
  } temp;
  temp.source = src;
  return ((temp.bits & 0x7F800000) == 0x7F800000) &&
         (temp.bits & 0x007FFFFF) != 0;
}

int is_inf(float src) {
  union {
    float source;
    unsigned int bits;
  } temp;
  temp.source = src;
  return ((temp.bits & 0x7F800000) == 0x7F800000) &&
         (temp.bits & 0x007FFFFF) == 0;
}