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

void parseNextInt(int* value, char** it);
void parseNextString(char* string, char **it);

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

    parseNextString(ordre, &current);   
    
    parseNextInt(&(moteur_g.vitesse), &current);
    parseNextInt(&(moteur_g.angle), &current);
    
    parseNextInt(&(moteur_d.vitesse), &current);
    parseNextInt(&(moteur_d.angle), &current);

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

void parseNextInt(int* value, char** it){

  *value = 0 ;

  for(; **it != ';' ; *it+=1){
    *value *= 10 ;
    *value += **it - 48;
  }

  *it += 1 ;
}

void parseNextString(char* string, char **it){

  int i = 0 ;

  for(; **it != ':' ; i++, *it+=1){
    string[i] = **it;
  }
  string[i] = '\0';

  //on quitte le délimiteur
  *it += 1 ;
}

