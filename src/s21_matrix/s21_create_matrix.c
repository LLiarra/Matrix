#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = OK;
  if (rows <= 0 || columns <= 0) {
    return INVALID_MATRIX;
  }
  result->rows = rows;
  result->columns = columns;
  result->matrix = (double**)calloc(rows, sizeof(double*));
  if (!result->matrix) {
    return CALLOC_ERROR;
  }
  for (int i = 0; i < rows; i++) {
    result->matrix[i] = (double*)calloc(columns, sizeof(double));
    if (!result->matrix[i]) {
      s21_remove_matrix(result);
      return CALLOC_ERROR;
    }
  }
  return res;
}
