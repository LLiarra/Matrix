#include "../s21_matrix.h"
#include <check.h>

START_TEST(s21_create_normal) {
  matrix_t result;
  s21_create_matrix(5, 4, &result);
  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      result.matrix[i][j] = 1.1;
      ck_assert_double_eq_tol(result.matrix[i][j], 1.1, 1e-6);
    }
  }
  ck_assert_int_eq(result.rows, 5);
  ck_assert_int_eq(result.columns, 4);
  s21_remove_matrix(&result);
} END_TEST

START_TEST(s21_create_error) {
  matrix_t result;
  int res = s21_create_matrix(0, 4, &result);
  ck_assert_int_eq(res, INVALID_MATRIX);
} END_TEST

START_TEST(s21_determinant_normal) {
  matrix_t m;
  m.matrix = calloc(2, sizeof(double**));
  double a = 0.0;
  double mat[] = {1.0, 2.0};
  double mat2[] = {3.0, 5.0};
  m.matrix[0] = &mat[0];
  m.matrix[1] = &mat2[0];
  m.rows = 2;
  m.columns = 2;
  s21_determinant(&m, &a);
  ck_assert_double_eq_tol(-1.0, a, 1e-6);
  free(m.matrix);
} END_TEST

START_TEST(s21_determinant_normal_2) {
  matrix_t m;
  m.matrix = calloc(2, sizeof(double**));
  double a = 0.0;
  double mat[] = {11.0, -24.0};
  double mat2[] = {-101.0, 77.0};
  m.matrix[0] = &mat[0];
  m.matrix[1] = &mat2[0];
  m.rows = 2;
  m.columns = 2;
  s21_determinant(&m, &a);
  ck_assert_double_eq_tol(-1577.0, a, 1e-6);
  free(m.matrix);
} END_TEST

START_TEST(s21_determinant_normal_4_by_4) {
  matrix_t m;
  m.matrix = calloc(4, sizeof(double**));
  double a = 0.0;
  double mat[] = {-8.0, 1.0, -1.0, 3.0};
  double mat2[] = {3.0, -1.0, 4.0, -3.0};
  double mat3[] = {-14.0, 2.0, 5.0, 1.0};
  double mat4[] = {5.0, 3.0, 1.0, -1.0};
  m.matrix[0] = &mat[0];
  m.matrix[1] = &mat2[0];
  m.matrix[2] = &mat3[0];
  m.matrix[3] = &mat4[0];
  m.rows = 4;
  m.columns = 4;
  s21_determinant(&m, &a);
  ck_assert_double_eq_tol(125.0, a, 1e-6);
  free(m.matrix);
} END_TEST

START_TEST(s21_determinant_normal_5_by_5) {
  matrix_t m;
  m.matrix = calloc(5, sizeof(double**));
  double a = 0.0;
  double mat[] = {4.0, 1.0, 1.0, 2.0, 1.0};
  double mat2[] = {1.0, 2.0, -1.0, 1.0, 1.0};
  double mat3[] = {3.0, 1.0, 1.0, 1.0, 1.0};
  double mat4[] = {2.0, 1.0, 1.0, 4.0, 1.0};
  double mat5[] = {2.0, -1.0, 1.0, 1.0, 5.0};
  m.matrix[0] = &mat[0];
  m.matrix[1] = &mat2[0];
  m.matrix[2] = &mat3[0];
  m.matrix[3] = &mat4[0];
  m.matrix[4] = &mat5[0];
  m.rows = 5;
  m.columns = 5;
  s21_determinant(&m, &a);
  ck_assert_double_eq_tol(64.0, a, 1e-6);
  free(m.matrix);
} END_TEST

START_TEST(s21_determinant_error) {
  matrix_t m;
  m.matrix = NULL;
  double a = 0.0;
  int res = s21_determinant(&m, &a);
  ck_assert_int_eq(res, INVALID_MATRIX);
} END_TEST

START_TEST(s21_determinant_error_2) {
  matrix_t m;
  double a = 0.0;
  m.matrix = calloc(2, sizeof(double**));
  double mat1[] = {4.0, 15.0, 44.0};
  double mat2[] = {6.0, 0.0, 20.0};
  m.matrix[0] = &mat1[0];
  m.matrix[1] = &mat2[0];
  m.rows = 2;
  m.columns = 3;
  int res = s21_determinant(&m, &a);
  ck_assert_int_eq(res, CALCULATION_ERROR);
  free(m.matrix);
} END_TEST

START_TEST(s21_complements_normal) {
  matrix_t m;
  matrix_t result;
  matrix_t test;
  m.matrix = calloc(3, sizeof(double**));
  test.matrix = calloc(3, sizeof(double**));
  double mat[] = {1.0, 2.0, 3.0};
  double mat2[] = {0.0, 4.0, 2.0};
  double mat3[] = {5.0, 2.0, 1.0};
  m.matrix[0] = &mat[0];
  m.matrix[1] = &mat2[0];
  m.matrix[2] = &mat3[0];
  m.rows = 3;
  m.columns = 3;
  double t[] = {0.0, 10.0, -20.0};
  double t2[] = {4.0, -14.0, 8.0};
  double t3[] = {-8.0, -2.0, 4.0};
  test.matrix[0] = &t[0];
  test.matrix[1] = &t2[0];
  test.matrix[2] = &t3[0];
  test.rows = 3;
  test.columns = 3;
  s21_calc_complements(&m, &result);
  ck_assert_int_eq(s21_eq_matrix(&test, &result), 1);
  s21_remove_matrix(&result);
  free(m.matrix);
  free(test.matrix);
} END_TEST

START_TEST(s21_complements_3_by_3) {
  matrix_t m;
  matrix_t result;
  matrix_t test;
  m.matrix = calloc(3, sizeof(double**));
  test.matrix = calloc(3, sizeof(double**));
  double mat[] = {101.0, 2.0, -4.0};
  double mat2[] = {6.0, -3.0, 12.0};
  double mat3[] = {5.0, -2.0, 3.0};
  m.matrix[0] = &mat[0];
  m.matrix[1] = &mat2[0];
  m.matrix[2] = &mat3[0];
  m.rows = 3;
  m.columns = 3;
  double t[] = {15.0, 42.0, 3.0};
  double t2[] = {2.0, 323.0, 212.0};
  double t3[] = {12.0, -1236.0, -315.0};
  test.matrix[0] = &t[0];
  test.matrix[1] = &t2[0];
  test.matrix[2] = &t3[0];
  test.rows = 3;
  test.columns = 3;
  s21_calc_complements(&m, &result);
  ck_assert_int_eq(s21_eq_matrix(&test, &result), 1);
  s21_remove_matrix(&result);
  free(m.matrix);
  free(test.matrix);
} END_TEST

START_TEST(s21_complements_4_by_4) {
  matrix_t m;
  matrix_t result;
  matrix_t test;
  m.matrix = calloc(4, sizeof(double**));
  test.matrix = calloc(4, sizeof(double**));
  double mat[] = {0.023, 124.161, -4.445, 0.123};
  double mat2[] = {6.122, -3.023, 12.011, 4.112};
  double mat3[] = {5.032, -2.120, 3.530, 1.222};
  double mat4[] = {1.032, -3.120, 0.530, 8.34};
  m.matrix[0] = &mat[0];
  m.matrix[1] = &mat2[0];
  m.matrix[2] = &mat3[0];
  m.matrix[3] = &mat4[0];
  m.rows = 4;
  m.columns = 4;
  double t[] = {120.198301, 316.662458, -17.408659, 104.696500};
  double t2[] = {-3514.483058, 181.479355, 5056.050798, 181.469446};
  double t3[] = {12116.204486, -209.216057, -5814.710587, -1208.019247};
  double t4[] = {-44.272415, -63.492874, -1640.619098, 4811.423335};
  test.matrix[0] = &t[0];
  test.matrix[1] = &t2[0];
  test.matrix[2] = &t3[0];
  test.matrix[3] = &t4[0];
  test.rows = 4;
  test.columns = 4;
  s21_calc_complements(&m, &result);
  ck_assert_int_eq(s21_eq_matrix(&test, &result), 1);
  s21_remove_matrix(&result);
  free(m.matrix);
  free(test.matrix);
} END_TEST

START_TEST(s21_complements_error) {
  matrix_t m;
  m.matrix = NULL;
  matrix_t result;
  int res = s21_calc_complements(&m, &result);
  ck_assert_int_eq(res, INVALID_MATRIX);
} END_TEST

START_TEST(s21_complements_error_2) {
  matrix_t m;
  matrix_t result;
  m.matrix = calloc(2, sizeof(double**));
  double mat1[] = {4.0, 15.0, 44.0};
  double mat2[] = {6.0, 0.0, 20.0};
  m.matrix[0] = &mat1[0];
  m.matrix[1] = &mat2[0];
  m.rows = 2;
  m.columns = 3;
  int res = s21_calc_complements(&m, &result);
  ck_assert_int_eq(res, CALCULATION_ERROR);
  free(m.matrix);
} END_TEST

START_TEST(s21_inverse_normal) {
  matrix_t m;
  matrix_t result;
  matrix_t test;
  m.matrix = calloc(3, sizeof(double**));
  test.matrix = calloc(3, sizeof(double**));
  double mat[] = {2.0, 5.0, 7.0};
  double mat2[] = {6.0, 3.0, 4.0};
  double mat3[] = {5.0, -2.0, -3.0};
  m.matrix[0] = &mat[0];
  m.matrix[1] = &mat2[0];
  m.matrix[2] = &mat3[0];
  m.rows = 3;
  m.columns = 3;
  double t[] = {1.0, -1.0, 1.0};
  double t2[] = {-38.0, 41.0, -34.0};
  double t3[] = {27.0, -29.0, 24.0};
  test.matrix[0] = &t[0];
  test.matrix[1] = &t2[0];
  test.matrix[2] = &t3[0];
  test.rows = 3;
  test.columns = 3;
  s21_inverse_matrix(&m, &result);
  ck_assert_int_eq(s21_eq_matrix(&test, &result), 1);
  s21_remove_matrix(&result);
  free(m.matrix);
  free(test.matrix);
} END_TEST

START_TEST(s21_inverse_1_by_1) {
  matrix_t m;
  matrix_t result;
  matrix_t test;
  m.matrix = calloc(1, sizeof(double**));
  test.matrix = calloc(1, sizeof(double**));
  double mat[] = {5.0};
  m.matrix[0] = &mat[0];
  m.rows = 1;
  m.columns = 1;
  double t[] = {0.2};
  test.matrix[0] = &t[0];
  test.rows = 1;
  test.columns = 1;
  s21_inverse_matrix(&m, &result);
  ck_assert_int_eq(s21_eq_matrix(&test, &result), 1);
  s21_remove_matrix(&result);
  free(m.matrix);
  free(test.matrix);
} END_TEST

START_TEST(s21_inverse_error) {
  matrix_t m;
  matrix_t result;
  m.matrix = NULL;
  int res = s21_inverse_matrix(&m, &result);
  ck_assert_int_eq(res, INVALID_MATRIX);
} END_TEST

START_TEST(s21_inverse_error_2) {
  matrix_t m;
  matrix_t result;
  m.matrix = calloc(2, sizeof(double**));;
  double mat1[] = {4.0, 15.0, 44.0};
  double mat2[] = {6.0, 0.0, 20.0};
  m.matrix[0] = &mat1[0];
  m.matrix[1] = &mat2[0];
  m.rows = 2;
  m.columns = 3;
  int res = s21_inverse_matrix(&m, &result);
  ck_assert_int_eq(res, CALCULATION_ERROR);
  free(m.matrix);
} END_TEST

START_TEST(s21_inverse_mul) {
  matrix_t m;
  matrix_t result;
  matrix_t test;

  m.matrix = calloc(3, sizeof(double**));
  test.matrix = calloc(3, sizeof(double**));
  double mat[] = {2.0, 5.0, 7.0};
  double mat2[] = {6.0, 3.0, 4.0};
  double mat3[] = {5.0, -2.0, -3.0};
  m.matrix[0] = &mat[0];
  m.matrix[1] = &mat2[0];
  m.matrix[2] = &mat3[0];
  m.rows = 3;
  m.columns = 3;
  double t[] = {1.0, -1.0, 1.0};
  double t2[] = {-38.0, 41.0, -34.0};
  double t3[] = {27.0, -29.0, 24.0};
  test.matrix[0] = &t[0];
  test.matrix[1] = &t2[0];
  test.matrix[2] = &t3[0];
  test.rows = 3;
  test.columns = 3;
  s21_inverse_matrix(&m, &result);
  ck_assert_int_eq(s21_eq_matrix(&test, &result), 1);
  matrix_t result_test_mul;
  result_test_mul.matrix = calloc(3, sizeof(double**));
  double mul[] = {1.0, 0.0, 0.0};
  double mul2[] = {0.0, 1.0, 0.0};
  double mul3[] = {0.0, 0.0, 1.0};
  result_test_mul.matrix[0] = &mul[0];
  result_test_mul.matrix[1] = &mul2[0];
  result_test_mul.matrix[2] = &mul3[0];
  result_test_mul.rows = 3;
  result_test_mul.columns = 3;
  matrix_t result_mul;

  s21_mult_matrix(&result, &m, &result_mul);
  ck_assert_int_eq(s21_eq_matrix(&result_mul, &result_test_mul), 1);
  free(m.matrix);
  free(test.matrix);
  free(result_test_mul.matrix);
  s21_remove_matrix(&result_mul);
  s21_remove_matrix(&result);
} END_TEST


START_TEST(s21_inverse_null) {
  matrix_t m;
  matrix_t result;
  result.matrix = calloc(3, sizeof(double**));
  m.matrix = calloc(3, sizeof(double**));
  double mat[] = {0.0, 0.0, 0.0};
  double mat2[] = {0.0, 0.0, 0.0};
  double mat3[] = {0.0, 0.0, 0.0};
  m.matrix[0] = &mat[0];
  m.matrix[1] = &mat2[0];
  m.matrix[2] = &mat3[0];
  m.rows = 3;
  m.columns = 3;
  int res = s21_inverse_matrix(&m, &result);
  ck_assert_int_eq(res, CALCULATION_ERROR);
  free(m.matrix);
  free(result.matrix);
} END_TEST

START_TEST(s21_sum_normal) {
  matrix_t m;
  matrix_t m2;
  matrix_t result;
  matrix_t test;
  m.matrix = calloc(3, sizeof(double**));
  m2.matrix = calloc(3, sizeof(double**));
  test.matrix = calloc(3, sizeof(double**));
  double mat[] = {-1.0, 0.0};
  double mat2[] = {3.0, 8.0};
  double mat3[] = {5.0, -12.0};
  m.matrix[0] = &mat[0];
  m.matrix[1] = &mat2[0];
  m.matrix[2] = &mat3[0];
  m.rows = 3;
  m.columns = 2;
  double mat_1[] = {4.0, 15.0};
  double mat_2[] = {6.0, 0.0};
  double mat_3[] = {11.0, -3.0};
  m2.matrix[0] = &mat_1[0];
  m2.matrix[1] = &mat_2[0];
  m2.matrix[2] = &mat_3[0];
  m2.rows = 3;
  m2.columns = 2;
  double t[] = {3.0, 15.0};
  double t2[] = {9.0, 8.0};
  double t3[] = {16.0, -15.0};
  test.matrix[0] = &t[0];
  test.matrix[1] = &t2[0];
  test.matrix[2] = &t3[0];
  test.rows = 3;
  test.columns = 2;
  int res = s21_sum_matrix(&m, &m2, &result);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(s21_eq_matrix(&test, &result), 1);
  s21_remove_matrix(&result);
  free(m.matrix);
  free(m2.matrix);
  free(test.matrix);
} END_TEST

START_TEST(s21_sum_error) {
  matrix_t m;
  matrix_t m2;
  matrix_t result;
  m.matrix = NULL;
  m2.matrix = calloc(3, sizeof(double**));
  double mat_1[] = {4.0, 15.0};
  double mat_2[] = {6.0, 0.0};
  double mat_3[] = {11.0, -3.0};
  m2.matrix[0] = &mat_1[0];
  m2.matrix[1] = &mat_2[0];
  m2.matrix[2] = &mat_3[0];
  m2.rows = 3;
  m2.columns = 2;
  int res = s21_sum_matrix(&m, &m2, &result);
  ck_assert_int_eq(res, INVALID_MATRIX);
  free(m2.matrix);
} END_TEST

START_TEST(s21_sum_error_2) {
  matrix_t m;
  matrix_t m2;
  matrix_t result;
  m.matrix = calloc(2, sizeof(double**));;
  m2.matrix = calloc(3, sizeof(double**));
  double mat1[] = {4.0, 15.0};
  double mat2[] = {6.0, 0.0};
  m.matrix[0] = &mat1[0];
  m.matrix[1] = &mat2[0];
  m.rows = 2;
  m.columns = 2;
  double mat_1[] = {4.0, 15.0};
  double mat_2[] = {6.0, 0.0};
  double mat_3[] = {11.0, -3.0};
  m2.matrix[0] = &mat_1[0];
  m2.matrix[1] = &mat_2[0];
  m2.matrix[2] = &mat_3[0];
  m2.rows = 3;
  m2.columns = 2;
  int res = s21_sum_matrix(&m, &m2, &result);
  ck_assert_int_eq(res, CALCULATION_ERROR);
  s21_remove_matrix(&result);
  free(m2.matrix);
  free(m.matrix);
} END_TEST

START_TEST(s21_sub_normal) {
  matrix_t m;
  matrix_t m2;
  matrix_t result;
  matrix_t test;
  m.matrix = calloc(2, sizeof(double**));
  m2.matrix = calloc(2, sizeof(double**));
  test.matrix = calloc(2, sizeof(double**));
  double mat[] = {8.0, 9.0, -10.0};
  double mat2[] = {-3.0, -7.0, 0.0};
  m.matrix[0] = &mat[0];
  m.matrix[1] = &mat2[0];
  m.rows = 2;
  m.columns = 3;
  double mat_1[] = {5.0, 3.0, 0.0};
  double mat_2[] = {1.0, 1.0, -2.0};
  m2.matrix[0] = &mat_1[0];
  m2.matrix[1] = &mat_2[0];
  m2.rows = 2;
  m2.columns = 3;
  double t[] = {3.0, 6.0, -10.0};
  double t2[] = {-4.0, -8.0, 2.0};
  test.matrix[0] = &t[0];
  test.matrix[1] = &t2[0];
  test.rows = 2;
  test.columns = 3;
  int res = s21_sub_matrix(&m, &m2, &result);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(s21_eq_matrix(&test, &result), 1);
  s21_remove_matrix(&result);
  free(m.matrix);
  free(m2.matrix);
  free(test.matrix);
} END_TEST

START_TEST(s21_sub_error) {
  matrix_t m;
  matrix_t m2;
  matrix_t result;
  m.matrix = NULL;
  m2.matrix = calloc(3, sizeof(double**));
  double mat_1[] = {4.0, 15.0};
  double mat_2[] = {6.0, 0.0};
  double mat_3[] = {11.0, -3.0};
  m2.matrix[0] = &mat_1[0];
  m2.matrix[1] = &mat_2[0];
  m2.matrix[2] = &mat_3[0];
  m2.rows = 3;
  m2.columns = 2;
  int res = s21_sub_matrix(&m, &m2, &result);
  ck_assert_int_eq(res, INVALID_MATRIX);
  free(m2.matrix);
} END_TEST

START_TEST(s21_sub_error_2) {
  matrix_t m;
  matrix_t m2;
  matrix_t result;
  m.matrix = calloc(2, sizeof(double**));;
  m2.matrix = calloc(3, sizeof(double**));
  double mat1[] = {4.0, 15.0};
  double mat2[] = {6.0, 0.0};
  m.matrix[0] = &mat1[0];
  m.matrix[1] = &mat2[0];
  m.rows = 2;
  m.columns = 2;
  double mat_1[] = {4.0, 15.0};
  double mat_2[] = {6.0, 0.0};
  double mat_3[] = {11.0, -3.0};
  m2.matrix[0] = &mat_1[0];
  m2.matrix[1] = &mat_2[0];
  m2.matrix[2] = &mat_3[0];
  m2.rows = 3;
  m2.columns = 2;
  int res = s21_sub_matrix(&m, &m2, &result);
  ck_assert_int_eq(res, CALCULATION_ERROR);
  s21_remove_matrix(&result);
  free(m2.matrix);
  free(m.matrix);
} END_TEST

START_TEST(s21_mul_normal) {
  matrix_t m;
  matrix_t m2;
  matrix_t result;
  matrix_t test;
  m.matrix = calloc(2, sizeof(double**));
  m2.matrix = calloc(2, sizeof(double**));
  test.matrix = calloc(2, sizeof(double**));
  double mat[] = {3.0, -3.0};
  double mat2[] = {-1.0, 5.0};
  m.matrix[0] = &mat[0];
  m.matrix[1] = &mat2[0];
  m.rows = 2;
  m.columns = 2;
  double mat_1[] = {5.0, 3.0};
  double mat_2[] = {1.0, 3.0};
  m2.matrix[0] = &mat_1[0];
  m2.matrix[1] = &mat_2[0];
  m2.rows = 2;
  m2.columns = 2;
  double t[] = {12.0, 0.0};
  double t2[] = {0.0, 12.0};
  test.matrix[0] = &t[0];
  test.matrix[1] = &t2[0];
  test.rows = 2;
  test.columns = 2;
  int res = s21_mult_matrix(&m, &m2, &result);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(s21_eq_matrix(&test, &result), 1);
  s21_remove_matrix(&result);
  free(m.matrix);
  free(m2.matrix);
  free(test.matrix);
} END_TEST

START_TEST(s21_mul_error) {
  matrix_t m;
  matrix_t m2;
  matrix_t result;
  m.matrix = NULL;
  m2.matrix = calloc(3, sizeof(double**));
  double mat_1[] = {4.0, 15.0};
  double mat_2[] = {6.0, 0.0};
  double mat_3[] = {11.0, -3.0};
  m2.matrix[0] = &mat_1[0];
  m2.matrix[1] = &mat_2[0];
  m2.matrix[2] = &mat_3[0];
  m2.rows = 3;
  m2.columns = 2;
  int res = s21_mult_matrix(&m, &m2, &result);
  ck_assert_int_eq(res, INVALID_MATRIX);
  free(m2.matrix);
} END_TEST

START_TEST(s21_mul_error_2) {
  matrix_t m;
  matrix_t m2;
  matrix_t result;
  m.matrix = calloc(2, sizeof(double**));;
  m2.matrix = calloc(3, sizeof(double**));
  double mat1[] = {4.0, 15.0};
  double mat2[] = {6.0, 0.0};
  m.matrix[0] = &mat1[0];
  m.matrix[1] = &mat2[0];
  m.rows = 2;
  m.columns = 2;
  double mat_1[] = {4.0, 15.0};
  double mat_2[] = {6.0, 0.0};
  double mat_3[] = {11.0, -3.0};
  m2.matrix[0] = &mat_1[0];
  m2.matrix[1] = &mat_2[0];
  m2.matrix[2] = &mat_3[0];
  m2.rows = 3;
  m2.columns = 2;
  int res = s21_mult_matrix(&m, &m2, &result);
  ck_assert_int_eq(res, CALCULATION_ERROR);
  free(m2.matrix);
  free(m.matrix);
} END_TEST

START_TEST(s21_mul_numb_normal) {
  matrix_t m;
  matrix_t result;
  matrix_t test;
  m.matrix = calloc(3, sizeof(double**));
  test.matrix = calloc(3, sizeof(double**));
  double mat[] = {1.0, 4.0, 7.0};
  double mat2[] = {2.0, 5.0, 8.0};
  double mat3[] = {3.0, 6.0, 9.0};
  m.matrix[0] = &mat[0];
  m.matrix[1] = &mat2[0];
  m.matrix[2] = &mat3[0];
  m.rows = 2;
  m.columns = 2;
  double t[] = {2.0, 8.0, 14.0};
  double t2[] = {4.0, 10.0, 16.0};
  double t3[] = {6.0, 12.0, 18.0};
  test.matrix[0] = &t[0];
  test.matrix[1] = &t2[0];
  test.matrix[2] = &t3[0];
  test.rows = 2;
  test.columns = 2;
  int res = s21_mult_number(&m, 2.0, &result);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(s21_eq_matrix(&test, &result), 1);
  s21_remove_matrix(&result);
  free(m.matrix);
  free(test.matrix);
} END_TEST

START_TEST(s21_mul_numb_error) {
  matrix_t m;
  matrix_t result;
  double a = 0.1;
  m.matrix = NULL;
  int res = s21_mult_number(&m, a, &result);
  ck_assert_int_eq(res, INVALID_MATRIX);
} END_TEST

START_TEST(s21_eq_matrix_normal) {
  matrix_t m;
  matrix_t m2;
  m.matrix = calloc(2, sizeof(double**));
  m2.matrix = calloc(2, sizeof(double**));
  double mat[] = {3.0, -3.0};
  double mat2[] = {-1.0, 5.0};
  m.matrix[0] = &mat[0];
  m.matrix[1] = &mat2[0];
  m.rows = 2;
  m.columns = 2;
  double mat_1[] = {5.0, 3.0};
  double mat_2[] = {1.0, 3.0};
  m2.matrix[0] = &mat_1[0];
  m2.matrix[1] = &mat_2[0];
  m2.rows = 2;
  m2.columns = 2;
  int res = s21_eq_matrix(&m, &m2);
  ck_assert_int_eq(res, 0);
  free(m.matrix);
  free(m2.matrix);
} END_TEST

START_TEST(s21_eq_matrix_error) {
  matrix_t m;
  matrix_t m2;
  m.matrix = NULL;
  m2.matrix = calloc(2, sizeof(double**));
  double mat_1[] = {5.0, 3.0};
  double mat_2[] = {1.0, 3.0};
  m2.matrix[0] = &mat_1[0];
  m2.matrix[1] = &mat_2[0];
  m2.rows = 2;
  m2.columns = 2;
  int res = s21_eq_matrix(&m, &m2);
  ck_assert_int_eq(res, 0);
  free(m2.matrix);
} END_TEST

START_TEST(s21_eq_matrix_error_2) {
  matrix_t m;
  matrix_t m2;
  m.matrix = calloc(2, sizeof(double**));
  m2.matrix = calloc(2, sizeof(double**));
  double mat1[] = {4.0, 15.0, 44.0};
  double mat2[] = {6.0, 0.0, 20.0};
  m.matrix[0] = &mat1[0];
  m.matrix[1] = &mat2[0];
  m.rows = 2;
  m.columns = 3;
  double mat_1[] = {5.0, 3.0};
  double mat_2[] = {1.0, 3.0};
  m2.matrix[0] = &mat_1[0];
  m2.matrix[1] = &mat_2[0];
  m2.rows = 2;
  m2.columns = 2;
  int res = s21_eq_matrix(&m, &m2);
  ck_assert_int_eq(res, 0);
  free(m.matrix);
  free(m2.matrix);
} END_TEST

START_TEST(s21_transpose_normal) {
  matrix_t m;
  matrix_t m2;
  matrix_t result;
  m.matrix = calloc(2, sizeof(double**));
  m2.matrix = calloc(3, sizeof(double**));
  double mat[] = {3.0, -3.0, 1.0};
  double mat2[] = {-1.0, 5.0, 2.0};
  m.matrix[0] = &mat[0];
  m.matrix[1] = &mat2[0];
  m.rows = 2;
  m.columns = 3;
  double mat_1[] = {3.0, -1.0};
  double mat_2[] = {-3.0, 5.0};
  double mat_3[] = {1.0, 2.0};
  m2.matrix[0] = &mat_1[0];
  m2.matrix[1] = &mat_2[0];
  m2.matrix[2] = &mat_3[0];
  m2.rows = 3;
  m2.columns = 2;
  s21_transpose(&m, &result);
  int res = s21_eq_matrix(&result, &m2);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&result);
  free(m.matrix);
  free(m2.matrix);
} END_TEST

START_TEST(s21_transpose_error) {
  matrix_t m;
  matrix_t m2;
  m.matrix = NULL;
  int res = s21_transpose(&m, &m2);
  ck_assert_int_eq(res, INVALID_MATRIX);
} END_TEST


Suite* s21_matrix_suite() {
  Suite* s;

  TCase *tc_create_matrix, *tc_determinant, *tc_calc_complements, *tc_inverse, \
  *tc_sum, *tc_sub, *tc_mul, *tc_mul_numb, *tc_eq_matrix, *tc_transpose;
  s = suite_create("s21_matrix");

  tc_eq_matrix = tcase_create("s21_eq_matrix");
  tcase_add_test(tc_eq_matrix, s21_eq_matrix_normal);
  tcase_add_test(tc_eq_matrix, s21_eq_matrix_error);
  tcase_add_test(tc_eq_matrix, s21_eq_matrix_error_2);
  suite_add_tcase(s, tc_eq_matrix);

  tc_transpose = tcase_create("s21_transpose");
  tcase_add_test(tc_transpose, s21_transpose_normal);
  tcase_add_test(tc_transpose, s21_transpose_error);
  suite_add_tcase(s, tc_transpose);

  tc_sum = tcase_create("s21_sum");
  tcase_add_test(tc_sum, s21_sum_normal);
  tcase_add_test(tc_sum, s21_sum_error);
  tcase_add_test(tc_sum, s21_sum_error_2);
  suite_add_tcase(s, tc_sum);

  tc_sub = tcase_create("s21_sub");
  tcase_add_test(tc_sub, s21_sub_normal);
  tcase_add_test(tc_sub, s21_sub_error);
  tcase_add_test(tc_sub, s21_sub_error_2);
  suite_add_tcase(s, tc_sub);

  tc_mul = tcase_create("s21_mul");
  tcase_add_test(tc_mul, s21_mul_normal);
  tcase_add_test(tc_mul, s21_mul_error);
  tcase_add_test(tc_mul, s21_mul_error_2);
  suite_add_tcase(s, tc_mul);

  tc_mul_numb = tcase_create("s21_mul_numb");
  tcase_add_test(tc_mul_numb, s21_mul_numb_normal);
  tcase_add_test(tc_mul_numb, s21_mul_numb_error);
  suite_add_tcase(s, tc_mul_numb);

  tc_create_matrix = tcase_create("s21_create");
  tcase_add_test(tc_create_matrix, s21_create_normal);
  tcase_add_test(tc_create_matrix, s21_create_error);
  suite_add_tcase(s, tc_create_matrix);

  tc_determinant = tcase_create("s21_determinant");
  tcase_add_test(tc_determinant, s21_determinant_normal);
  tcase_add_test(tc_determinant, s21_determinant_normal_2);
  tcase_add_test(tc_determinant, s21_determinant_normal_4_by_4);
  tcase_add_test(tc_determinant, s21_determinant_normal_5_by_5);
  tcase_add_test(tc_determinant, s21_determinant_error);
  tcase_add_test(tc_determinant, s21_determinant_error_2);
  suite_add_tcase(s, tc_determinant);

  tc_calc_complements = tcase_create("s21_calc_complements");
  tcase_add_test(tc_calc_complements, s21_complements_normal);
  tcase_add_test(tc_calc_complements, s21_complements_4_by_4);
  tcase_add_test(tc_calc_complements, s21_complements_3_by_3);
  tcase_add_test(tc_calc_complements, s21_complements_error);
  tcase_add_test(tc_calc_complements, s21_complements_error_2);
  suite_add_tcase(s, tc_calc_complements);

  tc_inverse = tcase_create("s21_inverse");
  tcase_add_test(tc_inverse, s21_inverse_normal);
  tcase_add_test(tc_inverse, s21_inverse_null);
  tcase_add_test(tc_inverse, s21_inverse_mul);
  tcase_add_test(tc_inverse, s21_inverse_1_by_1);
  tcase_add_test(tc_inverse, s21_inverse_error);
  tcase_add_test(tc_inverse, s21_inverse_error_2);
  suite_add_tcase(s, tc_inverse);
  return s;
}


int main() {
  int no_failed = 0;
  Suite* s;
  SRunner* runner;

  s = s21_matrix_suite();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
