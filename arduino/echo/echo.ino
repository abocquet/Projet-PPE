const int ledPin = 11;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("READY");
}

void loop() {

  if(Serial.available())
  {
    while (Serial.available()) {
      digitalWrite(ledPin, HIGH);
      Serial.write(Serial.read());
    }
    Serial.write('\n');
  }

  delay(100);
  digitalWrite(ledPin, LOW);
}
