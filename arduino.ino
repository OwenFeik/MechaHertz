#include "RB_Motor.h"

char inChar; //most recent character from Serial
String inStr; //current input recorded from serial
int bx,by; //ball's position
int g1x,g1y; //position of a goal
int g2x,g2y; //postion of other goal 
int *xpos,*ypos; //used to reference a set of coordinates


Motor motorFrontLeft(10,11,100);
Motor motorFrontRight(9,3,100);
Motor motorBackLeft(5,6,100);
Motor motorBackRight(0,0,100);

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN,OUTPUT);
}

void loop() {

  //Process inStr
  if(Serial.available()){
    inChar=Serial.read();

    if (inChar == 'b'){
      xpos = &bx; ypos = &by;
      inStr="";
    }
    else if (inChar == 'g'){
      xpos = &g1x; ypos = &g1y;
      inStr="";
    }
    else if (inChar == 'h'){
      xpos = &g2x; ypos = &g2y;
      inStr="";
    }
    else if (inChar=='x'){
      *xpos=inStr.toInt();
      inStr="";
    }
    else if (inChar=='y'){
      *ypos=inStr.toInt();
      inStr="";
    }
    else if (inChar=='s'){
      turnRight();
      delay(500);
      stopAll();
    }
    else if (inChar=='d'){
     turnLeft();
     delay(500);
     stopAll(); 
    }
    else {
      inStr+=inChar;
    }
  }


  if (bx>40 and bx<60){
    stopAll();
  }  
  else if (bx>=50){
    turnRight();
    digitalWrite(LED_BUILTIN,HIGH);
  }
  else if (bx<=49){
    turnLeft();
    digitalWrite(LED_BUILTIN,LOW);
  }
}

void goForward(){
  motorFrontLeft.drive(100);
  motorFrontRight.drive(-100);
  motorBackLeft.drive(100);
  motorBackRight.drive(-100);
}
void turnRight(){
  motorFrontLeft.drive(100);
  motorFrontRight.drive(100);
  motorBackLeft.drive(100);
  motorBackRight.drive(100);
}
void turnLeft(){
  motorFrontLeft.drive(-100);
  motorFrontRight.drive(-100);
  motorBackLeft.drive(-100);
  motorBackRight.drive(-100);
}
void stopAll(){
  motorFrontLeft.stop();
  motorFrontRight.stop();
  motorBackLeft.stop();
  motorBackRight.stop();
}

