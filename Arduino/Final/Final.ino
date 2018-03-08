#include "Definitions.h"
#include "Engine.h"

void setup() {
  Serial.begin(115200);       //monitor portu szeregowego
  Serial1.begin(115200);      //port komunikacyjny z RP

  pinMode(A_ENABLE, OUTPUT);  //ustawienie pinów do PWM na output
  pinMode(B_ENABLE, OUTPUT);

  pinMode(A_PHASE, OUTPUT);   //ustawienie pinów do kierunku jazdy na output
  pinMode(B_PHASE, OUTPUT);

  pinMode(MODE, OUTPUT);      //ustawienie pinu rozdzaju sterowania na output
  digitalWrite(MODE, HIGH);   //ustawienie uproszczonego sterowania ;P

  pinMode(40, INPUT);         //uruchomienie enkoderóœ
  pinMode(42, INPUT);

  attachInterrupt(digitalPinToInterrupt(40), RightCounter, CHANGE);
  attachInterrupt(digitalPinToInterrupt(42), LeftCounter, CHANGE);

  
}

void loop() {
  // put your main code here, to run repeatedly:
  MovementSpeed(3);
  delay(5000);
  MovementSpeed(2);
  delay(5000);
  MovementSpeed(0);
  delay(1000);
  MovementSpeed(-1);
  delay(3000);
}
