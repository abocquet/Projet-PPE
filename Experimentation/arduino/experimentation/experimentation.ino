#define BUFFER_LENGTH 25
#define VITESSE_PIN 3
#define SENS_PIN 2
#define WATCHDOG_PIN 8

char ordre[10] ;

void parseNextInt(int* value, char** it);
void parseNextString(char* string, char **it);

int vitesse = 0 ;
int sens = 0 ;
int boucle = 0 ;

void setup() {

  pinMode(VITESSE_PIN, OUTPUT);
  pinMode(SENS_PIN, OUTPUT);
  pinMode(WATCHDOG_PIN, OUTPUT);

  Serial.begin(9600);
  Serial.println("READY");
}

void loop() {

  if(Serial.available() > 0){

    char received[BUFFER_LENGTH] ;

    Serial.readBytes(received, BUFFER_LENGTH);
    char* current = received ;

    parseNextInt(&vitesse, &current);
    parseNextInt(&sens, &current);
    parseNextInt(&boucle, &current);

    Serial.print("Ok, vitesse de ");
    Serial.print(vitesse);
    Serial.print("/255 et sens ");
    Serial.print(sens);
    Serial.print(" (blocage: ");
    Serial.print(boucle);
    Serial.print(")");
    Serial.print('\n');

    analogWrite(VITESSE_PIN, 0);
    delay(100);

    analogWrite(VITESSE_PIN, vitesse);
    digitalWrite(SENS_PIN, sens == 1 ? HIGH : LOW);
  }

  digitalWrite(WATCHDOG_PIN, HIGH);
  delay(100);
  digitalWrite(WATCHDOG_PIN, LOW);

  if(boucle == 1) {
    Serial.println("Good bye ...");
    delay(15000); //Simule un blocage du controleur
    Serial.println("... here I am !");
    
    boucle = 0 ;
  }

  /*while(boucle == 1){
    //On ne fait plus rien, la carte est bloquee
    // (simulation de disfonctionnement)
  }*/

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



