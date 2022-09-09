#include "../s21_matrix.h"

int s21_calc_complements(matrix_t* A, matrix_t* result) {
  int res = OK;
  if (s21_not_valid(A)) {
    return INVALID_MATRIX;
    }
  if (A->columns != A->rows) {
    return CALCULATION_ERROR;
    }
  res = s21_create_matrix(A->rows, A->columns, result);
  if (!res) {
    s21_create_complements_matrix(A, result);
  }
  return res;
}

void s21_create_complements_matrix(matrix_t* A, matrix_t* result) {
  int size = A->rows;
  matrix_t new_matrix = { 0 };
  int degree = 1;
  if (size == 1) {
    result->matrix[0][0] = 1;
  } else {
    for (int i = 0; i < size; i++) {
      degree = i % 2 ? -1 : 1;
      for (int j = 0; j < size; j++) {
        s21_create_minor_matrix(A, size, i, j, &new_matrix);
        double temp =  s21_get_determinant(&new_matrix, size - 1);
        result->matrix[i][j] = degree * temp;
        degree *= (-1);
        s21_remove_matrix(&new_matrix);
      }
    }
  }
}
