#ifndef MY_MATRIX_H
#define MY_MATRIX_H

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum { OK, MATRIX_ERROR, CALCULATION_ERROR };

#define EPSILON 1e-7
#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// Создает новую матрицу размером rows x columns и записывает её в result
int my_create_matrix(int rows, int columns, matrix_t *result);

// Освобождает память, выделенную под матрицу A
void my_remove_matrix(matrix_t *A);

// Проверяет равенство двух матриц A и B
int my_eq_matrix(matrix_t *A, matrix_t *B);

// Складывает две матрицы A и B и записывает результат в result
int my_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Вычитает матрицу B из матрицы A и записывает результат в result
int my_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Умножает матрицу A на число number и записывает результат в result
int my_mult_number(matrix_t *A, double number, matrix_t *result);

// Перемножает две матрицы A и B и записывает результат в result
int my_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Транспонирует матрицу A и записывает результат в result
int my_transpose(matrix_t *A, matrix_t *result);

// Вычисляет матрицу алгебраических дополнений для матрицы A и записывает результат в result
int my_calc_complements(matrix_t *A, matrix_t *result);

// Вычисляет определитель квадратной матрицы A и записывает его в result
int my_determinant(matrix_t *A, double *result);

// Находит обратную матрицу для квадратной матрицы A (если существует) и записывает результат в result
int my_inverse_matrix(matrix_t *A, matrix_t *result);

#endif