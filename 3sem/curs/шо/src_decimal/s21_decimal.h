#ifndef INC_S21_DECIMAL__H
#define INC_S21_DECIMAL__H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define SIZE_S21_DECIMAL 4
#define HIGHEST_BIT_IN_32_BIT_PART 31
#define COUNT_BITS_IN_PART 32
#define START_SCALE_BIT 16
#define LAST_SCALE_BIT 23
#define MAX_HIGHT_BIT 95
#define MAX_POWER 28
#define BUFF_SIZE 128

#define s21_abs(x) ((x) < 0) ? (-(x)) : ((x))

#define DECIMAL_MAX                           \
  (s21_decimal) {                             \
    { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0 } \
  }
#define DECIMAL_MIN                                                         \
  (s21_decimal) {                                                           \
    { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 1 << HIGHEST_BIT_IN_32_BIT_PART } \
  }

typedef struct {
  int bits[SIZE_S21_DECIMAL];
} s21_decimal;

typedef enum {
  ARITHMETHIC_OK,
  ARITHMETHIC_BIG_INFINITY,
  ARITHMETHIC_SMALL_INFINITY,
  ARITHMETHIC_ZERO_DIV
} ARITHMETHIC_RES;

typedef enum {
  OK,
  ERROR,
} RESULT;

typedef enum { LOW_BIT, MID_BIT, HIGH_BIT, SCALE } BITS;

/* Функции возвращают код ошибки:
 *0 - OK
 *1 - число слишком велико или равно бесконечности
 *2 - число слишком мало или равно отрицательной бесконечности
 *3 - деление на 0
 */

// Сложение
extern int s21_add(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result);

// Вычитание
extern int s21_sub(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result);

// Умножение
extern int s21_mul(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result);

// Деление
extern int s21_div(s21_decimal value_1, s21_decimal value_2,
                   s21_decimal *result);

/*Возвращаемое значение:
 * FALSE - не меньше
 * TRUE - меньше
 */
extern int s21_is_less(s21_decimal num1, s21_decimal num2);

extern int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2);

extern int s21_is_greater(s21_decimal num1, s21_decimal num2);

extern int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2);

extern int s21_is_equal(s21_decimal num1, s21_decimal num2);

extern int s21_is_not_equal(s21_decimal num1, s21_decimal num2);

// Возвращаемое значение: 0 - OK || 1 - ошибка конвертации
extern int s21_from_int_to_decimal(int src, s21_decimal *dst);

extern int s21_from_float_to_decimal(float src, s21_decimal *dst);

extern int s21_from_decimal_to_int(s21_decimal src, int *dst);

extern int s21_from_decimal_to_float(s21_decimal src, float *dst);

/*Округляет указанное Decimal число до ближайшего целого числа в сторону
отрицательной бесконечности.
* Возвращаемое значение - код ошибки: 0 - OK || 1 - ошибка вычисления
*/
extern int s21_floor(s21_decimal value, s21_decimal *result);

/*Округляет Decimal до ближайшего целого числа.
 * Возвращаемое значение - код ошибки: 0 - OK || 1 - ошибка вычисления
 */
extern int s21_round(s21_decimal value, s21_decimal *result);

/*Возвращает целые цифры указанного Decimal числа; любые дробные цифры
  отбрасываются, включая конечные нули.
 * Возвращаемое значение - код ошибки: 0 - OK || 1 - ошибка вычисления
 */
extern int s21_truncate(s21_decimal value, s21_decimal *result);

/*Возвращает результат умножения указанного Decimal на -1.
 * Возвращаемое значение - код ошибки: 0 - OK || 1 - ошибка вычисления
 */
extern int s21_negate(s21_decimal value, s21_decimal *result);

// ------------------------------------
// Bit Manipulation Functions
// ------------------------------------

int Get_Sign(s21_decimal number);
void Set_Sign(s21_decimal *number, int sign);
int Get_Scale(s21_decimal number);
void Set_Scale(s21_decimal *number, int scale);
int Get_Bit(s21_decimal number, int bit);
void Set_Bit(s21_decimal *number, int bit, int sign);
int Shift_Left(s21_decimal *number);
int Shift_Right(s21_decimal *number);

// ------------------------------------
// Initialization Functions
// ------------------------------------

void Init_Decimal_Num(s21_decimal *number);

// ------------------------------------
// Simple Arithmetic Operations
// ------------------------------------

int Simple_Add(s21_decimal value1, s21_decimal value2, s21_decimal *result);
void Simple_Sub(s21_decimal value1, s21_decimal value2, s21_decimal *result);
int Simple_Mul(s21_decimal value1, s21_decimal value2, s21_decimal *result);
s21_decimal Simple_Div(s21_decimal value1, s21_decimal value2,
                       s21_decimal *result);

// ------------------------------------
// Comparison Operations
// ------------------------------------

int Simple_Is_Less(s21_decimal num1, s21_decimal num2);
int Simple_Is_Equal(s21_decimal num1, s21_decimal num2);
int Simple_Is_Less_Or_Equal(s21_decimal num1, s21_decimal num2);
int Simple_Is_Greater(s21_decimal num1, s21_decimal num2);
int Simple_Is_Greater_Or_Equal(s21_decimal num1, s21_decimal num2);
int Simple_Is_Not_Equal(s21_decimal num1, s21_decimal num2);

// ------------------------------------
// Utility Functions
// ------------------------------------

void Bank_Round(s21_decimal *value, int count);
void Normalize(s21_decimal *num1, s21_decimal *num2);

#endif