#include <PCBotRover.h>

PCBotRover bot;

#define rightTrigPin 1
#define rightEchoPin 1
#define leftTrigPin 1
#define leftEchoPin 1

#define MinDistance 10

void setup() 
{
    pinMode(rightTrigPin, OUTPUT);
    pinMode(rightEchoPin, INPUT);
    digitalWrite(rightTrigPin, LOW);

    pinMode(leftTrigPin, OUTPUT);
    pinMode(leftEchoPin, INPUT);
    digitalWrite(leftTrigPin, LOW);
}

void loop() 
{
    double rightDistance = rightSensor();
    double leftDistance = leftSensor();
    
    if(MinDistance>rightDistance && MinDistance>leftDistance && rightDistance<leftDistance)
    {
        bot.motor(BACKWARD,FORWARD);
        delay(1000);
    }
    else if(MinDistance>rightDistance && MinDistance>leftDistance)
    {
        bot.motor(FORWARD,BACKWARD);
        delay(1000);
    }
    else if(MinDistance>rightDistance)
    {
        bot.motor(BACKWARD,FORWARD);
        delay(1000);
    }
    else if(MinDistance>leftDistance)
    {
        bot.motor(FORWARD,BACKWARD);
        delay(1000);
    }
    else
    {
        bot.motor(FORWARD);
    }
    
}

double rightSensor()
{
    digitalWrite(rightTrigPin, HIGH);
    digitalWrite(rightTrigPin, LOW);
    double duration = pulseIn(rightEchoPin, HIGH,1000);
    return duration*0.034/2;
}

double leftSensor()
{
    digitalWrite(leftTrigPin, HIGH);
    digitalWrite(leftTrigPin, LOW);
    double duration = pulseIn(leftEchoPin, HIGH,1000);
    return duration*0.034/2;
}
