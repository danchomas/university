#ifndef MY_MATH_TEST_H_
#define MY_MATH_TEST_H_

#include <check.h>
#include <stdio.h>

#include "../my_matrix.h"

Suite *suite_my_create_matrix(void);
Suite *suite_my_eq_matrix(void);
Suite *suite_my_sum_matrix(void);
Suite *suite_my_sub_matrix(void);
Suite *suite_my_mult_number(void);
Suite *suite_my_mult_matrix(void);
Suite *suite_my_calc_complements(void);
Suite *suite_my_transpose(void);
Suite *suite_my_determinant(void);
Suite *suite_my_inverse(void);
Suite *suite_valid_matrix(void);

void run_tests(int *number_all, int *number_failed);
void run_testcase(Suite *testcase, int *number_all, int *number_failed);

#endif
