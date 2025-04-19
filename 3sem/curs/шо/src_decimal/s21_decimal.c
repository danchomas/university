#include "s21_decimal.h"

// ------------------------------------
// Bit Manipulation Functions
// ------------------------------------

int Get_Sign(s21_decimal number) {
  return ((number.bits[SCALE] & (1 << HIGHEST_BIT_IN_32_BIT_PART)) == 0) ? 0
                                                                         : 1;
}

void Set_Sign(s21_decimal *number, int sign) {
  if (sign == 0) {
    number->bits[SCALE] =
        number->bits[SCALE] & ~(1 << HIGHEST_BIT_IN_32_BIT_PART);
  } else {
    number->bits[SCALE] =
        number->bits[SCALE] | (1 << HIGHEST_BIT_IN_32_BIT_PART);
  }
}

int Get_Scale(s21_decimal number) {
  int shift = START_SCALE_BIT;
  int scale = 0, i = 0;
  while (shift <= LAST_SCALE_BIT) {
    int bit = ((number.bits[SCALE] & (1 << shift)) != 0);
    scale += bit * pow(2, i);
    shift++;
    i++;
  }
  return scale;
}

void Set_Scale(s21_decimal *number, int scale) {
  int shift = START_SCALE_BIT;
  while (shift <= LAST_SCALE_BIT) {
    if (scale > 0 && scale % 2 == 1)
      number->bits[SCALE] = number->bits[SCALE] | (1 << shift);

    else
      number->bits[SCALE] = number->bits[SCALE] & ~(1 << shift);

    scale /= 2;
    shift++;
  }
}

int Get_Bit(s21_decimal number, int pos) {
  return ((number.bits[pos / COUNT_BITS_IN_PART] &
           (1 << pos % COUNT_BITS_IN_PART)) == 0)
             ? 0
             : 1;
}

void Set_Bit(s21_decimal *number, int bit, int sign) {
  int pos = bit / COUNT_BITS_IN_PART;

  if (sign)
    number->bits[pos] = number->bits[pos] | (1 << bit % COUNT_BITS_IN_PART);

  else
    number->bits[pos] = number->bits[pos] & ~(1 << bit % COUNT_BITS_IN_PART);
}

int shift_left(s21_decimal *number) {
  int is_overflow = Get_Bit(*number, MAX_HIGHT_BIT);
  for (int i = MAX_HIGHT_BIT; i >= 0; i--) {
    if (i != 0)
      Set_Bit(number, i, Get_Bit(*number, i - 1));

    else
      Set_Bit(number, i, 0);
  }

  return is_overflow;
}

int Shift_Right(s21_decimal *number) {
  int is_overflow = Get_Bit(*number, 1);
  for (int i = 0; i < MAX_HIGHT_BIT + 1; i++) {
    if (i != MAX_HIGHT_BIT)
      Set_Bit(number, i, Get_Bit(*number, i + 1));

    else
      Set_Bit(number, i, 0);
  }

  return is_overflow;
}

// ------------------------------------
// Initialization Functions
// ------------------------------------

void Init_Decimal_Num(s21_decimal *number) {
  memset(number, 0, sizeof(s21_decimal));
}

// ------------------------------------
// Simple Arithmetic Operations
// ------------------------------------

int Simple_Add(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
  Init_Decimal_Num(result);
  int rank = 0;
  for (int i = 0; i < MAX_HIGHT_BIT + 1; i++) {
    int bit_dec1 = Get_Bit(value1, i);
    int bit_dec2 = Get_Bit(value2, i);

    Set_Bit(result, i, bit_dec1 ^ bit_dec2 ^ rank);

    rank = (bit_dec1 && bit_dec2) || (bit_dec1 && rank) || (bit_dec2 && rank);
  }

  return rank;
}

void Simple_Sub(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
  Init_Decimal_Num(result);
  for (int i = 0; i < MAX_HIGHT_BIT + 1; i++) {
    int bit_dec1 = Get_Bit(value1, i);
    int bit_dec2 = Get_Bit(value2, i);

    Set_Bit(result, i, bit_dec1 ^ bit_dec2);

    if (!bit_dec1 && bit_dec2) {
      int j = i + 1;
      while ((bit_dec1 = Get_Bit(value1, j)) != 1) {
        Set_Bit(&value1, j, 1);
        j++;
      }
      Set_Bit(&value1, j, 0);
    }
  }
}

int Simple_Mul(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
  s21_decimal tmp;
  Init_Decimal_Num(&tmp);
  int is_overflow = 0;
  for (int i = 0; i < MAX_HIGHT_BIT + 1 && !is_overflow; i++) {
    if (Get_Bit(value2, i) == 1) {
      s21_decimal temp = value1;
      int j = 0;
      while (j < i) {
        if (shift_left(&temp)) {
          is_overflow = 1;
          break;
        }
        j++;
      }
      if (is_overflow || (is_overflow = Simple_Add(temp, tmp, &tmp))) {
        break;
      }
    }
  }

  if (!is_overflow) *result = tmp;

  return is_overflow;
}

s21_decimal Simple_Div(s21_decimal value1, s21_decimal value2,
                       s21_decimal *result) {
  if (result) Init_Decimal_Num(result);

  s21_decimal fmod = {0};
  s21_decimal temp = {0};

  if (Simple_Is_Greater_Or_Equal(value1, value2)) Set_Bit(&temp, 0, 1);

  if (!Simple_Is_Greater(value2, value1)) {
    while (1) {
      s21_decimal copy_dec2 = value2;
      while (Simple_Is_Greater_Or_Equal(value1, copy_dec2) &&
             !(Get_Bit(value1, MAX_HIGHT_BIT) &&
               Get_Bit(copy_dec2, MAX_HIGHT_BIT))) {
        shift_left(&copy_dec2);
        shift_left(&temp);
      }

      if (!(Get_Bit(value1, MAX_HIGHT_BIT) &&
            Get_Bit(copy_dec2, MAX_HIGHT_BIT)) ||
          (Simple_Is_Greater_Or_Equal(copy_dec2, value1))) {
        Shift_Right(&copy_dec2);
        Shift_Right(&temp);
      }

      Simple_Sub(value1, copy_dec2, &value1);

      if (result) Simple_Add(*result, temp, result);

      Init_Decimal_Num(&temp);
      Set_Bit(&temp, 0, 1);

      if (Simple_Is_Less(value1, value2)) break;
    }
  }

  fmod = value1;
  return fmod;
}

// ------------------------------------
// Comparison Operations
// ------------------------------------

int Simple_Is_Less(s21_decimal num1, s21_decimal num2) {
  int is_less = FALSE;
  for (int i = MAX_HIGHT_BIT; i >= 0; i--) {
    if (Get_Bit(num1, i) ^ Get_Bit(num2, i)) {
      is_less = Get_Bit(num2, i);
      break;
    }
  }

  return is_less;
}

int Simple_Is_Equal(s21_decimal num1, s21_decimal num2) {
  int is_equal = TRUE;
  for (int i = MAX_HIGHT_BIT; i >= 0; i--) {
    if (Get_Bit(num1, i) != Get_Bit(num2, i)) {
      is_equal = FALSE;
      break;
    }
  }

  return is_equal;
}

int Simple_Is_Less_Or_Equal(s21_decimal num1, s21_decimal num2) {
  return Simple_Is_Less(num1, num2) || Simple_Is_Equal(num1, num2);
}

int Simple_Is_Greater(s21_decimal num1, s21_decimal num2) {
  return !Simple_Is_Less_Or_Equal(num1, num2);
}

int Simple_Is_Greater_Or_Equal(s21_decimal num1, s21_decimal num2) {
  return Simple_Is_Greater(num1, num2) || Simple_Is_Equal(num1, num2);
}

int Simple_Is_Not_Equal(s21_decimal num1, s21_decimal num2) {
  return !Simple_Is_Equal(num1, num2);
}

// ------------------------------------
// Utility Functions
// ------------------------------------

void Bank_Round(s21_decimal *value, int count) {
  int system_bit = value->bits[SCALE];
  int exp = Get_Scale(*value) - count;

  while (count > 0) {
    s21_decimal base = {0}, one = {0}, two = {0}, two_res = {0};

    s21_from_int_to_decimal(10, &base);
    s21_from_int_to_decimal(1, &one);
    s21_from_int_to_decimal(2, &two);
    s21_decimal dec_mod = Simple_Div(*value, base, value);

    if (dec_mod.bits[LOW_BIT] > 5) {
      Simple_Add(*value, one, value);
    } else if (dec_mod.bits[LOW_BIT] == 5) {
      two_res = Simple_Div(*value, two, NULL);
      if (Simple_Is_Equal(one, two_res)) Simple_Add(*value, one, value);
    }

    count--;
  }

  value->bits[SCALE] = system_bit;
  Set_Scale(value, exp);
}