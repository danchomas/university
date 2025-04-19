#include "my_matrix.h"

int my_check_matrix(const matrix_t *A) {
  return (A == NULL || A->matrix == NULL || A->rows < 1 || A->columns < 1)
             ? MATRIX_ERROR
             : OK;
}


int my_create_matrix(int rows, int columns, matrix_t *A) {
  if (!A) return MATRIX_ERROR;
  if (rows < 1 || columns < 1) {
    A->rows = 0;
    A->columns = 0;
    A->matrix = NULL;
    return MATRIX_ERROR;
  }


  A->matrix = (double **)malloc(rows * sizeof(double *));
  if (!A->matrix) {
    A->rows = 0;
    A->columns = 0;
    return MATRIX_ERROR;
  }
  for (int i = 0; i < rows; i++) {
    A->matrix[i] = (double *)malloc(columns * sizeof(double));
    if (!A->matrix[i]) {
      for (int j = 0; j < i; j++) free(A->matrix[j]);
      free(A->matrix);
      A->rows = 0;
      A->columns = 0;
      return MATRIX_ERROR;
    }

    for (int j = 0; j < columns; j++) {
      A->matrix[i][j] = 0.0;
    }


  }

  A->rows = rows;
  A->columns = columns;

  return OK;
}
void my_remove_matrix(matrix_t *A) {
  if (my_check_matrix(A) == OK) {
    for (int i = 0; i < A->rows; i++) free(A->matrix[i]);

    free(A->matrix);

    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}

int my_eq_matrix(matrix_t *A, matrix_t *B) {
  if (A == NULL || B == NULL) return FAILURE;
  if (A->rows != B->rows || A->columns != B->columns) return FAILURE;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-6) return FAILURE;
    }
  }
  return SUCCESS;
}

int my_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A->rows != B->rows || A->columns != B->columns) {
    return CALCULATION_ERROR;
  }

  if (my_create_matrix(A->rows, A->columns, result) != OK) {
    return MATRIX_ERROR;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    }
  }
  return OK;
}

int my_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A->rows != B->rows || A->columns != B->columns) {
    return CALCULATION_ERROR;
  }

  if (my_create_matrix(A->rows, A->columns, result) != OK) {
    return MATRIX_ERROR;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }
  return OK;
}

int my_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A->columns != B->rows) {
    return CALCULATION_ERROR;
  }

  if (my_create_matrix(A->rows, B->columns, result) != OK) {
    return MATRIX_ERROR;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      result->matrix[i][j] = 0;
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }
  return OK;
}

int my_mult_number(matrix_t *A, double number, matrix_t *result) {

  if (my_create_matrix(A->rows, A->columns, result) != OK) {
    return MATRIX_ERROR;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }
  return OK;
}

int my_transpose(matrix_t *A, matrix_t *result) {
  if (A == NULL || result == NULL) return MATRIX_ERROR;

  if (my_create_matrix(A->columns, A->rows, result) != OK) {
    return MATRIX_ERROR;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[j][i] = A->matrix[i][j];
    }
  }

  return OK;
}

int get_minor_matrix(matrix_t *A, int i, int j) {
  int n = A->rows;
  double minor;
  matrix_t B;

  if (n == 1) return A->matrix[0][0];

  my_create_matrix(n - 1, n - 1, &B);
  for (int row = 0, b_row = 0; row < A->rows; row++) {
    if (row == i) continue;
    for (int col = 0, b_col = 0; col < A->columns; col++) {
      if (col == j) continue;
      B.matrix[b_row][b_col++] = A->matrix[row][col];
    }
    b_row++;
  }

  my_determinant(&B, &minor);
  my_remove_matrix(&B);

  return minor;
}

int my_calc_complements(matrix_t *A, matrix_t *result) {
  if (A == NULL || result == NULL) return MATRIX_ERROR;
  if (!result) return MATRIX_ERROR;
  if (my_eq_matrix(A, result)) return MATRIX_ERROR;
  if (A->rows != A->columns) return CALCULATION_ERROR;

  int n = A->rows;
  my_create_matrix(n, n, result);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      double minor = get_minor_matrix(A, i, j);
      double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
      result->matrix[i][j] = sign * minor;
    }
  }

  return OK;
}

static int calculate_determinant_2x2(matrix_t *A, double *result) {
  if (A->rows != 2 || A->columns != 2) {
    return MATRIX_ERROR;
  }
  *result =
      A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  return OK;
}

int my_determinant(matrix_t *A, double *result) {
  if (A->rows != A->columns) return CALCULATION_ERROR;

  *result = 0.0;

  if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else if (A->rows == 2) {
    return calculate_determinant_2x2(A, result);
  } else {
    for (int i = 0; i < A->rows; i++) {
      double sign = (i % 2 == 0) ? 1.0 : -1.0;
      double minor = get_minor_matrix(A, 0, i);
      *result += sign * A->matrix[0][i] * minor;
    }
  }
  return OK;
}

int is_matrix_all_zero(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (A->matrix[i][j] != 0) {
        return 0;
      }
    }
  }
  return 1;
}

int my_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (!A) return MATRIX_ERROR;
  if (!result) return CALCULATION_ERROR;

  if (A->rows != A->columns) return CALCULATION_ERROR;
  if (is_matrix_all_zero(A)) return MATRIX_ERROR;

  double det = 0.0;
  int det_status = my_determinant(A, &det);
  if (det_status != OK || det == 0) {
    return CALCULATION_ERROR;
  }

  my_create_matrix(A->rows, A->columns, result);

  if (A->rows == 1) {
    result->matrix[0][0] = 1.0 / A->matrix[0][0];
  } else {
    matrix_t compliments;
    my_calc_complements(A, &compliments);
    matrix_t transposed_compliments;
    my_transpose(&compliments, &transposed_compliments);

    for (int i = 0; i < transposed_compliments.rows; i++) {
      for (int j = 0; j < transposed_compliments.columns; j++) {
        result->matrix[i][j] = transposed_compliments.matrix[i][j] / det;
      }
    }

    my_remove_matrix(&transposed_compliments);
    my_remove_matrix(&compliments);
  }
  return OK;
}