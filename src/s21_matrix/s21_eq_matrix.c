#include "../s21_matrix.h"

#define SUCCESS 1
#define FAILURE 0

int s21_eq_matrix(matrix_t* A, matrix_t* B) {
  int result = SUCCESS;
  if (s21_not_valid(A) || s21_not_valid(B)) {
    return FAILURE;
  }
  if ((A->rows == B->rows) && (A->columns == B->columns)) {
    for (int i = 0; i < A->rows; i++) {
      int flag = 0;
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
          result = FAILURE;
          flag = 1;
          break;
        }
      }
      if (flag == 1) {
        break;
      }
    }
  } else {
    result = FAILURE;
  }
  return result;
}
