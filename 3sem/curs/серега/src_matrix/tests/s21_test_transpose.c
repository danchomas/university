#include "my_test.h"

START_TEST(matrix_transpose_test_1) {
  double array[1][1] = {{2}};
  double array_res[1][1] = {{2}};
  int row = 1;
  int col = 1;
  matrix_t A = {0};
  matrix_t res_check = {0};
  matrix_t result = {0};
  my_create_matrix(row, col, &A);
  my_create_matrix(col, row, &res_check);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
      res_check.matrix[i][j] = array_res[i][j];
    }
  }
  ck_assert_int_eq(my_transpose(&A, &result), OK);
  ck_assert_int_eq(my_eq_matrix(&res_check, &result), SUCCESS);
  my_remove_matrix(&A);
  my_remove_matrix(&res_check);
  my_remove_matrix(&result);
}
END_TEST

START_TEST(matrix_transpose_test_2) {
  double array[6][5] = {
      {6.76, 453, 43.9, 0.87, -667},       {45.3, -13.996, 19, 0.1, 0.667},
      {0.76, 83, -45, 0.887, 7.89},        {54, 0, 99, -3.14, 6653},
      {-1.09672, 1, 1.887, 1.61, 9056734}, {0.88, 2, 23.87543, 0.87, -776.98}};
  double array_res[5][6] = {{6.76, 45.3, 0.76, 54, -1.09672, 0.88},
                            {453, -13.996, 83, 0, 1, 2},
                            {43.9, 19, -45, 99, 1.887, 23.87543},
                            {0.87, 0.1, 0.887, -3.14, 1.61, 0.87},
                            {-667, 0.667, 7.89, 6653, 9056734, -776.98}};
  int row = 6;
  int col = 5;
  matrix_t A = {0};
  matrix_t res_tr = {0};
  matrix_t result = {0};
  my_create_matrix(row, col, &A);
  my_create_matrix(col, row, &res_tr);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
    }
  }
  for (int i = 0; i < col; i++) {
    for (int j = 0; j < row; j++) {
      res_tr.matrix[i][j] = array_res[i][j];
    }
  }
  ck_assert_int_eq(my_transpose(&A, &result), OK);
  ck_assert_int_eq(my_eq_matrix(&res_tr, &result), SUCCESS);
  my_remove_matrix(&result);
  ck_assert_int_eq(my_transpose(&res_tr, &result), OK);
  ck_assert_int_eq(my_eq_matrix(&A, &result), SUCCESS);
  my_remove_matrix(&A);
  my_remove_matrix(&res_tr);
  my_remove_matrix(&result);
}
END_TEST

START_TEST(matrix_transpose_test_3) {
  double array_1[3][2] = {{6.98, 9.8}, {3.14, -44}, {-0.76, 6.995}};
  double array_2[3][2] = {{78, 0.87}, {-5.76, 1.34}, {6676, -98.065}};
  int row = 3;
  int col = 2;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t SUM = {0};
  matrix_t A_tr = {0};
  matrix_t B_tr = {0};
  matrix_t SUM_tr = {0};
  matrix_t tr_SUM = {0};
  my_create_matrix(row, col, &A);
  my_create_matrix(row, col, &B);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array_1[i][j];
      B.matrix[i][j] = array_2[i][j];
    }
  }
  ck_assert_int_eq(my_sum_matrix(&A, &B, &SUM), OK);
  ck_assert_int_eq(my_transpose(&SUM, &tr_SUM), OK);
  ck_assert_int_eq(my_transpose(&A, &A_tr), OK);
  ck_assert_int_eq(my_transpose(&B, &B_tr), OK);
  ck_assert_int_eq(my_sum_matrix(&A_tr, &B_tr, &SUM_tr), OK);
  ck_assert_int_eq(my_eq_matrix(&tr_SUM, &SUM_tr), SUCCESS);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&A_tr);
  my_remove_matrix(&B_tr);
  my_remove_matrix(&SUM);
  my_remove_matrix(&SUM_tr);
  my_remove_matrix(&tr_SUM);
}
END_TEST

START_TEST(matrix_transpose_test_4) {
  matrix_t A = {0};
  matrix_t result = {0};
  ck_assert_int_eq(my_transpose(&A, &result), ERROR);
}
END_TEST

START_TEST(matrix_transpose_test_5) {
  double array[3][2] = {{1, 2}, {0, 4}, {5, 2}};
  int row = 3;
  int col = 2;
  matrix_t A = {0};
  my_create_matrix(row, col, &A);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
    }
  }
  ck_assert_int_eq(my_transpose(&A, NULL), ERROR);
  my_remove_matrix(&A);
}
END_TEST

Suite *suite_my_transpose(void) {
  Suite *s = suite_create("\033[42mmy_TRANSPOSE\033[0m");
  TCase *tcase = tcase_create("create_tc");

  tcase_add_test(tcase, matrix_transpose_test_1);
  tcase_add_test(tcase, matrix_transpose_test_2);
  tcase_add_test(tcase, matrix_transpose_test_3);
  tcase_add_test(tcase, matrix_transpose_test_4);
  tcase_add_test(tcase, matrix_transpose_test_5);

  suite_add_tcase(s, tcase);
  return s;
}
