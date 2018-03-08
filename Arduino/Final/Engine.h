int LeftCount = 0;
int RightCount = 0;

int actualSpeed = STOP;

void LeftCounter(){
  LeftCount--;
}

void RightCounter(){
  RightCount--;
}

void MovementDirection(bool leftDirection, bool rightDirection){
  digitalWrite(A_PHASE, leftDirection);
  digitalWrite(B_PHASE, rightDirection);
}

void MovementSpeed(int speed){
    if(speed < -1)
        speed = -1;
    if(speed > 3)
        speed = 3;
    
    if(speed < 0)
        MovementDirection(LEFT_BACK, RIGHT_BACK);
    else
        MovementDirection(LEFT_FRONT, RIGHT_FRONT);
    
    switch(speed){
        case -1:
            speed = SPEED_1;
            break;
        case 0:
            speed = STOP;
            break;
        case 1:
            speed = SPEED_1;
            break;
        case 2:
            speed = SPEED_2;
            break;
        case 3:
            speed = SPEED_3;
            break;
    }
    analogWrite(A_ENABLE, speed);
    analogWrite(B_ENABLE, speed);
}

