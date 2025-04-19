#include "s21_decimal.h"

big_decimal big_plus_big(big_decimal value_1, big_decimal value_2) {
  big_decimal result = {{0, 0, 0, 0, 0, 0, 0, 0}};
  int memory = 0, sum = 0;
  for (int i = 0; i < 32 * 7; i++) {
    sum = check_bit(value_1, i) + check_bit(value_2, i) + memory;
    memory = sum > 1 ? 1 : 0;
    set_bit(&result, i, sum % 2);
  }
  result.bits[7] = value_1.bits[7];
  return result;
}

bool check_bit(big_decimal a, int num) {
  return (a.bits[num / 32] >> (num % 32)) & 1;
}

void set_bit(big_decimal *a, int num, int choice) {
  a->bits[num / 32] = choice ? a->bits[num / 32] | (1 << (num % 32))
                             : a->bits[num / 32] & ~(1 << (num % 32));
}

bool check_sign(unsigned value) { return (value >> 31) & 1; }

void set_sign(unsigned *value, bool choice) {
  *value = choice ? *value | (choice << 31) : *value & ~(1 << 31);
}

int get_scale(unsigned value) { return (value >> 16) & 255; }

void set_scale(unsigned *value, int num) {
  *value = (*value & (1 << 31)) | num << 16;
}

bool is_not_null(big_decimal a) {
  return (a.bits[0] == a.bits[1] && a.bits[0] == a.bits[2] &&
          a.bits[0] == a.bits[3] && a.bits[0] == a.bits[4] &&
          a.bits[0] == a.bits[5] && a.bits[0] == a.bits[6] && a.bits[0] == 0)
             ? false
             : true;
}

big_decimal shift_big_decimal(big_decimal a, int value, char vector) {
  unsigned memory = 0, tmp = 0;
  while (value > 0) {
    if (vector == 'L') {
      for (int i = 0; i < 7; i++) {
        tmp = a.bits[i];
        a.bits[i] <<= (value > 31 ? 31 : value);
        a.bits[i] |= memory;
        memory = tmp >> (32 - (value > 31 ? 31 : value));
      }
    } else if (vector == 'R') {
      for (int i = 6; i >= 0; i--) {
        tmp = a.bits[i];
        a.bits[i] >>= (value > 31 ? 31 : value);
        a.bits[i] |= memory;
        memory = tmp << (32 - (value > 31 ? 31 : value));
      }
    }
    value -= 31;
  }
  return a;
}

big_decimal to_big(s21_decimal a) {
  big_decimal b = {{0, 0, 0, 0, 0, 0, 0, 0}};
  for (int i = 0; i < 3; i++) b.bits[i] = a.bits[i];
  b.bits[7] = a.bits[3];
  return b;
}

int is_overflow(big_decimal value) {
  bool ret = false;
  for (int i = 3; i < 7; i++) {
    if (value.bits[i] != 0) {
      ret = true;
    }
  }
  return ret;
}

int can_convert(big_decimal value) {
  int ret = OK;
  bool sign = check_sign(value.bits[7]);
  set_sign(&value.bits[7], false);
  int scale = get_scale(value.bits[7]);
  // if overflow
  while (scale > 0 && is_overflow(value)) {
    big_decimal reminader = big_div10(value, &value);
    big_decimal pol_litra = {{5, 0, 0, 0, 0, 0, 0, 0}};
    if (big_mantissa_is_equal(reminader, pol_litra)) {
      if (value.bits[0] & 1) {
        value = big_plus_big(value, (big_decimal){{1, 0, 0, 0, 0, 0, 0, 0}});
      }
    } else if (big_mantissa_is_greater(reminader, pol_litra)) {
      value = big_plus_big(value, (big_decimal){{1, 0, 0, 0, 0, 0, 0, 0}});
    }
    scale--;
  }
  if (is_overflow(value)) {
    if (sign) {
      ret = TOO_LITTLE;
    } else {
      ret = TOO_BIG;
    }
  }
  return ret;
}

s21_decimal from_big(big_decimal a) {
  bool sign = check_sign(a.bits[7]);
  set_sign(&a.bits[7], false);
  s21_decimal b = {0};
  int scale = get_scale(a.bits[7]);
  // if overflow
  while ((scale > 0 && is_overflow(a)) || scale > 28) {
    big_decimal reminader = big_div10(a, &a);
    big_decimal pol_litra = {{5, 0, 0, 0, 0, 0, 0, 0}};
    if (big_mantissa_is_equal(reminader, pol_litra)) {
      if (a.bits[0] & 1) {
        a = big_plus_big(a, (big_decimal){{1, 0, 0, 0, 0, 0, 0, 0}});
      }
    } else if (big_mantissa_is_greater(reminader, pol_litra)) {
      a = big_plus_big(a, (big_decimal){{1, 0, 0, 0, 0, 0, 0, 0}});
    }
    scale--;
  }
  set_sign(&a.bits[7], sign);
  for (int i = 0; i < 3; i++) b.bits[i] = a.bits[i];
  b.bits[3] = a.bits[7];
  set_scale(&b.bits[3], scale);
  return b;
}

big_decimal big_minus_big(big_decimal value_1, big_decimal value_2) {
  big_decimal result = {{0, 0, 0, 0, 0, 0, 0, 0}};
  int debt = 0, sum = 0;
  for (int i = 0; i < 32 * 7; i++) {
    sum = check_bit(value_1, i) - check_bit(value_2, i) - debt;
    debt = sum < 0 ? 1 : 0;
    set_bit(&result, i, sum % 2);
  }
  result.bits[7] = value_1.bits[7];
  return result;
}

big_decimal big_x10(big_decimal value) {
  return big_plus_big(shift_big_decimal(value, 3, 'L'),
                      shift_big_decimal(value, 1, 'L'));
}

big_decimal big_div10(big_decimal value, big_decimal *result) {
  big_decimal divider = {{10, 0, 0, 0, 0, 0, 0, 0}};
  return big_div_big(value, divider, result);
}

void normalization(big_decimal *value_1, big_decimal *value_2) {
  int delta = get_scale(value_1->bits[7]) - get_scale(value_2->bits[7]);

  while (delta > 0) {
    *value_2 = big_x10(*value_2);
    set_scale(&(value_2->bits[7]), get_scale((value_1->bits[7])));
    delta--;
  }
  while (delta < 0) {
    *value_1 = big_x10(*value_1);
    set_scale(&(value_1->bits[7]), get_scale((value_2->bits[7])));
    delta++;
  }
}

int get_width(big_decimal value) {
  int width = 0;
  for (int i = 32 * 7 - 1; i >= 0 && !width; i--) {
    if (check_bit(value, i)) width = i;
  }
  return width;
}

int big_mantissa_compare(big_decimal value_1, big_decimal value_2) {
  int result = 0;
  for (int i = 32 * 7 - 1; i >= 0 && result == 0; i--) {
    int bit1 = check_bit(value_1, i);
    int bit2 = check_bit(value_2, i);
    result = (bit1 < bit2) ? -1 : (bit1 > bit2) ? 1 : 0;
  }
  return result;
}

int big_mantissa_is_less(big_decimal value_1, big_decimal value_2) {
  return big_mantissa_compare(value_1, value_2) == -1;
}

int big_mantissa_is_less_or_equal(big_decimal value_1, big_decimal value_2) {
  int compare_result = big_mantissa_compare(value_1, value_2);
  return compare_result == -1 || compare_result == 0;
}

int big_mantissa_is_greater(big_decimal value_1, big_decimal value_2) {
  return big_mantissa_compare(value_1, value_2) == 1;
}

int big_mantissa_is_greater_or_equal(big_decimal value_1, big_decimal value_2) {
  int compare_result = big_mantissa_compare(value_1, value_2);
  return compare_result == 1 || compare_result == 0;
}

int big_mantissa_is_equal(big_decimal value_1, big_decimal value_2) {
  return big_mantissa_compare(value_1, value_2) == 0;
}

int big_mantissa_is_not_equal(big_decimal value_1, big_decimal value_2) {
  return big_mantissa_compare(value_1, value_2) != 0;
}