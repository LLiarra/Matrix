#include "../s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  if (s21_not_valid(A)) {
    return INVALID_MATRIX;
  }
  if (A->columns != A->rows) {
    return CALCULATION_ERROR;
  }
  *result = s21_get_determinant(A, A->rows);
  return OK;
}

double s21_get_determinant(matrix_t* matrix, int size) {
  double det = 0.0;
  int degree = 1;
  if (size == 1) {
    return matrix->matrix[0][0];
  } else if (size == 2) {
    return matrix->matrix[0][0] * matrix->matrix[1][1] - (matrix->matrix[0][1] * matrix->matrix[1][0]);
  } else if (size > 2) {
    matrix_t new_matrix = {0};
    for (int j = 0; j < size; j++) {
      s21_create_minor_matrix(matrix, size, 0, j, &new_matrix);
      det += degree * (matrix->matrix[0][j] * s21_get_determinant(&new_matrix, size - 1));
      degree *= (-1);
      s21_remove_matrix(&new_matrix);
    }
  }
  return det;
}
