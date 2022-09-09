#include "../s21_matrix.h"
/**
 * Вычисление методом матрицы алгебраических дополнений 
 */
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (s21_not_valid(A)) {
    return INVALID_MATRIX;
  }
  if (A->rows != A->columns) {
    return CALCULATION_ERROR;
  }
  double det = 0.0;
  s21_determinant(A, &det);
  if (fabs(det) < EPS) {
    return CALCULATION_ERROR;
  }
  matrix_t complements = {0};
  matrix_t invers = {0};

  int size = A->rows;
  s21_create_matrix(size, size, result);

  s21_calc_complements(A, &complements);
  s21_transpose(&complements, &invers);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      result->matrix[i][j] = invers.matrix[i][j] / det;
    }
  }
  s21_remove_matrix(&invers);
  s21_remove_matrix(&complements);
  return OK;
}
