//
//  Matrix.c
//  Pilote
//

#include "Matrix.h"

void sum_col_matrix(double A[2], double B[2], double res[2])
{
	for (int i = 0; i < 2; i++) {
		res[i] = A[i] + B[i];
	}
}

void product_matrix(double a[2], double B[2][2], double res[2])
{
	double A[2];
	
	/*
	 * on copie les données de la matrice colonne donnée en argument
	 * ainsi s'il s'agit de la même matrice que res
	 * on évite les erreurs dues à la lecture de cette matrice
	 * alors qu'elle est modifiée
	 *
	 */
	 
	for(int i = 0 ; i < 2 ; i++){
		A[i] = a[i] ;
	}
	
	for(int y = 0 ; y < 2 ; y++){
		res[y] = 0 ;
		
		for(int i = 0 ; i < 2 ; i++){
			res[y] += B[i][y] * A[i] ;
		}
	}
	
}

void print_col_matrix(double* m)
{
	for (int i = 0 ; i < 2; i++) {
		printf("%f\n", m[i]);
	}
	printf("\n");
}

void print_rect_matrix(double m[2][2]){
	for(int x = 0 ; x < 2 ; x++){
		for(int y = 0 ; y < 2 ; y++){
			printf("%f ", m[x][y]);
		}
		printf("\n");
	}
	printf("\n");
}