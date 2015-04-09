#define BUFFER_LENGTH 25
#define VITESSE_PIN 3
#define SENS_PIN 2
#define WATCHDOG_PIN 15

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
    Serial.println(sens);


    analogWrite(VITESSE_PIN, vitesse);
    digitalWrite(SENS_PIN, sens);
  }

  digitalWrite(WATCHDOG_PIN, true);
  delay(100);
  digitalWrite(WATCHDOG_PIN, false);

  while(boucle == 1){
    digitalWrite(WATCHDOG_PIN, true);
    delay(1000);
    digitalWrite(WATCHDOG_PIN, false);
    delay(1000);
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



