#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial1.begin(115200);
  Serial.begin(115200);
  
  lcd.begin(16, 2);

  char* tab;

  tab = (char*)malloc(5);
}

char dane;

void loop() {
  if(Serial.available() > 0){
    dane = Serial.read();
    Serial1.write(dane);
  }

  if(Serial1.available() > 0){
    dane = Serial1.read();
    Serial.print(dane);
    lcd.print(dane);
  }  
}
