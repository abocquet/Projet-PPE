//
//  Matrix.h
//  Matrices
//

#ifndef __Matrices__Matrix__
#define __Matrices__Matrix__

#include <stdlib.h>
#include <stdio.h>
#include "Matrix.struct.h"

Matrix* new_matrix(unsigned int width, unsigned int height);

Matrix* sum_matrix(Matrix* m1, Matrix* m2);

Matrix* product_matrix(Matrix* m1, Matrix* m2);

void del_matrix(Matrix* matrix);

void print_matrix(Matrix* matrix);

void set_matrix(Matrix *matrix, int x, int y, double val);

#endif /* defined(__Matrices__Matrix__) */
