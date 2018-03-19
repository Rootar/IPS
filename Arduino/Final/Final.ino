#include "Definitions.h"
#include "Engine.h"
#include "Leds.h"
#include "Oled.h"
#include "Serwo.h"


void setup() {
  Serial.begin(115200);       //monitor portu szeregowego
  Serial1.begin(115200);      //port komunikacyjny z RP
  Serial2.begin(115200);

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

  //
  //
  //  ServoY(80);
  //
  //  ServoX(20);
  //
  //
  //  SetLedColor(1);
  //  Blink();
  //
  //  String tekst = String("dupa");
  //  String tekst2 = String("siema");
  //  Write(tekst);
  //  delay(2000);
  //  Write(tekst2);
  //
  //  MovementSpeed(1);
  //  delay(2000);
  //  MovementSpeed(3);
  //  MovementSpeed(0);
  //  Shot();

//
//  pinMode(2, OUTPUT);
//  digitalWrite(2, HIGH);
  pinMode(11,OUTPUT);    //ustawienie diód LED w stanie niskim
  digitalWrite(11,LOW);
  
  sendData("AT+RST\r\n", 2000); // reset modułu
  sendData("AT+CWMODE=2\r\n", 1000); // ustawienie w trybie Access Point
  sendData("AT+CIFSR\r\n", 1000); // Uzyskanie adresu IP (domyślnie 192.168.4.1)
  sendData("AT+CIPMUX=1\r\n", 1000); // Tryb połączeń wielokrotnych
  sendData("AT+CIPSERVER=1,80\r\n", 1000); // Ustawienie serwera na porcie 80


}

char dane;

void loop() {
    if(Serial2.available()){
      
      dane = Serial2.read();
      //Serial1.print(dane);
      Serial.print(dane);
    }
    
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

String sendData(String command, const int timeout)
    {
        String response = "";
        
        Serial2.print(command); // wysłanie polecenia do ESP01
        
        long int time = millis();
        
        while( (time+timeout) > millis())
        {
          while(Serial2.available()) //jeśli są jakieś dane z modułu, wtedy następuje ich odczyt
          {
            char c = Serial2.read(); // odczyt kolejnego znaku
            response += c;
          }  
        } 
        Serial.print(response);
        return response;
    }
