//
//  main.c
//  Matrices
//

#include <stdlib.h>
#include <stdio.h>
#include "Matrix.h"

int main(int argc, const char * argv[]) {
	
	Matrix* mat1 = new_matrix(3, 3);
	Matrix* mat2 = new_matrix(3, 3);
	
	int c = 1 ;
	for(int i = 0 ; i < mat1->height ; i++){
		for(int j = 0 ; j < mat2->width ; j++){
			set_matrix(mat2, i, j, (double)c);
			c++ ;
		}
	}
	
	Matrix* sum = product_matrix(mat1, mat2);
	
	print_matrix(mat1);
	print_matrix(mat2);
	print_matrix(sum);
	
	del_matrix(mat1);
	del_matrix(mat2);
	del_matrix(sum);
	
    return 0;
}
