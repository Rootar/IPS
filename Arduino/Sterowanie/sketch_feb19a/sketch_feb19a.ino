#define A_ENABLE 2  //PWM
#define A_PHASE 22  //0 - przod, 1 - tyl
#define B_ENABLE 3  //PWM
#define B_PHASE 23  //0 - przod, 1 - tyl
#define MODE 30     //sterowanie 0 - ciężkie, 1 - uproszczone
#define LEFT_ENCODER_0 40
#define LEFT_ENCODER_1 41
#define RIGHT_ENCODER_0 42
#define RIGHT_ENCODER_1 43

volatile int licznik = 0, licznikTemp = 0, velocity = 0;
volatile unsigned long last_measurement;
void counter() {
  licznik++;
  licznikTemp++;
  if (last_measurement + 1000 <= millis()) {
    last_measurement = millis();
    velocity = licznikTemp;
    licznikTemp = 0;
  }
}

void setup() {
  Serial.begin(115200);   //monitor portu szeregowego
  Serial1.begin(115200);  //port komunikacyjny z RP


  pinMode(A_ENABLE, OUTPUT);  //ustawienie pinów do PWM na output
  pinMode(B_ENABLE, OUTPUT);

  pinMode(A_PHASE, OUTPUT);   //ustawienie pinów do kierunku jazdy na output
  pinMode(B_PHASE, OUTPUT);

  pinMode(MODE, OUTPUT);      //ustawienie pinu rozdzaju sterowania na output
  digitalWrite(MODE, HIGH);   //ustawienie uproszczonego sterowania ;P

  digitalWrite(A_PHASE, LOW); //ustawienie na poczatek jazdy do przodu
  digitalWrite(B_PHASE, HIGH);

  analogWrite(A_ENABLE, 60);   //wylaczenie domyslnie silnikow
  analogWrite(B_ENABLE, 60);

  
  pinMode(44, INPUT); // 44 = USOUND_ECHO
  attachInterrupt(digitalPinToInterrupt(44), counter, CHANGE);
}

String dane;
int predkosc;

void loop() {
  if (Serial.available() > 0) {
    dane = Serial.readString();

    if (dane == "LF")         //lewa(A) do przodu
      digitalWrite(A_PHASE, LOW);
    if (dane == "RF")         //prawa(B) do przodu
      digitalWrite(B_PHASE, HIGH);

    if (dane == "LB")         //lewa(A) do tyłu
      digitalWrite(A_PHASE, HIGH);
    if (dane == "RB")         //prawa(B) do tyłu
      digitalWrite(B_PHASE, LOW);

    if (dane == "LS") {
      Serial.print("podaj predkosc\n");

      while (Serial.available() == 0);

      dane = Serial.readString();
      predkosc = dane.toInt();
      Serial.print(predkosc);
      analogWrite(A_ENABLE, predkosc);
    }
    if (dane == "RS") {
      Serial.print("podaj predkosc\n");

      while (Serial.available() == 0);

      dane = Serial.readString();
      predkosc = dane.toInt();
      Serial.print(predkosc);
      analogWrite(B_ENABLE, predkosc);
    }
  }




  //  if(Serial1.available() > 0){
  //    dane = Serial1.read();
  //    Serial.print(dane);
  //  }
  //Serial.print("licznik = %d\tpredkosc = %d\n");

  char buf[32];
  sprintf(buf, "i=%d; vel=%.2f RPM\n", licznik, (float)velocity * 60.0f / (1000.0f / 5.0f));
  Serial.print(buf);
  delay(250);
}

//zrobić funkcję do odbierania danych od raspberki
