#include "Definitions.h"
#include "Engine.h"
#include "Leds.h"
#include "Oled.h"
#include "Serwo.h"
#include "Wifi.h"


void setup() {
  Serial.begin(115200);       //monitor portu szeregowego
  Serial1.begin(115200);      //port komunikacyjny z RP
  Serial2.begin(115200);      //WiFi

  Engine();
  Leds();
  Oled();
  Wifi();
  
  
}

char dane;
String danes;
int command, value;


void loop() {
//    if(false)
//    if(Serial2.available()){
//      
//      dane = Serial2.read();
//      //Serial1.print(dane);
//      Serial.print(dane);
//    }
//    
//  if(false)
//  if(Serial2.available()){
//    Serial2.find("asdasd");
//    danes = Serial2.read();
//    Serial.print(danes);
//  }
  
//  if(false)
  if(Serial2.available()){
    if(Serial2.find("+IPD")){
      delay(10);

      Serial2.find("COM:");
      command = Serial2.read() - 48;
      dane = Serial2.read();
      value = Serial2.read() - 48;
      
      switch(command){
        case 1:
          Serial.println("+=DIR=+");
          if(value == 1){
            MovementDirection(LEFT_FRONT, RIGHT_FRONT);
            MovementSpeed(actualSpeed);
          }
          if(value == 2){
            MovementDirection(LEFT_BACK, RIGHT_FRONT);
            MovementSpeed(actualSpeed);
          }
          if(value == 3){
            MovementDirection(LEFT_FRONT, RIGHT_BACK);
            MovementSpeed(actualSpeed);
          }
          if(value == 4){
            MovementDirection(LEFT_BACK, RIGHT_BACK);
            MovementSpeed(actualSpeed);
          }
          if(value == 5)
            MovementSpeed(0);
            //MovementDirection(LEFT_FRONT, RIGHT_FRONT);            
          break;
          
        case 2:
          Serial.println("+=SPEED=+");
          MovementSpeed(value);
          actualSpeed = value;
          break;
          
        case 3:
          Serial.println("+=COLOR=+");
          SetLedColor(value);
          break;

        case 4:
          Serial.println("+=BLINK=+");
          Blink();
          break;

        case 5:
          Serial.println("+=TEXT=+");
          danes = Serial2.read();
          Write(danes);
          break;
          
        case 6:
          Serial.println("+=TOWER=+");
          if(value == 1){
            angleY += 5;
            ServoY(angleY);
          }
          if(value == 2){
            angleX += 5;
            ServoX(angleX);
          }
          if(value == 3){
            angleX -= 5;
            ServoX(angleX);
          }
          if(value == 4){
            angleY -= 5;
            ServoY(angleY);
          }
          break;
          
        case 7:
          Serial.println("+=SHOT=+");
          Shot();
          break;

        default:
          Serial.println("+=default=+");
      }
    }
  }




  
//    if(Serial2.available()){
//      
//      dane = Serial2.read();
//      //Serial1.print(dane);
//      Serial.print(dane);
//    }

    
    
//    if(Serial.available()){
//      dane = Serial.read();
//      Serial2.print(dane);
//    }
    
//  if(Serial2.available()) // sprawdzenie czy moduł otzrymał dane 
//      {
//        if(Serial2.find("+IPD,"))
//        {
////         delay(1000); // czekanie na zapełnienie bufora danymi
//         
//         // odczytanie ID połączenia
//         int connectionId = Serial2.read()-48; // odjęcie 48 ponieważ funkcja read() zwraca wartość dziesiętną ASCII na pozycji 48
//              
//         Serial2.find("pin="); // wyszukanie frazy "pin=" oraz ustawienie tam "kursora"
//         
//         int pinNumber = (Serial2.read()-48)*10; // pobranie pierwszej cyfry, np. dla pinu 13, pierwsza cyfra to 1, należy ją pomnożyć przez 10
//         pinNumber += (Serial2.read()-48); // pobranie drugiej cyfry, np. dla pinu 13, druga cyfra to 3, należy ją dodać do poprzedniego wyniku
//         
//         //digitalWrite(pinNumber, !digitalRead(pinNumber)); // zmiana stanu wybranego pinu    
//         Serial.print(pinNumber);
//         // zamknięcie połączenia
//         String closeCommand = "AT+CIPCLOSE="; 
//         closeCommand+=connectionId; // ID połączenia odczytane na początku
//         closeCommand+="\r\n";
//         
//         sendData(closeCommand,1000); 
//        }
//      }

}


