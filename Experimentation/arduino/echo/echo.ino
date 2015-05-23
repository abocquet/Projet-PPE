#include <string.h>
#define MAX_ORDER_LENGTH 50

const int motor_g = 6 ;
const int motor_d = 5 ;

double speed_g = 50 ;
double speed_d = 50 ;

void setup() {
  pinMode(motor_g, OUTPUT);
  pinMode(motor_d, OUTPUT);
  Serial.begin(9600);
  Serial.println("READY");
}

void loop() {

  if(Serial.available() > 0)
  {
    double tmp = Serial.parseInt();

    while(Serial.available()){ 
      Serial.read(); 
    }

    if(tmp <= 100 && tmp >= 0){
      speed_g = tmp * 2.55 ;
      speed_d = tmp*2.55;
      Serial.println(speed_g);
    }

    analogWrite(motor_g, speed_g);
    analogWrite(motor_d, speed_d);
  }

}




