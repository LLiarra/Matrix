#include "../s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (s21_not_valid(A) || s21_not_valid(B)) {
    return INVALID_MATRIX;
  }
  res = s21_create_matrix(A->rows, A->columns, result);
  if ((A->rows == B->rows) && (A->columns == B->columns) && !res) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
         result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  } else {
    res = CALCULATION_ERROR;
  }
  return res;
}
