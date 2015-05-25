//
//  Matrix.c
//  Pilote
//

#include "Matrix.h"

void matrix_col_copy(double from[SIZE], double to[SIZE]){
	for (int i = 0; i < SIZE; i++) {
		to[i] = from[i];
	}
}

void matrix_col_sum(double A[SIZE], double B[SIZE], double res[SIZE])
{
	for (int i = 0; i < SIZE; i++) {
		res[i] = A[i] + B[i];
	}
}

void matrix_col_diff(double A[SIZE], double B[SIZE], double res[SIZE])
{
	for (int i = 0; i < SIZE; i++) {
		res[i] = A[i] - B[i];
	}
}

void matrix_k(double m[SIZE], double k, double res[SIZE]){

	for (int i = 0; i < SIZE ; i++) {
		res[i] = m[i] * k ;
	}
	
}

void matrix_product(double a[SIZE], double B[SIZE][SIZE], double res[SIZE])
{
	double A[SIZE];
	
	/*
	 * on copie les données de la matrice colonne donnée en argument
	 * ainsi s'il s'agit de la même matrice que res
	 * on évite les erreurs dues à la lecture de cette matrice
	 * alors qu'elle est modifiée
	 */
	 
	for(int i = 0 ; i < SIZE ; i++){
		A[i] = a[i] ;
	}
	
	for(int y = 0 ; y < SIZE ; y++){
		res[y] = 0 ;
		
		for(int i = 0 ; i < SIZE ; i++){
			res[y] += B[i][y] * A[i] ;
		}
	}
	
}

void matrix_col_print(double* m)
{
	for (int i = 0 ; i < SIZE; i++) {
		printf("%f ", m[i]);
	}
	printf("\n");
}

void matrix_rect_print(double m[SIZE][SIZE]){
	for(int x = 0 ; x < SIZE ; x++){
		for(int y = 0 ; y < SIZE ; y++){
			printf("%f ", m[x][y]);
		}
		printf("\n");
	}
	printf("\n");
}