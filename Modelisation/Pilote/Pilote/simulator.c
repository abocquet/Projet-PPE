//
//  simulator.c
//  Pilote
//

#include "simulator.h"

int acquerir_angle_nord(){
	return (int)round(angle_nord) ;
}

double get_delta_t(){
	return delta_t ;
}

void adapter_propulsion(int norme, double angle_gauche, double angle_droit){
		
	motor_power = norme ;
	angle_moteur_gauche = angle_gauche ;
	angle_moteur_droit  = angle_droit;
}

void acquerir_acceleration(double* acceleration){
	
	double nouvelle_vitesse[3] = {0} ;
	double norme_propulsion = motor_power * norme_moteur_max / 100 ;
	
	double prop_y = (angle_moteur_gauche * angle_moteur_droit >= 0 ? cos(-angle_moteur_gauche + HALF_PI)*norme_propulsion : 0); // Si les moteurs ne sont pas dans le même sens, on a pas de propulsion en translation
	double prop_z = norme_propulsion * sin(angle_moteur_gauche + HALF_PI);
	
	nouvelle_vitesse[0] = vitesse[0] ;
	nouvelle_vitesse[1] = vitesse[1] + (-Kx * pow(vitesse[1],2) +  prop_y) / masse * delta_t ;
	nouvelle_vitesse[2] = vitesse[2] + ((vitesse[2] > 0 ? -1 : 1) * Kz * pow(vitesse[2],2) - gravite * (masse - helium) + prop_z) / masse * delta_t ; // les frottements sont opposés au sens de la vitesse
	
	if(angle_moteur_gauche * angle_moteur_droit < 0)//si les moteurs ont un sens différent
	{
		/**
		 *
		 *	Selon le cahier des charges, on doit aller à 0.1 rad/s soit 6°/s environ
		 *	pour simplifier ce raisonnement, on admettra que cette contrainte est toujours respectée
		 *
		 */
		angle_nord += 6 * (angle_moteur_gauche < 0 ? 1 : -1) * delta_t;
		
		if(angle_nord < 0){
			angle_nord += 360 ;
		}
		
		if(angle_nord > 360){
			angle_nord -= 360 ;
		}		
	}
	
	//En deçà d'une certaine vitesse, on considère que le ballon est stoppé par l'air
	if(fabs(vitesse[1]) < 0.01 && sqrt(fabs(prop_y/Kx)) < 0.01){
		nouvelle_vitesse[1] = 0 ;
	}
	
	for (int i = 0 ; i < 3; i++) {
		acceleration[i] = (nouvelle_vitesse[i]-vitesse[i]) / delta_t ;
		vitesse[i] = nouvelle_vitesse[i];
	}
	
	
}

/** Fonctions de traçage des données
 *
 * acceleration, vitesse: acceleration et vitesse du dirigeable dans le repère du dirigeable
 * position: position du dirigeable dans le repère de référence
 * cible_rel: position de la destination dans le référentiel du dirigeable
 * propulsion: force de propulsion demandée, en %
 * angle_gauche, angele_droite: angle des moteurs par rapport à la verticale
 *
 * unités SI sauf contre-indication
 */
void setup_log(){
	log_file = fopen("log.csv", "w+");
	
	if (log_file == NULL){
		printf("Impossible d'ouvrir le fichier de log");
	}
	else {
		fputs("t;acceleration_x;acceleration_y;acceleration_z;vitesse_x;vitesse_y;vitesse_z;position_x;position_y;position_z;cible_rel_x;cible_rel_y;cible_rel_z;propulsion_verticale;propulsion_horizontale;angle_gauche;angle_droite;angle_nord\n", log_file);
	}
}

void close_log(){
	fclose(log_file);
}

void add_log(double* acceleration, double* vitesse, double* position, double* target_rel, double prop_z, double prop_x, double angle_gauche, double angle_droit, double angle_nord){
	current_time += delta_t ;
	
	fprintf(log_file, "%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;\n", current_time, acceleration[0], acceleration[1], acceleration[2], vitesse[0], vitesse[1], vitesse[2], position[0], position[1], position[2], target_rel[0], target_rel[1], target_rel[2], prop_z, prop_x, angle_gauche, angle_droit, angle_nord);
	
}

int isClose(double value, double ref, double marge)
{
	return value > ref - marge && value < ref + marge ? 1 : 0 ;
}
