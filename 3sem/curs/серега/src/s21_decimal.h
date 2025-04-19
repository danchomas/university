#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_
#include <stdbool.h>
#include <stdio.h>

/// errors
#define OK 0
#define CONVERT_ERROR 1

#define TOO_BIG 1
#define TOO_LITTLE 2
#define DIV_BY_ZERO 3

#define FALSE 0
#define TRUE 1

typedef struct {
  unsigned bits[4];
} s21_decimal;

typedef struct {
  unsigned bits[8];
} big_decimal;

// Из int
int s21_from_int_to_decimal(int src, s21_decimal *dst);
// Из float
int s21_from_float_to_decimal(float src, s21_decimal *dst);
// В int
int s21_from_decimal_to_int(s21_decimal src, int *dst);
// В float
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Сложение
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// Вычитание
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// Умножение
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// Деление
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Меньше
int s21_is_less(s21_decimal, s21_decimal);
// Меньше или равно
int s21_is_less_or_equal(s21_decimal, s21_decimal);
// Больше
int s21_is_greater(s21_decimal, s21_decimal);
// Больше или равно
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
// Равно
int s21_is_equal(s21_decimal, s21_decimal);
// Не равно
int s21_is_not_equal(s21_decimal, s21_decimal);

// Возвращает целые цифры указанного Decimal числа; любые дробные цифры
// отбрасываются, включая конечные нули.
int s21_truncate(s21_decimal value, s21_decimal *result);
// Возвращает результат умножения указанного Decimal на -1.
int s21_negate(s21_decimal value, s21_decimal *result);
// Округляет указанное Decimal число до ближайшего целого числа в сторону
// отрицательной бесконечности.
int s21_floor(s21_decimal value, s21_decimal *result);
// Округляет Decimal до ближайшего целого числа.
int s21_round(s21_decimal value, s21_decimal *result);

// Печать одного числа в двоичном виде (УБРАТЬ!)
void print_32_binary(int a);
// Печать децимел в двоичном виде (УБРАТЬ!)
void print_binary(big_decimal a);
// Функция сравнения
int compare_decimals(s21_decimal value_1, s21_decimal value_2);
// Проверка указанного бита
bool check_bit(big_decimal a, int num);
// Установка указанного бита указанным значением
void set_bit(big_decimal *a, int num, int choice);
// Проверить знак
bool check_sign(unsigned value);
// Установить знак
void set_sign(unsigned *value, bool choice);
// Получить разряд
int get_scale(unsigned value);
// Установить разряд
void set_scale(unsigned *value, int num);
// Проверка на ноль
bool is_not_null(big_decimal a);

// Сдвиг по количеству и направлению (L or R)
big_decimal shift_big_decimal(big_decimal a, int value, char vector);
// можем ли перевести число из бига
int can_convert(big_decimal value);
// Перевод в биг децимел
big_decimal to_big(s21_decimal a);
// Перевод из биг в децимел
s21_decimal from_big(big_decimal a);
// Сложить два положительных числа одного порядка
big_decimal big_plus_big(big_decimal value_1, big_decimal value_2);
// Вычесть одно из второго, положительные одного порядка
big_decimal big_minus_big(big_decimal value_1, big_decimal value_2);
// Деление
big_decimal big_div_big(big_decimal divisible, big_decimal divider,
                        big_decimal *result);
// Умножение мантиссы на 10
big_decimal big_x10(big_decimal value);
// Деление мантиссы на 10
big_decimal big_div10(big_decimal value, big_decimal *result);
// Приведение к одному порядку
void normalization(big_decimal *value_1, big_decimal *value_2);
// Получение ширины числа
int get_width(big_decimal value);

// Сравнение мантисс
int big_mantissa_compare(big_decimal value_1, big_decimal value_2);
// Меньше
int big_mantissa_is_less(big_decimal value_1, big_decimal value_2);
// Меньше или равно
int big_mantissa_is_less_or_equal(big_decimal value_1, big_decimal value_2);
// Больше
int big_mantissa_is_greater(big_decimal value_1, big_decimal value_2);
// Больше или равно
int big_mantissa_is_greater_or_equal(big_decimal value_1, big_decimal value_2);
// Равно
int big_mantissa_is_equal(big_decimal value_1, big_decimal value_2);
// Не равно
int big_mantissa_is_not_equal(big_decimal value_1, big_decimal value_2);

#endif  //  SRC_S21_DECIMAL_H_