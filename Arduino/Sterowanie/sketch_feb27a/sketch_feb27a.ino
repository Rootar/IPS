#define A_ENABLE 2  //PWM
#define A_PHASE 22  //0 - przod, 1 - tyl DIGITAL
#define B_ENABLE 3  //PWM
#define B_PHASE 23  //0 - przod, 1 - tyl DIGITAL
#define MODE 30     //sterowanie 0 - ciężkie, 1 - uproszczone DIGITAL
#define LEFT_ENCODER_0 40
#define LEFT_ENCODER_1 41
#define RIGHT_ENCODER_0 42
#define RIGHT_ENCODER_1 43

#define STOP 0
#define SPEED_0 0
#define SPEED_1 100
#define SPEED_2 150
#define SPEED_3 200

#define LEFT_FRONT LOW
#define RIGHT_FRONT HIGH
#define LEFT_BACK HIGH
#define RIGHT_BACK LOW

//enum spe{STOP, SPEED_0 = 0, SPEED_1 = 100, SPEED_2 = 150, SPEED_3 = 200}

int speedInfo;

enum directionEnum{left, right};
directionEnum dir;
//enum class XX {a,b,c};

//XX val = XX::a;

volatile int LeftCount = 0, RightCount = 0;


void LeftCounter(){
  LeftCount--;
}

void RightCounter(){
  RightCount--;
}

void MovSpe(int motorSpeed){
  speedInfo = motorSpeed;
  analogWrite(A_ENABLE, motorSpeed);
  analogWrite(B_ENABLE, motorSpeed);
}

void MovDir(bool leftDir, bool rightDir){
  digitalWrite(A_PHASE, leftDir);
  digitalWrite(B_PHASE, rightDir);
}

void Rotate(int angle){
  if(angle == 0)
    return;

  if(angle > 0)
    dir = left;
  else{
    dir = right;
    angle = -angle;
  }
  LeftCount = angle;
  RightCount = angle;

  if(speedInfo == STOP){
    MovSpe(SPEED_1);
  }

  while(LeftCount > 0 && RightCount > 0)
  {
    if(dir){
      MovDir(LEFT_FRONT, RIGHT_BACK);
    }else{
      MovDir(LEFT_BACK, RIGHT_FRONT);
    }
  }

  MovSpe(STOP);  
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

  MovDir(LEFT_FRONT, RIGHT_FRONT);
  MovSpe(STOP);
  
  pinMode(40, INPUT); // ENCODER RIGHT
  attachInterrupt(digitalPinToInterrupt(40), RightCounter, CHANGE);
  pinMode(42, INPUT); // ENCODER LEFT
  attachInterrupt(digitalPinToInterrupt(42), LeftCounter, CHANGE);
  delay(5000);
}

void loop() {
  MovSpe(SPEED_3);
  Rotate(500);

  delay(50000);
}
