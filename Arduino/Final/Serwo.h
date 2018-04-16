#include <Servo.h>

Servo serwo1;
Servo serwo2;

int angleX = 90;
int angleY = 90;

//=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0
void ServoX(int angle){
  if(angle < 0)
    angle = 0;
  if(angle > 180)
    angle = 180;
    
  serwo1.attach(SERVO_X);
  serwo1.write(angle);

  delay(500);
  
  if(serwo1.attached())
    serwo1.detach();
}


//=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0
void ServoY(int angle){
  if(angle < 0)
    angle = 0;
  if(angle > 180)
    angle = 180;
    
  serwo2.attach(SERVO_Y);
  serwo2.write(angle);

  delay(500);
  
  if(serwo2.attached())
    serwo2.detach();
}

