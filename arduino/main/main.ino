#define BUFFER_LENGTH 25

typedef struct Moteur Moteur;
struct Moteur
{
  int vitesse ;
  int angle ;
  int pin ;
};

Moteur moteur_g ;
Moteur moteur_d ;

char ordre[10] ;

void parseMoteur(Moteur* moteur, char** pointer);
void parseOrder(char **pointer);

void setup() {

  moteur_g.pin = 5 ;
  moteur_d.pin = 6 ;

  pinMode(moteur_g.pin, OUTPUT);
  pinMode(moteur_d.pin, OUTPUT);
  Serial.begin(9600);
  Serial.println("READY");
}

void loop() {

  if(Serial.available() > 0){

    char received[BUFFER_LENGTH] ;

    Serial.readBytes(received, BUFFER_LENGTH);
    char* current = received ;

    parseOrder(&current);     
    parseMoteur(&moteur_g, &current);
    parseMoteur(&moteur_d, &current);

    Serial.print("Ok, a gauche, vitesse de ");
    Serial.print(moteur_g.vitesse);
    Serial.print("/255 et moteurs inclines de ");
    Serial.print(moteur_g.angle);
    Serial.print(" degres. ");

    Serial.print("A droite, vitesse de ");
    Serial.print(moteur_d.vitesse);
    Serial.print("/255 et moteurs inclines de ");
    Serial.print(moteur_d.angle);
    Serial.println(" degres.");

    analogWrite(moteur_g.pin, moteur_g.vitesse);
    analogWrite(moteur_d.pin, moteur_d.vitesse);
  }
}

void parseMoteur(Moteur* moteur, char** pointer){

  moteur->angle = 0 ;
  moteur->vitesse = 0 ;

  for(; **pointer != ';' ; *pointer+=1){
    moteur->vitesse *= 10 ;
    moteur->vitesse += **pointer - 48;
  }

  *pointer += 1 ;

  for(; **pointer != ';' ; *pointer+=1){
    moteur->angle *= 10 ;
    moteur->angle += **pointer - 48;
  }

  moteur->vitesse *= 2.55 ;

  //on se place sur le chiffre suivante
  *pointer += 1 ;
}

void parseOrder(char **pointer){

  int i = 0 ;

  for(; **pointer != ':' ; i++, *pointer+=1){
    ordre[i] = **pointer;
  }
  ordre[i] = '\0';

  //On se place sur le premier chiffre qui vient
  *pointer += 1 ;
}

