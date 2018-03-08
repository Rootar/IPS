#include <LiquidCrystal.h>
#include <RingBuffer.h>
//#include <HardwareSerial.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


#define SERIAL_BUFFER_SIZE 256

void setup() {
  Serial1.begin(115200);
  Serial.begin(115200);
  
  lcd.begin(16, 2);

  //char* tab;
  //tab = (char*)malloc(5);
}

char dane;
int daneInt;
int przelacznik;

void loop() {
  delay(10);
  przelacznik = analogRead(A0);
  
  if(przelacznik > 800){  // na znakach
    
    if(Serial.available() > 0){ //Arduino -> Raspberry
      dane = Serial.read();
      Serial1.write(dane);
    }
  
    if(Serial1.available() > 0){  //Raspberry -> Arduino
      dane = Serial1.read();
      Serial.print(dane);
      lcd.print(dane);
    }  
    
  }else{                  // na intach
  /*
    if(Serial.available() > 0){ //Arduino -> Raspberry
      daneInt = Serial.read();
      Serial1.write(daneInt);
    }
  
    if(Serial1.available() > 0){  //Raspberry -> Arduino
      daneInt = Serial1.read();
      Serial.print(daneInt);
      Serial.print(' ');
      lcd.print(daneInt);
    }
    */
    if(Serial1.available() > 0){
      daneInt = Serial1.read();
      Serial.print(daneInt);
      lcd.print(daneInt);
      Serial1.write(daneInt);
    }
  }
}
