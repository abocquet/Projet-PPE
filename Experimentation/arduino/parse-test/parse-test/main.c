#include <stdlib.h>
#include <stdio.h>

typedef struct Moteur Moteur;
struct Moteur
{
	int vitesse ;
	int angle ;
};

char ordre[10];

Moteur parseMoteur(char** pointer){
	
	Moteur moteur ;
	
	moteur.angle = 0 ;
	moteur.vitesse = 0 ;
	
	for(; **pointer != ';' ; *pointer +=1)
	{
		moteur.angle *= 10 ;
		moteur.angle += **pointer - 48;
	}
	
	*pointer += 1 ;

	for(; **pointer != ';' && **pointer != '\0' ; *pointer += 1)
	{
		moteur.vitesse *= 10 ;
		moteur.vitesse += **pointer - 48;
	
	}
	
	*pointer += 1 ;

	return moteur ;
}

void parseOrder(char **pointer)
{
	int i = 0 ;
	
	for(; **pointer != ':' ; i++, *pointer+=1)
	{
		printf("%d %c \n", **pointer, **pointer);
		ordre[i] = **pointer;
	}
	
	ordre[i] = '\0';
	
	//On se place sur le premier chiffre qui vient
	*pointer ++ ;
}


int main(int argc, const char * argv[]) {
	
	char serial[30] = "motor:140;60;180;100" ;
	
	Moteur moteur[2] ;
	
	char *current = serial ;
	
	parseOrder(&current);
	
	//On se place sur le premier chiffre qui vient
	current ++ ;
	
	moteur[0] = parseMoteur(&current);
	moteur[1] = parseMoteur(&current);
	
	printf("Ordre: %s\n", ordre);
	for(int j = 0 ; j < 2 ; j++){
		printf("Moteur %d Vitesse: %d tr/min Angle: %d°\n", j, moteur[j].vitesse, moteur[j].angle);
	}

    return 0;
}
