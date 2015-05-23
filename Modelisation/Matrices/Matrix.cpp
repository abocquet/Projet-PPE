//
//  Matrix.cpp
//  Matrices
//

#include "Matrix.h"

Matrix* new_matrix(unsigned int width, unsigned int height)
{
	if(width <= 0 || height <= 0){
		exit(0);
	}
	
	Matrix* matrix  = (Matrix*)malloc(sizeof(Matrix));
	
	matrix->width = width ;
	matrix->height = height ;
	
	matrix->cells = malloc(width * sizeof(double*));
	
	for (int i = 0; i < width; i++) {
		matrix->cells[i] = malloc(height * sizeof(double));
	}
	
	
	return matrix ;
};


Matrix* sum_matrix(Matrix* m1, Matrix* m2){
	
	if(m1->width != m2->width || m1->height != m2->height){
		exit(0);
	}
	
	Matrix* sum = new_matrix(m1->width, m1->height);
	
	for(int x = 0 ; x < sum->height ; x++){
		for(int y = 0 ; y < sum->width ; y++){
			sum->cells[x][y] = m1->cells[x][y] + m2->cells[x][y] ;
		}
	}
	
	return sum ;
}

Matrix* product_matrix(Matrix* m1, Matrix* m2){
	
	if(m1->height != m2->width){
		exit(0);
	}
	
	Matrix* product = new_matrix(m1->width, m1->height);
	
	for(int x = 0 ; x < product->height ; x++){
		for(int y = 0 ; y < product->width ; y++){
			product->cells[x][y] = 0 ;
			
			for(int i = 0 ; i < m1->height ; i++){
				product->cells[x][y] += m1->cells[i][y] * m2->cells[x][i] ;
			}
		}
	}
	
	return product ;
}

void del_matrix(Matrix* matrix)
{
	
	for (int i = 0; i < matrix->width; i++) {
		free(matrix->cells[i]);
	}
	
	free(matrix->cells);
	free(matrix);
}

void print_matrix(Matrix* matrix)
{
	
	for(int i = 0 ; i < matrix->height ; i++)
	{
		for(int j = 0 ; j < matrix->width ; j++){
			printf("%f ", matrix->cells[j][i]);
		}
		printf("\n");
	}
	printf("\n");
}

void set_matrix(Matrix *matrix, int x, int y, double val)
{
	matrix->cells[x][y] = val ;
}