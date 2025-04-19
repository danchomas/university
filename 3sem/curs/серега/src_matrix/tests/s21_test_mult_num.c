#include "my_test.h"

START_TEST(matrix_mul_num_test_1) {
  double array[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double array_res[3][3] = {{20, 50, 70}, {60, 30, 40}, {50, -20, -30}};
  int row = 3;
  int col = 3;
  matrix_t A = {0};
  double num = 10.0;
  matrix_t result = {0};
  matrix_t res_check = {0};
  my_create_matrix(row, col, &A);
  my_create_matrix(row, col, &res_check);
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
      res_check.matrix[i][j] = array_res[i][j];
    }
  ck_assert_int_eq(my_mult_number(&A, num, &result), OK);
  ck_assert_int_eq(my_eq_matrix(&res_check, &result), SUCCESS);
  my_remove_matrix(&A);
  my_remove_matrix(&result);
  my_remove_matrix(&res_check);
}
END_TEST

START_TEST(matrix_mul_num_test_2) {
  double array[3][5] = {{2.36, 4.59, 4.325, 0.364, 0.003},
                        {2.3, 99.6, 45.786, 944.36, 23.336},
                        {-5546, -2.36, -31.668, -565.22, -94.2}};
  double array_res[3][5] = {
      {8.7084, 16.9371, 15.95925, 1.34316, 0.01107},
      {8.487, 367.524, 168.95034, 3484.6884, 86.10984},
      {-20464.74, -8.7084, -116.85492, -2085.6618, -347.598}};
  int row = 3;
  int col = 5;
  matrix_t A = {0};
  double num = 3.69;
  matrix_t result = {0};
  matrix_t res_check = {0};
  my_create_matrix(row, col, &A);
  my_create_matrix(row, col, &res_check);
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
      res_check.matrix[i][j] = array_res[i][j];
    }
  ck_assert_int_eq(my_mult_number(&A, num, &result), OK);
  ck_assert_int_eq(my_eq_matrix(&res_check, &result), SUCCESS);
  my_remove_matrix(&A);
  my_remove_matrix(&result);
  my_remove_matrix(&res_check);
}
END_TEST

START_TEST(matrix_mul_num_test_3) {
  matrix_t A = {0};
  double num = 3.14;
  matrix_t result = {0};
  ck_assert_int_eq(my_mult_number(&A, num, &result), ERROR);
  my_remove_matrix(&A);
  my_remove_matrix(&result);
}
END_TEST

START_TEST(matrix_mul_num_test_4) {
  double array[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  int row = 3;
  int col = 3;
  matrix_t A = {0};
  double num = 1.16;
  matrix_t result = {0};
  my_create_matrix(row, col, &A);
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
    }
  ck_assert_int_eq(my_mult_number(&A, num, NULL), ERROR);
  my_remove_matrix(&A);
  my_remove_matrix(&result);
}
END_TEST

START_TEST(matrix_mul_num_test_5) {
  matrix_t A = {0};
  double num = 3.14;
  matrix_t result = {0};
  ck_assert_int_eq(my_mult_number(&A, num, &result), ERROR);
  my_remove_matrix(&result);
}
END_TEST

Suite *suite_my_mult_number(void) {
  Suite *s = suite_create("\033[42mmy_MULT_NUMBER\033[0m");
  TCase *tcase = tcase_create("create_tc");

  tcase_add_test(tcase, matrix_mul_num_test_1);
  tcase_add_test(tcase, matrix_mul_num_test_2);
  tcase_add_test(tcase, matrix_mul_num_test_3);
  tcase_add_test(tcase, matrix_mul_num_test_4);
  tcase_add_test(tcase, matrix_mul_num_test_5);

  suite_add_tcase(s, tcase);
  return s;
}
