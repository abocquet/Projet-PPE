//
//  Matrix.h
//  Pilote
//

#ifndef __Pilote__Matrix__
#define __Pilote__Matrix__

#include <stdio.h>
#include <stdlib.h>

void sum_col_matrix(double m1[2], double m2[2], double res[2]);

void product_matrix(double m1[2], double m2[2][2], double res[2]);

void print_col_matrix(double* m);
void print_rect_matrix(double m[2][2]);

#endif /* defined(__Pilote__Matrix__) */
