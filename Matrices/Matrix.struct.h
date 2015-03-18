//
//  Matrix.struct.h
//  Matrices
//

#ifndef Matrices_Matrix_struct_h
#define Matrices_Matrix_struct_h

typedef struct Matrix Matrix;
struct Matrix {
	
	int width ;
	int height ;
	
	double **cells ;
	
};

#endif
