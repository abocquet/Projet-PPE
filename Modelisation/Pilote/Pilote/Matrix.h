//
//  Matrix.h
//  Pilote
//

#ifndef __Pilote__Matrix__
#define __Pilote__Matrix__

#define SIZE 3

#include <stdio.h>
#include <stdlib.h>

void matrix_col_copy(double from[SIZE], double to[SIZE]);

void matrix_col_sum(double m1[SIZE], double m2[SIZE], double res[SIZE]);
void matrix_col_diff(double m1[SIZE], double m2[SIZE], double res[SIZE]);

void matrix_product(double m1[SIZE], double m2[SIZE][SIZE], double res[SIZE]);
void matrix_k(double m[SIZE], double k, double res[SIZE]);

void matrix_col_print(double* m);
void matrix_rect_print(double m[SIZE][SIZE]);

#endif /* defined(__Pilote__Matrix__) */
