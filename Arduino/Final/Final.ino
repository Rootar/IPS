#include "Definitions.h"
#include "Engine.h"
#include "Leds.h"
#include "Oled.h"
#include "Serwo.h"

void setup() {
  Serial.begin(115200);       //monitor portu szeregowego
  Serial1.begin(115200);      //port komunikacyjny z RP

  pinMode(A_ENABLE, OUTPUT);  //ustawienie pinów do PWM na output
  pinMode(B_ENABLE, OUTPUT);

  pinMode(A_PHASE, OUTPUT);   //ustawienie pinów do kierunku jazdy na output
  pinMode(B_PHASE, OUTPUT);

  pinMode(MODE, OUTPUT);      //ustawienie pinu rozdzaju sterowania na output
  digitalWrite(MODE, HIGH);   //ustawienie uproszczonego sterowania ;P

  pinMode(LEFT_ENCODER_0, INPUT);         //uruchomienie enkoderóœ
  pinMode(RIGHT_ENCODER_0, INPUT);

  attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER_0), RightCounter, CHANGE);
  attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER_0), LeftCounter, CHANGE);

  

  ServoY(80);

  ServoX(20);
  

  SetLedColor(1);
  Blink();

  String tekst = String("dupa");
  String tekst2 = String("siema");
  Write(tekst);
  delay(2000);
  Write(tekst2);
  
  MovementSpeed(1);
  delay(2000);
  MovementSpeed(3);
  MovementSpeed(0);
  Shot();
}



void loop() {
  SetLedColor(4);
//  
//  MovementSpeed(3);
//  delay(5000);
//  
//  MovementSpeed(2);
//  delay(5000);
//  
//  SetLedColor(2);
//  
//  MovementSpeed(0);
//  delay(1000);
//  
//  MovementSpeed(-1);
  delay(1000);
Shot();
delay(1000);
}
