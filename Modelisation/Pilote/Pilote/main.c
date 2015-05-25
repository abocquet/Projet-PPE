//
//  main.c
//  Pilote
//

#include <stdio.h>
#include <math.h>
#include "Matrix.h"
#include "simulator.h"

#define PI 3.14159265

int isClose(double, double , double);

int main(int argc, const char * argv[]) {
	
	setup_log();
	
	double destination[3] = {20, 10, 3} ;
	
	double vitesse[3] = {0} ;
	double position[3] = {0} ;
	
	double propulsion_verticale = 0, propulsion_horizontale = 0 ;
	
	int  i = 1;
	
	do {
		double delta_t = get_delta_t(); ;
		
		double acceleration[3];
		double deplacement[3] = { 0 };
		
		acquerir_acceleration(acceleration);
		
		double v0[3];
		matrix_col_copy(vitesse, v0);
		
		// vitesse = acceleration * ∆t + v0
			matrix_k(acceleration, delta_t, acceleration);
			matrix_col_sum(acceleration, v0, vitesse);
		
		// vitesse = 1/2 . acceleration * ∆t^2 + v0 . ∆t
			matrix_k(acceleration, delta_t, acceleration);
			matrix_k(acceleration, 0.5, acceleration);
		
			matrix_k(v0, delta_t, v0);
		
			matrix_col_sum(deplacement, acceleration, deplacement);
			matrix_col_sum(deplacement, v0, deplacement);
		
		//matrix_col_print(acceleration);
		//matrix_col_print(vitesse);
		
		//On calcul la nouvelle position du dirigeable
			double θ = acquerir_angle_nord() / (2 * PI) ; //conversion degré/radians
		
			double matrice_passage[3][3] = {
				{ cos(θ), sin(θ),  0 },
				{ -sin(θ), cos(θ), 0 },
				{	0	 ,	0	 , 1 }
			};
		
			matrix_product(deplacement, matrice_passage, deplacement); //on calcul les coordonées de d dans (i,j)
			matrix_col_sum(deplacement, position, position); // on ajoute le déplacement à la position du dirigeable
		
		// et on agit en fonction
		
			//on inverse la matrice de passage afin d'aller de (i, j) vers (k, l)
			matrice_passage[0][1] *= -1 ;
			matrice_passage[1][0] *= -1 ;
		
			//les coordonées de la destination, dans le référentiel du ballon
			double dest[3] ;
			matrix_col_copy(destination, dest) ;
			matrix_col_diff(dest, position, dest);
			matrix_product(dest, matrice_passage, dest);
		
			char tourner = 0 ;
			double angle_destination = atan(dest[0]/dest[1]);
			double distance_destination = sqrt(pow(dest[0], 2) + pow(dest[1], 2));
		
			if(distance_destination > 0.1){
				if(dest[1] > 0 && isClose(angle_destination, 0, PI/16)){
					if(vitesse[1] > .1 && acceleration[1] > 0){
						propulsion_horizontale -= .1 ;
					}
						
					if(vitesse[1] < .1){
						propulsion_horizontale += .1 ;
					}
				}
				else {
					propulsion_horizontale = .2 ;
					
					if(dest[0] < 0){
						tourner = -1 ;
					}
					else if(dest[0] > 0){
						tourner = 1 ;
					}
				}
			}
			else {
				if (vitesse[1] > 0.01) { //on ralenti à l'approche de l'objectif
					propulsion_horizontale = -7 ;
				}
				else {
					propulsion_horizontale = 0 ;
				}
			}
		
			printf("%f %d\n",angle_destination, tourner);
		
			// on adapte la propulsion verticale
			/*if(position[2] < destination[2]){
				if(vitesse[2] > 0.1){
					if(acceleration[2] > .1){
						propulsion_verticale -= 10 ;
					}
					else {
						propulsion_verticale -= 1 ;
					}
				}
				
				if(vitesse[2] < .1){
					if(acceleration[2] < 0){
						propulsion_verticale += 10 ;
					}
					else {
						propulsion_verticale += 1 ;
					}
				}
			}
			else {
				if(vitesse[2] < -.1){
					propulsion_verticale += 1 ;
				}
				else {
					propulsion_verticale = 0 ;
				}
			}*/
		
		
			//On réajuste ensuite les demandes moteur
				if(propulsion_verticale > 100){
					propulsion_verticale = 100 ;
				}
				else if(propulsion_verticale < 1){
					propulsion_verticale = 1 ;
				}
		
				if(propulsion_horizontale > 100){
					propulsion_horizontale = 100 ;
				}
				else if(propulsion_horizontale < -100){
					propulsion_horizontale = -100 ;
				}
		
			double norme = sqrt(pow(propulsion_verticale,2) + pow(propulsion_horizontale,2)) ;
		
			if(norme > 100){
				norme = 100 ;
				int signe = propulsion_horizontale < 0 ? -1 : 1 ;
				propulsion_horizontale = signe * sqrt(pow(norme, 2) - pow(propulsion_verticale,2)) ;
				
			}
		
			double angle_moteur_gauche = atan(propulsion_horizontale / propulsion_verticale) ;
			double angle_moteur_droit = angle_moteur_gauche ;
		
			if(tourner != 0){
				angle_moteur_gauche *= tourner ;
				angle_moteur_droit *= -tourner ;
			}
		
			adapter_propulsion(norme, angle_moteur_gauche, angle_moteur_droit);
		
		
		if(i % 5 == 0){ //On complète le log toutes les 5 périodes
			add_log(acceleration, vitesse, position, destination, propulsion_verticale, propulsion_horizontale, angle_moteur_gauche, angle_moteur_droit, angle_nord);
		}
		
	} while(i++ < 1000) ;
		
	matrix_col_print(vitesse);
	matrix_col_print(position);
	
	close_log();
	
    return 0;
}
			
