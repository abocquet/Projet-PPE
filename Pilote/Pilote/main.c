//
//  main.c
//  Pilote
//

#include <stdio.h>
#include <math.h>
#include "Matrix.h"

#define PI 3.14159265

void calculer_deplacement(double* d){
	d[0] = 1 ;
	d[1] = 0 ;
}

void adapter_propulsion(unsigned char a, unsigned char g, unsigned char d)
{
	printf("%d %d %d \n", a, g, d);
}

int main(int argc, const char * argv[]) {
	
	double d[2] = {0, 0} ;
	double p[2] = {0, 0} ;
	double t[2] = {0, 10} ;
	
	int  i = 1;
	
	unsigned char avancer = 0, tourner_gauche = 0 , tourner_droite = 0 ;
	
	do {
	
		//On calcul la nouvelle position du dirigeable
			double θ = 0 ;
			calculer_deplacement(d);
		
			double matrice_passage[2][2] = {
				{ cos(θ), sin(θ) },
				{ -sin(θ), cos(θ) }
			};
		
			product_matrix(d, matrice_passage, d); //on calcul les coordonées de d dans (i, j)
			sum_col_matrix(d, p, p); // on ajoute le déplacement à la position du dirigeable
		
		// et on agit en fonction
		
			//on inverse la matrice de passage afin d'aller de (i, j) vers (k, l)
			matrice_passage[0][1] *= -1 ;
			matrice_passage[1][0] *= -1 ;
		
			double tr[2];
			product_matrix(t, matrice_passage, tr);
		
			//print_col_matrix(tr);
			//print_col_matrix(d);

		
			if(tr[0] == 0){
			
				if(tr[1] > 0) { avancer = 1 ; }
				else if(tr[1] < 0){ tourner_gauche = 1 ; }
			
			}
			else {
			
				if(tr[0] > 0){ tourner_droite = 1 ; }
				if(tr[0] < 0){ tourner_gauche = 1 ; }
		
			}
		
			adapter_propulsion(avancer, tourner_gauche, tourner_droite);
		
	} while(i++ < 5) ;
	
	
	print_col_matrix(p);
	
    return 0;
}
