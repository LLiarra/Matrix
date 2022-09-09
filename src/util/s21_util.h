#ifndef SRC_UTIL_S21_UTIL_H_
#define SRC_UTIL_S21_UTIL_H_

#include <stdlib.h>
#include <math.h>

typedef struct matrix_struct {
  double** matrix;
  int rows;
  int columns;
} matrix_t;


enum {
  OK,
  INVALID_MATRIX,
  CALCULATION_ERROR,
  CALLOC_ERROR
};

#define EPS 1e-6

//  matrix helpers
int s21_not_valid(matrix_t* A);
int s21_create_minor_matrix(matrix_t* A, int size, int row, int column, matrix_t* B);
void s21_create_complements_matrix(matrix_t* A, matrix_t* result);
double s21_get_determinant(matrix_t* matrix, int size);

#endif  //  SRC_UTIL_S21_UTIL_H_
