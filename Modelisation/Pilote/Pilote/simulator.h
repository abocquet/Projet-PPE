//
//  simulator.h
//  Pilote
//

#ifndef __Pilote__simulator__
#define __Pilote__simulator__

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define HALF_PI 1.570796326794897

// Variables liées aux caractéristiques physiques du dirigeable
// et de l'environnement

static const double masse = 1 ;
static const double helium= 0.873 ;

static const double Cx = 0.45 ;
static const double Sx = 1.35 ;

static const double Cz = 1.32 ;
static const double Sz = 1.35 ;

static const double densite_air = 1.2 ;
static const double gravite = 9.81 ;

static const double Kx = 0.5 * Cx * Sx * densite_air ;
static const double Kz = 0.5 * Cz * Sz * densite_air ;

// Caractéristiques des moteurs
static const int norme_moteur_max = 20 ;
static int motor_power = 0 ; // L'utilisation en % de la puissance totale des moteurs

static double angle_moteur_gauche = 0 ;
static double angle_moteur_droit = 0 ;

//Données de vol

static const double delta_t = 0.2 ;
static double current_time = 0 ;

static double vitesse[3] = {0} ;
static double angle_nord = 0;

// Fonctions d'interface

void adapter_propulsion(int, double, double);

int acquerir_angle_nord();
double get_delta_t();
void acquerir_acceleration(double* acceleration);

//Fonctions usuelles
int isClose(double value, double ref, double marge);

// Pour traiter les données par la suite

static FILE* log_file = NULL;

void setup_log();
void add_log(double*, double*, double*, double*, double, double, double, double, double);
void close_log();

#endif /* defined(__Pilote__simulator__) */
