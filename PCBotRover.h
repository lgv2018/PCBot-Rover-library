
#ifndef  PCBotRover_h
#define  PCBotRover_h

#if ARDUINO >= 100
    #include <Arduino.h>
#else
    #include <WProgram.h>
    #include <wiring.h>
#endif

/*  // add this later
#ifndef  POSISION_PID
    #define  POSISION_PID False
#endif
#ifndef  SPEED_PID
    #define  SPEED_PID False
#endif
*/


#define  FORWARD 255
#define  STOP 0
#define  BACKWARD -255
#define  SpotRotationCount 100

#define  RightMotorPinA 6
#define  RightMotorPinB 11
#define  LeftMotorPinA 9
#define  LeftMotorPinB 10


#define  RightLedPin 0
#define  LeftLedPin 1

#define  RightPhotoInterrupterPin 3
#define  LeftPhotoInterrupterPin 2
#define  RightPhotoPin 14
#define  LeftPhotoPin 15

#define PulsePerRotation 2

class  PCBotRover
{
    public:
        // SETUP 
        PCBotRover();

        void setMotor(int Leftspeed,int Rightspeed);

        // Set motors
        void motor(int Leftspeed,int Rightspeed); // value between -255 and 255 for speed and direction
        void motor(int LeftAndRightspeed); // value between -255 and 255 for speed and direction
        void rightMotor(int speed); // value between -255 and 255 for speed and direction
        void leftMotor(int speed); // value between -255 and 255 for speed and direction
        void stop();

        // Move motors
        void move(int LeftPosition,int RightPosition); 
        void move(int LeftAndRightPosition);
        void moveRight(int Position);
        void moveLeft(int Position);
        /*void moveToMotor(int LeftPosition,int RightPosition); 
        void moveToMotor(int LeftAndRightPosition);
        void moveToRightMotor(int Position);
        void moveToLeftMotor(int Position);*/

        // Motor Fuctions
        /*void turnLeft();
        void turnRight();
        void turn(int degrees);*/

        long rightCount=0;
        long leftCount=0;
        double rightSpeed=0;
        double leftSpeed=0;

        
        void (*rightInterrupt) ();
        void (*leftInterrupt) ();
        
    private: //maybe protected:
        long rightToCount=0;
        long leftToCount=0;

        int rightMotorSpeed=0;
        int leftMotorSpeed=0;
        
        unsigned long rightLastTime=0;
        unsigned long leftLastTime=0;

        //interupts
        static PCBotRover* _deviceForInterrupt;
        static void RightInterruptDispatch();
        static void LeftInterruptDispatch();
        void RightInt();
        void LeftInt();

        bool positionMode=false;
};

#endif 
