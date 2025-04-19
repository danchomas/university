#include "my_test.h"

// START_TEST(matrix_sum_test_1) {
//   double array[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
//   double array_res[3][3] = {{4, 10, 14}, {12, 6, 8}, {10, -4, -6}};
//   int row = 3;
//   int col = 3;
//   matrix_t A = {0};
//   matrix_t B = {0};
//   matrix_t result = {0};
//   matrix_t res_check = {0};
//   my_create_matrix(row, col, &A);
//   my_create_matrix(row, col, &B);
//   my_create_matrix(row, col, &res_check);
//   for (int i = 0; i < row; i++)
//     for (int j = 0; j < col; j++) {
//       A.matrix[i][j] = array[i][j];
//       B.matrix[i][j] = array[i][j];
//       res_check.matrix[i][j] = array_res[i][j];
//     }
//   ck_assert_int_eq(my_sum_matrix(&A, &B, &result), OK);
//   ck_assert_int_eq(my_eq_matrix(&res_check, &result), SUCCESS);
//   my_remove_matrix(&A);
//   my_remove_matrix(&B);
//   my_remove_matrix(&result);
//   my_remove_matrix(&res_check);
// }
// END_TEST

// START_TEST(matrix_sum_test_2) {
//   double array_a[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
//   double array_b[2][3] = {{2, 5, 7}, {6, 3, 4}};
//   int row_a = 3;
//   int col_a = 3;
//   int row_b = 2;
//   int col_b = 3;
//   matrix_t A = {0};
//   matrix_t B = {0};
//   matrix_t result = {0};
//   my_create_matrix(row_a, col_a, &A);
//   my_create_matrix(row_b, col_b, &B);
//   for (int i = 0; i < row_a; i++)
//     for (int j = 0; j < col_a; j++) {
//       A.matrix[i][j] = array_a[i][j];
//     }
//   for (int i = 0; i < row_b; i++) {
//     for (int j = 0; j < row_b; j++) {
//       B.matrix[i][j] = array_b[i][j];
//     }
//   }
//   ck_assert_int_eq(my_sum_matrix(&A, &B, &result), CALCULATION_ERROR);
//   my_remove_matrix(&A);
//   my_remove_matrix(&B);
//   my_remove_matrix(&result);
// }
// END_TEST

// START_TEST(matrix_sum_test_3) {
//   double array_b[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
//   double array_a[2][3] = {{2, 5, 7}, {6, 3, 4}};
//   int row_b = 3;
//   int col_b = 3;
//   int row_a = 2;
//   int col_a = 3;
//   matrix_t A = {0};
//   matrix_t B = {0};
//   matrix_t result = {0};
//   my_create_matrix(row_a, col_a, &A);
//   my_create_matrix(row_b, col_b, &B);
//   for (int i = 0; i < row_a; i++)
//     for (int j = 0; j < col_a; j++) {
//       A.matrix[i][j] = array_a[i][j];
//     }
//   for (int i = 0; i < row_b; i++) {
//     for (int j = 0; j < col_b; j++) {
//       B.matrix[i][j] = array_b[i][j];
//     }
//   }
//   ck_assert_int_eq(my_sum_matrix(&A, &B, &result), CALCULATION_ERROR);
//   my_remove_matrix(&A);
//   my_remove_matrix(&B);
//   my_remove_matrix(&result);
// }
// END_TEST

// START_TEST(matrix_sum_test_4) {
//   double array_a[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
//   double array_b[3][2] = {{2, 5}, {6, 3}, {5, -2}};
//   int row_a = 3;
//   int col_a = 3;
//   int row_b = 3;
//   int col_b = 2;
//   matrix_t A = {0};
//   matrix_t B = {0};
//   matrix_t result = {0};
//   my_create_matrix(row_a, col_a, &A);
//   my_create_matrix(row_b, col_b, &B);
//   for (int i = 0; i < row_a; i++)
//     for (int j = 0; j < col_a; j++) {
//       A.matrix[i][j] = array_a[i][j];
//     }
//   for (int i = 0; i < row_b; i++) {
//     for (int j = 0; j < col_b; j++) {
//       B.matrix[i][j] = array_b[i][j];
//     }
//   }
//   ck_assert_int_eq(my_sum_matrix(&A, &B, &result), CALCULATION_ERROR);
//   my_remove_matrix(&A);
//   my_remove_matrix(&B);
//   my_remove_matrix(&result);
// }
// END_TEST

// START_TEST(matrix_sum_test_5) {
//   double array_a[2][3] = {{2, 5, 7}, {6, 3, 4}};
//   int row_a = 2;
//   int col_a = 3;
//   matrix_t A = {0};
//   matrix_t B = {0};
//   matrix_t result = {0};
//   my_create_matrix(row_a, col_a, &A);
//   for (int i = 0; i < row_a; i++)
//     for (int j = 0; j < col_a; j++) {
//       A.matrix[i][j] = array_a[i][j];
//     }
//   ck_assert_int_eq(my_sum_matrix(&A, &B, &result), MATRIX_ERROR);
//   my_remove_matrix(&A);
//   my_remove_matrix(&B);
//   my_remove_matrix(&result);
// }
// END_TEST

// START_TEST(matrix_sum_test_6) {
//   double array_b[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
//   int row_b = 3;
//   int col_b = 3;
//   matrix_t A = {0};
//   matrix_t B = {0};
//   matrix_t result = {0};
//   my_create_matrix(row_b, col_b, &B);
//   for (int i = 0; i < row_b; i++) {
//     for (int j = 0; j < col_b; j++) {
//       B.matrix[i][j] = array_b[i][j];
//     }
//   }
//   ck_assert_int_eq(my_sum_matrix(&A, &B, &result), MATRIX_ERROR);
//   my_remove_matrix(&A);
//   my_remove_matrix(&B);
//   my_remove_matrix(&result);
// }
// END_TEST

// START_TEST(matrix_sum_test_7) {
//   double array_b[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
//   double array_a[2][3] = {{2, 5, 7}, {6, 3, 4}};
//   int row_b = 3;
//   int col_b = 3;
//   int row_a = 2;
//   int col_a = 3;
//   matrix_t A = {0};
//   matrix_t B = {0};
//   matrix_t result = {0};
//   my_create_matrix(row_a, col_a, &A);
//   my_create_matrix(row_b, col_b, &B);

//   for (int i = 0; i < row_a; i++)
//     for (int j = 0; j < col_a; j++) {
//       A.matrix[i][j] = array_a[i][j];
//     }
//   for (int i = 0; i < row_b; i++) {
//     for (int j = 0; j < col_b; j++) {
//       B.matrix[i][j] = array_b[i][j];
//     }
//   }
//   ck_assert_int_eq(my_sum_matrix(&A, &B, NULL), MATRIX_ERROR);
//   my_remove_matrix(&A);
//   my_remove_matrix(&B);
//   my_remove_matrix(&result);
// }
// END_TEST

// START_TEST(matrix_sum_test_8) {
//   double array_a[3][3] = {{2.000000001, 5.000000001, 7.000000001},
//                           {6.000000001, 3.000000001, 4.000000001},
//                           {5.000000001, -2.000000001, -3.000000001}};
//   double array_b[3][3] = {{2.000000002, 5.000000002, 7.000000002},
//                           {6.000000002, 3.000000002, 4.000000002},
//                           {5.000000002, -2.000000002, -3.000000002}};
//   double array_res[3][3] = {{4.000000003, 10.000000003, 14.000000003},
//                             {12.000000003, 6.000000003, 8.000000003},
//                             {10.000000003, -4.000000003, -6.000000003}};
//   int row = 3;
//   int col = 3;
//   matrix_t A = {0};
//   matrix_t B = {0};
//   matrix_t result = {0};
//   matrix_t result_chek = {0};
//   my_create_matrix(row, col, &A);
//   my_create_matrix(row, col, &B);
//   my_create_matrix(row, col, &result_chek);
//   for (int i = 0; i < row; i++)
//     for (int j = 0; j < col; j++) {
//       A.matrix[i][j] = array_a[i][j];
//       B.matrix[i][j] = array_b[i][j];
//       result_chek.matrix[i][j] = array_res[i][j];
//     }
//   ck_assert_int_eq(my_sum_matrix(&A, &B, &result), OK);
//   ck_assert_int_eq(my_eq_matrix(&result_chek, &result), SUCCESS);
//   my_remove_matrix(&A);
//   my_remove_matrix(&B);
//   my_remove_matrix(&result);
//   my_remove_matrix(&result_chek);
// }
// END_TEST

// START_TEST(matrix_sum_test_9) {
//   double array_a[3][3] = {{2.0000001, 5.0000001, 7.0000001},
//                           {6.0000001, 3.0000001, 4.0000001},
//                           {5.0000001, -2.0000001, -3.0000001}};
//   double array_b[3][3] = {{2.0000002, 5.0000002, 7.0000002},
//                           {6.0000002, 3.0000002, 4.0000002},
//                           {5.0000002, -2.0000002, -3.0000002}};
//   double array_res[3][3] = {{4.0000003, 10.0000003, 14.0000003},
//                             {12.0000003, 6.0000003, 8.0000003},
//                             {10.0000003, -4.0000003, -6.0000003}};
//   int row = 3;
//   int col = 3;
//   matrix_t A = {0};
//   matrix_t B = {0};
//   matrix_t result = {0};
//   matrix_t result_chek = {0};
//   my_create_matrix(row, col, &A);
//   my_create_matrix(row, col, &B);
//   my_create_matrix(row, col, &result_chek);
//   for (int i = 0; i < row; i++)
//     for (int j = 0; j < col; j++) {
//       A.matrix[i][j] = array_a[i][j];
//       B.matrix[i][j] = array_b[i][j];
//       result_chek.matrix[i][j] = array_res[i][j];
//     }
//   ck_assert_int_eq(my_sum_matrix(&A, &B, &result), OK);
//   ck_assert_int_eq(my_eq_matrix(&result_chek, &result), SUCCESS);
//   my_remove_matrix(&A);
//   my_remove_matrix(&B);
//   my_remove_matrix(&result);
//   my_remove_matrix(&result_chek);
// }
// END_TEST

// START_TEST(matrix_sum_test_10) {
//   double array_a[2][3] = {{2, 5, 7}, {6, 3, 4}};
//   int row_a = 2;
//   int col_a = 3;
//   matrix_t A = {0};
//   matrix_t result = {0};
//   my_create_matrix(row_a, col_a, &A);

//   for (int i = 0; i < row_a; i++) {
//     for (int j = 0; j < col_a; j++) {
//       A.matrix[i][j] = array_a[i][j];
//     }
//   }
//   ck_assert_int_eq(my_sum_matrix(&A, NULL, &result), MATRIX_ERROR);
//   my_remove_matrix(&A);
//   my_remove_matrix(&result);
// }
// END_TEST

// START_TEST(matrix_sum_test_11) {
//   double array_b[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
//   double array_a[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
//   int row_b = 3;
//   int col_b = 3;
//   int row_a = 3;
//   int col_a = 3;
//   matrix_t A = {0};
//   matrix_t B = {0};
//   matrix_t result = {0};
//   my_create_matrix(row_a, col_a, &A);
//   my_create_matrix(row_b, col_b, &B);

//   for (int i = 0; i < row_a; i++)
//     for (int j = 0; j < col_a; j++) {
//       A.matrix[i][j] = array_a[i][j];
//     }
//   for (int i = 0; i < row_b; i++) {
//     for (int j = 0; j < col_b; j++) {
//       B.matrix[i][j] = array_b[i][j];
//     }
//   }
//   A.rows = -1;
//   ck_assert_int_eq(my_sum_matrix(&A, &B, &result), MATRIX_ERROR);
//   A.rows = 3;
//   my_remove_matrix(&A);
//   my_remove_matrix(&B);
//   my_remove_matrix(&result);
// }
// END_TEST

// START_TEST(matrix_sum_test_12) {
//   double array_b[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
//   double array_a[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
//   int row_b = 3;
//   int col_b = 3;
//   int row_a = 3;
//   int col_a = 3;
//   matrix_t A = {0};
//   matrix_t B = {0};
//   matrix_t result = {0};
//   my_create_matrix(row_a, col_a, &A);
//   my_create_matrix(row_b, col_b, &B);

//   for (int i = 0; i < row_a; i++)
//     for (int j = 0; j < col_a; j++) {
//       A.matrix[i][j] = array_a[i][j];
//     }
//   for (int i = 0; i < row_b; i++) {
//     for (int j = 0; j < col_b; j++) {
//       B.matrix[i][j] = array_b[i][j];
//     }
//   }
//   A.columns = -1;
//   ck_assert_int_eq(my_sum_matrix(&A, &B, &result), MATRIX_ERROR);
//   A.columns = 3;
//   my_remove_matrix(&A);
//   my_remove_matrix(&B);
//   my_remove_matrix(&result);
// }
// END_TEST

// Suite *suite_my_sum_matrix(void) {
//   Suite *s = suite_create("\033[42mmy_SUM_MATRIX\033[0m");
//   TCase *tcase = tcase_create("create_tc");

//   tcase_add_test(tcase, matrix_sum_test_1);
//   tcase_add_test(tcase, matrix_sum_test_2);
//   tcase_add_test(tcase, matrix_sum_test_3);
//   tcase_add_test(tcase, matrix_sum_test_4);
//   tcase_add_test(tcase, matrix_sum_test_5);
//   tcase_add_test(tcase, matrix_sum_test_6);
//   tcase_add_test(tcase, matrix_sum_test_7);
//   tcase_add_test(tcase, matrix_sum_test_8);
//   tcase_add_test(tcase, matrix_sum_test_9);
//   tcase_add_test(tcase, matrix_sum_test_10);
//   tcase_add_test(tcase, matrix_sum_test_11);
//   tcase_add_test(tcase, matrix_sum_test_12);

//   suite_add_tcase(s, tcase);
//   return s;
// }

START_TEST(matrix_sub_test_1) {
  double array[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double array_res[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  int row = 3;
  int col = 3;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  matrix_t res_check = {0};
  my_create_matrix(row, col, &A);
  my_create_matrix(row, col, &B);
  my_create_matrix(row, col, &res_check);
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
      B.matrix[i][j] = array[i][j];
      res_check.matrix[i][j] = array_res[i][j];
    }
  ck_assert_int_eq(my_sub_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(my_eq_matrix(&res_check, &result), SUCCESS);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&result);
  my_remove_matrix(&res_check);
}
END_TEST

START_TEST(matrix_sub_test_2) {
  double array_a[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double array_b[2][3] = {{2, 5, 7}, {6, 3, 4}};
  int row_a = 3;
  int col_a = 3;
  int row_b = 2;
  int col_b = 3;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  my_create_matrix(row_a, col_a, &A);
  my_create_matrix(row_b, col_b, &B);
  for (int i = 0; i < row_a; i++)
    for (int j = 0; j < col_a; j++) {
      A.matrix[i][j] = array_a[i][j];
    }
  for (int i = 0; i < row_b; i++) {
    for (int j = 0; j < col_b; j++) {
      B.matrix[i][j] = array_b[i][j];
    }
  }
  ck_assert_int_eq(my_sub_matrix(&A, &B, &result), CALCULATION_ERROR);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&result);
}
END_TEST

START_TEST(matrix_sub_test_3) {
  double array_b[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double array_a[2][3] = {{2, 5, 7}, {6, 3, 4}};
  int row_b = 3;
  int col_b = 3;
  int row_a = 2;
  int col_a = 3;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  my_create_matrix(row_a, col_a, &A);
  my_create_matrix(row_b, col_b, &B);
  for (int i = 0; i < row_a; i++)
    for (int j = 0; j < col_a; j++) {
      A.matrix[i][j] = array_a[i][j];
    }
  for (int i = 0; i < row_b; i++) {
    for (int j = 0; j < col_b; j++) {
      B.matrix[i][j] = array_b[i][j];
    }
  }
  ck_assert_int_eq(my_sub_matrix(&A, &B, &result), CALCULATION_ERROR);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&result);
}
END_TEST

START_TEST(matrix_sub_test_4) {
  double array_a[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double array_b[3][2] = {{2, 5}, {6, 3}, {5, -2}};
  int row_a = 3;
  int col_a = 3;
  int row_b = 3;
  int col_b = 2;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  my_create_matrix(row_a, col_a, &A);
  my_create_matrix(row_b, col_b, &B);
  for (int i = 0; i < row_a; i++)
    for (int j = 0; j < col_a; j++) {
      A.matrix[i][j] = array_a[i][j];
    }
  for (int i = 0; i < row_b; i++) {
    for (int j = 0; j < col_b; j++) {
      B.matrix[i][j] = array_b[i][j];
    }
  }
  ck_assert_int_eq(my_sub_matrix(&A, &B, &result), CALCULATION_ERROR);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&result);
}
END_TEST

START_TEST(matrix_sub_test_8) {
  double array_a[3][3] = {{2.000000002, 5.000000002, 7.000000002},
                          {6.000000002, 3.000000002, 4.000000002},
                          {5.000000002, -2.000000002, -3.000000002}};
  double array_b[3][3] = {{1.000000001, 1.000000001, 1.000000001},
                          {1.000000001, 1.000000001, 1.000000001},
                          {1.000000001, -1.000000001, -1.000000001}};
  double array_res[3][3] = {{1.000000001, 4.000000001, 6.000000001},
                            {5.000000001, 2.000000001, 3.000000001},
                            {4.000000001, -1.000000001, -2.000000001}};
  int row = 3;
  int col = 3;
  matrix_t A;
  matrix_t B;
  matrix_t result;
  matrix_t result_chek;
  my_create_matrix(row, col, &A);
  my_create_matrix(row, col, &B);
  my_create_matrix(row, col, &result_chek);
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array_a[i][j];
      B.matrix[i][j] = array_b[i][j];
      result_chek.matrix[i][j] = array_res[i][j];
    }
  ck_assert_int_eq(my_sub_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(my_eq_matrix(&result_chek, &result), SUCCESS);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&result);
  my_remove_matrix(&result_chek);
}
END_TEST

START_TEST(matrix_sub_test_9) {
  double array_a[3][3] = {{2.0000002, 5.0000002, 7.0000002},
                          {6.0000002, 3.0000002, 4.0000002},
                          {5.0000002, -2.0000002, -3.0000002}};
  double array_b[3][3] = {{1.0000001, 1.0000001, 1.0000001},
                          {1.0000001, 1.0000001, 1.0000001},
                          {1.0000001, -1.0000001, -1.0000001}};
  double array_res[3][3] = {{1.0000001, 4.0000001, 6.0000001},
                            {5.0000001, 2.0000001, 3.0000001},
                            {4.0000001, -1.0000001, -2.0000001}};
  int row = 3;
  int col = 3;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  matrix_t result_chek = {0};
  my_create_matrix(row, col, &A);
  my_create_matrix(row, col, &B);
  my_create_matrix(row, col, &result_chek);
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array_a[i][j];
      B.matrix[i][j] = array_b[i][j];
      result_chek.matrix[i][j] = array_res[i][j];
    }
  ck_assert_int_eq(my_sub_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(my_eq_matrix(&result_chek, &result), SUCCESS);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&result);
  my_remove_matrix(&result_chek);
}
END_TEST

Suite *suite_my_sub_matrix(void) {
  Suite *s = suite_create("\033[42mmy_SUB_MATRIX\033[0m");
  TCase *tcase = tcase_create("create_tc");

  tcase_add_test(tcase, matrix_sub_test_1);
  tcase_add_test(tcase, matrix_sub_test_2);
  tcase_add_test(tcase, matrix_sub_test_3);
  tcase_add_test(tcase, matrix_sub_test_4);
  tcase_add_test(tcase, matrix_sub_test_8);
  tcase_add_test(tcase, matrix_sub_test_9);

  suite_add_tcase(s, tcase);
  return s;
}

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
  ck_assert_int_eq(my_mult_number(&A, num, &result), MATRIX_ERROR);
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
  ck_assert_int_eq(my_mult_number(&A, num, NULL), MATRIX_ERROR);
  my_remove_matrix(&A);
  my_remove_matrix(&result);
}
END_TEST

START_TEST(matrix_mul_num_test_5) {
  matrix_t A = {0};
  double num = 3.14;
  matrix_t result = {0};
  ck_assert_int_eq(my_mult_number(&A, num, &result), MATRIX_ERROR);
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

START_TEST(matrix_mult_mtrx_test_1) {
  double array_a[3][2] = {{1, 4}, {2, 5}, {3, 6}};
  double array_b[2][3] = {{1, -1, 1}, {2, 3, 4}};
  double array_res[3][3] = {{9, 11, 17}, {12, 13, 22}, {15, 15, 27}};
  int row_a = 3;
  int col_a = 2;
  int row_b = 2;
  int col_b = 3;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  matrix_t res_check = {0};
  my_create_matrix(row_a, col_a, &A);
  my_create_matrix(row_b, col_b, &B);
  my_create_matrix(row_a, col_b, &res_check);
  for (int i = 0; i < row_a; i++) {
    for (int j = 0; j < col_a; j++) {
      A.matrix[i][j] = array_a[i][j];
    }
  }
  for (int i = 0; i < row_b; i++) {
    for (int j = 0; j < col_b; j++) {
      B.matrix[i][j] = array_b[i][j];
    }
  }
  for (int i = 0; i < res_check.rows; i++) {
    for (int j = 0; j < res_check.columns; j++) {
      res_check.matrix[i][j] = array_res[i][j];
    }
  }
  ck_assert_int_eq(my_mult_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(my_eq_matrix(&res_check, &result), SUCCESS);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&result);
  my_remove_matrix(&res_check);
}
END_TEST

START_TEST(matrix_mult_mtrx_test_2) {
  double array_a[3][5] = {{2.36, 4.59, 4.325, 0.364, 0.003},
                          {2.3, 99.6, 45.786, 944.36, 23.336},
                          {-5546, -2.36, -31.668, -565.22, -94.2}};
  double array_b[2][3] = {{2, 5, 7}, {6, 3, 4}};
  int row_a = 3;
  int col_a = 5;
  int row_b = 2;
  int col_b = 3;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  my_create_matrix(row_a, col_a, &A);
  my_create_matrix(row_b, col_b, &B);
  my_create_matrix(row_a, col_b, &result);
  for (int i = 0; i < row_a; i++)
    for (int j = 0; j < col_a; j++) {
      A.matrix[i][j] = array_a[i][j];
    }
  for (int i = 0; i < row_b; i++) {
    for (int j = 0; j < row_b; j++) {
      B.matrix[i][j] = array_b[i][j];
    }
  }
  ck_assert_int_eq(my_mult_matrix(&A, &B, &result), CALCULATION_ERROR);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&result);
}
END_TEST

START_TEST(matrix_mult_mtrx_test_5) {
  double array_b[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double array_a[2][3] = {{2, 5, 7}, {6, 3, 4}};
  int row_b = 3;
  int col_b = 3;
  int row_a = 2;
  int col_a = 3;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  my_create_matrix(row_a, col_a, &A);
  my_create_matrix(row_b, col_b, &B);
  for (int i = 0; i < row_a; i++)
    for (int j = 0; j < col_a; j++) {
      A.matrix[i][j] = array_a[i][j];
    }
  for (int i = 0; i < row_b; i++) {
    for (int j = 0; j < col_b; j++) {
      B.matrix[i][j] = array_b[i][j];
    }
  }
  ck_assert_int_eq(my_mult_matrix(&A, &B, NULL), MATRIX_ERROR);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&result);
}
END_TEST

Suite *suite_my_mult_matrix(void) {
  Suite *s = suite_create("\033[42mmy_MULT_MATRIX\033[0m");
  TCase *tcase = tcase_create("create_tc");

  tcase_add_test(tcase, matrix_mult_mtrx_test_1);
  tcase_add_test(tcase, matrix_mult_mtrx_test_2);
  tcase_add_test(tcase, matrix_mult_mtrx_test_5);

  suite_add_tcase(s, tcase);
  return s;
}

START_TEST(matrix_inverse_test_1) {
  double array[1][1] = {{2}};
  int row = 1;
  int col = 1;
  matrix_t A = {0};
  matrix_t result = {0};
  matrix_t res_check = {0};
  my_create_matrix(row, col, &A);
  my_create_matrix(row, col, &res_check);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
    }
  }
  res_check.matrix[0][0] = 1.0 / 2.0;
  ck_assert_int_eq(my_inverse_matrix(&A, &result), OK);
  ck_assert_int_eq(my_eq_matrix(&res_check, &result), SUCCESS);
  my_remove_matrix(&A);
  my_remove_matrix(&result);
  my_remove_matrix(&res_check);
}
END_TEST

START_TEST(matrix_inverse_test_2) {
  double array[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  int row = 3;
  int col = 3;
  matrix_t A = {0};
  matrix_t result = {0};
  my_create_matrix(row, col, &A);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
    }
  }
  ck_assert_int_eq(my_inverse_matrix(&A, &result), CALCULATION_ERROR);
  my_remove_matrix(&A);
}
END_TEST

START_TEST(matrix_inverse_test_3) {
  double array[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double array_res[3][3] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};
  int row = 3;
  int col = 3;
  matrix_t A = {0};
  matrix_t res_check = {0};
  matrix_t result = {0};
  my_create_matrix(row, col, &A);
  my_create_matrix(row, col, &res_check);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
      res_check.matrix[i][j] = array_res[i][j];
    }
  }
  ck_assert_int_eq(my_inverse_matrix(&A, &result), OK);
  ck_assert_int_eq(my_eq_matrix(&res_check, &result), SUCCESS);
  my_remove_matrix(&A);
  my_remove_matrix(&result);
  my_remove_matrix(&res_check);
}
END_TEST

START_TEST(matrix_inverse_test_4) {
  double array[3][2] = {{1, 2}, {0, 4}, {5, 2}};
  int row = 3;
  int col = 2;
  matrix_t A = {0};
  matrix_t result = {0};
  my_create_matrix(row, col, &A);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
    }
  }
  ck_assert_int_eq(my_inverse_matrix(&A, &result), CALCULATION_ERROR);
  my_remove_matrix(&A);
}
END_TEST

START_TEST(matrix_inverse_test_5) {
  matrix_t A = {0};
  matrix_t result = {0};
  ck_assert_int_eq(my_inverse_matrix(&A, &result), MATRIX_ERROR);
}
END_TEST

Suite *suite_my_inverse(void) {
  Suite *s = suite_create("\033[42mmy_INVERSE\033[0m");
  TCase *tcase = tcase_create("create_tc");

  tcase_add_test(tcase, matrix_inverse_test_1);
  tcase_add_test(tcase, matrix_inverse_test_2);
  tcase_add_test(tcase, matrix_inverse_test_3);
  tcase_add_test(tcase, matrix_inverse_test_4);
  tcase_add_test(tcase, matrix_inverse_test_5);

  suite_add_tcase(s, tcase);
  return s;
}

START_TEST(matrix_determinant_test_1) {
  double array[1][1] = {{2}};
  double res_check = 2;
  int row = 1;
  int col = 1;
  matrix_t A = {0};
  double result = 0.0;
  my_create_matrix(row, col, &A);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
    }
  }
  ck_assert_int_eq(my_determinant(&A, &result), OK);
  ck_assert_int_eq(result, res_check);
  my_remove_matrix(&A);
}
END_TEST

START_TEST(matrix_determinant_test_2) {
  double array[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  double res_check = 0;
  int row = 3;
  int col = 3;
  matrix_t A = {0};
  double result = 0.0;
  my_create_matrix(row, col, &A);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
    }
  }
  ck_assert_int_eq(my_determinant(&A, &result), OK);
  ck_assert_int_eq(result, res_check);
  my_remove_matrix(&A);
}
END_TEST

Suite *suite_my_determinant(void) {
  Suite *s = suite_create("\033[42mmy_DETERMINANT\033[0m");
  TCase *tcase = tcase_create("create_tc");

  tcase_add_test(tcase, matrix_determinant_test_1);
  tcase_add_test(tcase, matrix_determinant_test_2);

  suite_add_tcase(s, tcase);
  return s;
}

START_TEST(matrix_create_test_1) {
  matrix_t A = {0};
  ck_assert_int_eq(my_create_matrix(3, 3, &A), OK);
  my_remove_matrix(&A);
}
END_TEST

START_TEST(matrix_create_test_2) {
  ck_assert_int_eq(my_create_matrix(3, 3, NULL), MATRIX_ERROR);
}
END_TEST

START_TEST(matrix_create_test_3) {
  matrix_t A = {0};
  ck_assert_int_eq(my_create_matrix(3, 0, &A), MATRIX_ERROR);
}
END_TEST

START_TEST(matrix_create_test_4) {
  matrix_t A = {0};
  ck_assert_int_eq(my_create_matrix(0, 3, &A), MATRIX_ERROR);
}
END_TEST

START_TEST(matrix_create_test_5) {
  matrix_t A = {0};
  ck_assert_int_eq(my_create_matrix(1, 1, &A), OK);
  my_remove_matrix(&A);
}
END_TEST

START_TEST(matrix_create_test_6) {
  matrix_t A = {0};
  ck_assert_int_eq(my_create_matrix(
                       (unsigned int)0b11111111111111111111111111111111, 1, &A),
                   MATRIX_ERROR);
}
END_TEST

Suite *suite_my_create_matrix(void) {
  Suite *s = suite_create("\033[42mmy_CREATE_MATRIX\033[0m");
  TCase *tcase = tcase_create("create_tc");

  tcase_add_test(tcase, matrix_create_test_1);
  tcase_add_test(tcase, matrix_create_test_2);
  tcase_add_test(tcase, matrix_create_test_3);
  tcase_add_test(tcase, matrix_create_test_4);
  tcase_add_test(tcase, matrix_create_test_5);
  tcase_add_test(tcase, matrix_create_test_6);

  suite_add_tcase(s, tcase);
  return s;
}


START_TEST(matrix_calc_complements_test_2) {
  double array[3][3] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};
  double array_res[3][3] = {{0, 10, -20}, {4, -14, 8}, {-8, -2, 4}};
  int row = 3;
  int col = 3;
  matrix_t A = {0};
  matrix_t res_check = {0};
  matrix_t result = {0};
  my_create_matrix(row, col, &A);
  my_create_matrix(row, col, &res_check);
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
      res_check.matrix[i][j] = array_res[i][j];
    }
  ck_assert_int_eq(my_calc_complements(&A, &result), OK);
  ck_assert_int_eq(my_eq_matrix(&res_check, &result), SUCCESS);
  my_remove_matrix(&A);
  my_remove_matrix(&res_check);
  my_remove_matrix(&result);
}
END_TEST


START_TEST(matrix_calc_complements_test_4) {
  matrix_t A = {0};
  matrix_t result = {0};
  ck_assert_int_eq(my_calc_complements(&A, &result), MATRIX_ERROR);
  my_remove_matrix(&A);
  my_remove_matrix(&result);
}
END_TEST

START_TEST(matrix_calc_complements_test_5) {
  double array[3][2] = {{1, 2}, {0, 4}, {5, 2}};
  int row = 3;
  int col = 2;
  matrix_t A = {0};
  matrix_t result = {0};
  my_create_matrix(row, col, &A);
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
    }
  ck_assert_int_eq(my_calc_complements(&A, &result), CALCULATION_ERROR);
  my_remove_matrix(&A);
  my_remove_matrix(&result);
}
END_TEST

START_TEST(matrix_calc_complements_test_6) {
  double array[2][1] = {{2}, {5}};
  int row = 2;
  int col = 1;
  matrix_t A = {0};
  matrix_t result = {0};
  my_create_matrix(row, col, &A);
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
    }
  ck_assert_int_eq(my_calc_complements(&A, &result), CALCULATION_ERROR);
  my_remove_matrix(&A);
  my_remove_matrix(&result);
}
END_TEST

START_TEST(matrix_calc_complements_test_7) {
  double array[1][2] = {{2, 5}};
  int row = 1;
  int col = 2;
  matrix_t A = {0};
  matrix_t result = {0};
  my_create_matrix(row, col, &A);
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
    }
  ck_assert_int_eq(my_calc_complements(&A, &result), CALCULATION_ERROR);
  my_remove_matrix(&A);
  my_remove_matrix(&result);
}
END_TEST

START_TEST(matrix_calc_complements_test_8) {
  double array[3][3] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};
  int row = 3;
  int col = 3;
  matrix_t A = {0};
  my_create_matrix(row, col, &A);
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
    }
  ck_assert_int_eq(my_calc_complements(&A, NULL), MATRIX_ERROR);
  my_remove_matrix(&A);
}
END_TEST

Suite *suite_my_calc_complements(void) {
  Suite *s = suite_create("\033[42mmy_CALC_COMPLEMENTS\033[0m");
  TCase *tcase = tcase_create("create_tc");

  tcase_add_test(tcase, matrix_calc_complements_test_2);
  tcase_add_test(tcase, matrix_calc_complements_test_4);
  tcase_add_test(tcase, matrix_calc_complements_test_5);
  tcase_add_test(tcase, matrix_calc_complements_test_6);
  tcase_add_test(tcase, matrix_calc_complements_test_7);
  tcase_add_test(tcase, matrix_calc_complements_test_8);

  suite_add_tcase(s, tcase);
  return s;
}

START_TEST(matrix_eq_test_1) {
  double array[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  int row = 3;
  int col = 3;
  matrix_t A = {0};
  matrix_t B = {0};
  my_create_matrix(row, col, &A);
  my_create_matrix(row, col, &B);

  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
      B.matrix[i][j] = array[i][j];
    }
  ck_assert_int_eq(my_eq_matrix(&A, &B), SUCCESS);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
}
END_TEST

START_TEST(matrix_eq_test_2) {
  double array_a[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double array_b[2][3] = {{2, 5, 7}, {6, 3, 4}};
  int row_a = 3;
  int col_a = 3;
  int row_b = 2;
  int col_b = 3;
  matrix_t A = {0};
  matrix_t B = {0};
  my_create_matrix(row_a, col_a, &A);
  my_create_matrix(row_b, col_b, &B);

  for (int i = 0; i < row_a; i++)
    for (int j = 0; j < col_a; j++) {
      A.matrix[i][j] = array_a[i][j];
    }
  for (int i = 0; i < row_b; i++)
    for (int j = 0; j < col_b; j++) {
      B.matrix[i][j] = array_b[i][j];
    }
  ck_assert_int_eq(my_eq_matrix(&A, &B), FAILURE);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
}
END_TEST

START_TEST(matrix_eq_test_3) {
  double array_a[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double array_b[3][1] = {{2}, {6}, {4}};
  int row_a = 3;
  int col_a = 3;
  int row_b = 3;
  int col_b = 1;
  matrix_t A = {0};
  matrix_t B = {0};
  my_create_matrix(row_a, col_a, &A);
  my_create_matrix(row_b, col_b, &B);

  for (int i = 0; i < row_a; i++)
    for (int j = 0; j < col_a; j++) {
      A.matrix[i][j] = array_a[i][j];
    }
  for (int i = 0; i < row_b; i++)
    for (int j = 0; j < col_b; j++) {
      B.matrix[i][j] = array_b[i][j];
    }
  ck_assert_int_eq(my_eq_matrix(&A, &B), FAILURE);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
}
END_TEST

START_TEST(matrix_eq_test_4) {
  double array_a[3][3] = {{2.000000001, 5.000000001, 7.000000001},
                          {6.000000001, 3.000000001, 4.000000001},
                          {5.000000001, -2.000000001, -3.000000001}};
  double array_b[3][3] = {{2.000000002, 5.000000002, 7.000000002},
                          {6.000000002, 3.000000002, 4.000000002},
                          {5.000000002, -2.000000002, -3.000000002}};
  int row = 3;
  int col = 3;
  matrix_t A = {0};
  matrix_t B = {0};
  my_create_matrix(row, col, &A);
  my_create_matrix(row, col, &B);

  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array_a[i][j];
      B.matrix[i][j] = array_b[i][j];
    }
  ck_assert_int_eq(my_eq_matrix(&A, &B), SUCCESS);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
}
END_TEST

START_TEST(matrix_eq_test_5) {
  double array_a[3][3] = {{2.0000001, 5.0000001, 7.0000001},
                          {6.0000001, 3.0000001, 4.0000001},
                          {5.0000001, -2.0000001, -3.0000001}};
  double array_b[3][3] = {{2.0000002, 5.0000002, 7.0000002},
                          {6.0000002, 3.0000002, 4.0000002},
                          {5.0000002, -2.0000002, -3.0000002}};
  int row = 3;
  int col = 3;
  matrix_t A = {0};
  matrix_t B = {0};
  my_create_matrix(row, col, &A);
  my_create_matrix(row, col, &B);

  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array_a[i][j];
      B.matrix[i][j] = array_b[i][j];
    }
  ck_assert_int_eq(my_eq_matrix(&A, &B), SUCCESS);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
}
END_TEST

START_TEST(matrix_eq_test_6) {
  double array_a[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  int row = 3;
  int col = 3;
  matrix_t A = {0};
  matrix_t B = {0};
  my_create_matrix(row, col, &A);
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array_a[i][j];
    }
  ck_assert_int_eq(my_eq_matrix(&A, &B), FAILURE);
  my_remove_matrix(&A);
}
END_TEST

START_TEST(matrix_eq_test_7) {
  double array_a[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  int row = 3;
  int col = 3;
  matrix_t A = {0};
  matrix_t B = {0};
  my_create_matrix(row, col, &B);
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      B.matrix[i][j] = array_a[i][j];
    }
  ck_assert_int_eq(my_eq_matrix(&A, &B), FAILURE);
  my_remove_matrix(&B);
}
END_TEST

START_TEST(matrix_eq_test_8) {
  double array[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  int row = 3;
  int col = 3;
  matrix_t A = {0};
  matrix_t B = {0};
  my_create_matrix(row, col, &B);
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      B.matrix[i][j] = array[i][j];
    }
  A.rows = 3;
  A.columns = -3;
  ck_assert_int_eq(my_eq_matrix(&A, &B), FAILURE);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
}
END_TEST

START_TEST(matrix_eq_test_9) {
  double array[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  int row = 3;
  int col = 3;
  matrix_t A = {0};
  matrix_t B = {0};
  my_create_matrix(row, col, &A);
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
    }
  B.rows = -1;
  B.columns = 3;
  ck_assert_int_eq(my_eq_matrix(&A, &B), FAILURE);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
}
END_TEST

Suite *suite_my_eq_matrix(void) {
  Suite *s = suite_create("\033[42mmy_EQ_MATRIX\033[0m");
  TCase *tcase = tcase_create("create_tc");

  tcase_add_test(tcase, matrix_eq_test_1);
  tcase_add_test(tcase, matrix_eq_test_2);
  tcase_add_test(tcase, matrix_eq_test_3);
  tcase_add_test(tcase, matrix_eq_test_4);
  tcase_add_test(tcase, matrix_eq_test_5);
  tcase_add_test(tcase, matrix_eq_test_6);
  tcase_add_test(tcase, matrix_eq_test_7);
  tcase_add_test(tcase, matrix_eq_test_8);
  tcase_add_test(tcase, matrix_eq_test_9);

  suite_add_tcase(s, tcase);
  return s;
}



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
  ck_assert_int_eq(my_transpose(&A, &result), MATRIX_ERROR);
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
  ck_assert_int_eq(my_transpose(&A, NULL), MATRIX_ERROR);
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

void run_tests(int *number_all, int *number_failed) {
  Suite *list_cases[] = {suite_my_create_matrix(),
                         suite_my_eq_matrix(),
                         suite_my_sub_matrix(),
                         suite_my_mult_number(),
                         suite_my_mult_matrix(),
                         suite_my_transpose(),
                         suite_my_calc_complements(),
                         suite_my_determinant(),
                         suite_my_inverse(),
                         NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase, number_all, number_failed);
  }
}

void run_testcase(Suite *testcase, int *number_all, int *number_failed) {
  static int counter_testcase = 1;
  int failed = 0;
  int all = 0;
  if (counter_testcase > 0) putchar('\n');
  counter_testcase++;

  SRunner *sr = srunner_create(testcase);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  failed = srunner_ntests_failed(sr);
  all = srunner_ntests_run(sr);
  *number_failed += failed;
  *number_all += all;

  srunner_free(sr);
}

int main(void) {
  int number_all = 0;
  int number_failed = 0;
  run_tests(&number_all, &number_failed);
  int number_succeess = number_all - number_failed;
  printf(
      "\n===============================\nAll: %d, "
      "\033[32mSuccess: %d\033[0m, \033[31mFailed: "
      "%d\033[0m\n===============================\n",
      number_all, number_succeess, number_failed);
  return 0;
}