/**********************************************************************************************
 * Arduino PCBotRover Library - Version 1.0
 * by William Bailes <williambailes@gmail.com> http://tinkersprojects.com/
 *
 * This Library is licensed under a GPLv3 License
 **********************************************************************************************/

#include "PCBotRover.h"

#if ARDUINO >= 100
  #include "Arduino.h"
#else
    #include <WProgram.h>
    #include <wiring.h>
#endif


PCBotRover* PCBotRover::_deviceForInterrupt = 0;

/******************* SETUP *******************/

 PCBotRover:: PCBotRover()
{
  pinMode(LeftMotorPinA, OUTPUT);
  pinMode(LeftMotorPinB, OUTPUT);
  pinMode(RightMotorPinA, OUTPUT);
  pinMode(RightMotorPinB, OUTPUT);
 /* pinMode(RightLedPin, OUTPUT);
  pinMode(LeftLedPin, OUTPUT);
  digitalWrite(RightLedPin, LOW);
  digitalWrite(LeftLedPin, LOW);*/
  pinMode (LeftPhotoPin, INPUT);
  pinMode (RightPhotoPin, INPUT);

  _deviceForInterrupt = this;

  attachInterrupt(digitalPinToInterrupt(RightPhotoInterrupterPin), RightInterruptDispatch, RISING);
  attachInterrupt(digitalPinToInterrupt(LeftPhotoInterrupterPin), LeftInterruptDispatch, RISING);  

  //timer0 maybe but coul be problematic, timer0 controls the millis()...
}




void PCBotRover::setMotor(int Leftspeed,int Rightspeed)
{
  if(Leftspeed>0)
  {
    analogWrite(LeftMotorPinA, abs(Leftspeed));
    digitalWrite(LeftMotorPinB, LOW);
  }
  else
  {
    analogWrite(LeftMotorPinB, abs(Leftspeed));
    digitalWrite(LeftMotorPinA, LOW);
  }

  if(Rightspeed>0)
  {
    analogWrite(RightMotorPinA, abs(Rightspeed));
    digitalWrite(RightMotorPinB, LOW);
  }
  else
  {
    analogWrite(RightMotorPinB, abs(Rightspeed));
    digitalWrite(RightMotorPinA, LOW);
  }
  rightMotorSpeed=Rightspeed;
  leftMotorSpeed=Leftspeed;
}




void PCBotRover::motor(int Leftspeed,int Rightspeed)
{
  this->setMotor(Leftspeed,Rightspeed);
  positionMode=false;
  //rightCount=0;
  //leftCount=0;
}

void PCBotRover::motor(int LeftAndRightspeed)
{
  this->motor(LeftAndRightspeed,LeftAndRightspeed);
}

void PCBotRover::rightMotor(int speed)
{
  this->motor(leftMotorSpeed,speed);
}

void PCBotRover::leftMotor(int speed)
{
  this->motor(speed,rightMotorSpeed);
}


void PCBotRover::stop()
{
  this->motor(0,0);
}






void PCBotRover::move(int LeftPosition,int RightPosition)
{
  leftCount = 0;
  rightCount = 0;
  leftToCount = LeftPosition;
  rightToCount = RightPosition;
  setMotor(255,255);
}
 
void PCBotRover::move(int LeftAndRightPosition)
{
  this->move(LeftAndRightPosition,LeftAndRightPosition);
}

void PCBotRover::moveRight(int Position)
{
  if(positionMode)
    this->move(rightToCount,Position);
  else
    this->move(rightCount,Position);
}

void PCBotRover::moveLeft(int Position)
{
  if(positionMode)
    this->move(Position,leftToCount);
  else
    this->move(Position,leftCount);
}



/*
void PCBotRover::moveToMotor(int LeftPosition,int RightPosition)
{
  positionMode=true;
  rightToCount = RightPosition;
  leftToCount = LeftPosition;

  leftMotorSpeed=255;
  rightMotorSpeed=255;
  if(rightCount>rightToCount)
  rightMotorSpeed = -rightMotorSpeed;
  if(leftCount>leftToCount)
  leftMotorSpeed = -leftMotorSpeed;
  this->setMotor(leftMotorSpeed,rightMotorSpeed);
}

void PCBotRover::moveToMotor(int LeftAndRightPosition)
{
  this->moveToMotor(LeftAndRightPosition,LeftAndRightPosition);
}

void PCBotRover::moveToRightMotor(int Position)
{
  if(positionMode)
    this->moveToMotor(rightToCount,Position);
  else
    this->moveToMotor(rightCount,Position);
}

void PCBotRover::moveToLeftMotor(int Position)
{
  if(positionMode)
    this->moveToMotor(Position,leftToCount);
  else
    this->moveToMotor(Position,leftCount);
}
*/







/*
void PCBotRover::turnLeft()
{
  this->turn(90);
}

void PCBotRover::turnRight()
{
  this->turn(-90);
}

void PCBotRover::turn(int degrees)
{
  float circlePpercent= degrees/360;
  double position = SpotRotationCount*circlePpercent;
  this->moveMotor((int)position,(int)(-1*position));
}
*/






void PCBotRover::RightInterruptDispatch() 
{
  if (_deviceForInterrupt)
    _deviceForInterrupt->RightInt();
}

void PCBotRover::LeftInterruptDispatch() 
{
  if (_deviceForInterrupt)
    _deviceForInterrupt->LeftInt();
}

void PCBotRover::RightInt()
{
  unsigned long difference = millis()-rightLastTime;
  rightLastTime = millis();
  rightSpeed = 60000/(difference*PulsePerRotation); // OLD: 1/(difference/1000*PulsePerRotation)*60;

  rightCount++;

  if(positionMode && rightCount>=rightToCount)
  {
    this->setMotor(leftMotorSpeed,STOP);
  }

  if(rightInterrupt != NULL)
    rightInterrupt();
}

void PCBotRover::LeftInt()
{
  
  unsigned long difference = millis()-leftLastTime;
  leftLastTime = millis();
  leftSpeed = 60000/(difference*PulsePerRotation); // OLD: 1/(difference/1000*PulsePerRotation)*60;

  leftCount++;

  if(positionMode && leftCount>=leftToCount)
  {
    this->setMotor(STOP,rightMotorSpeed);
  }
  
  if(leftInterrupt != NULL)
    leftInterrupt();
}