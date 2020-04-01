#include <PCBotRover.h>

PCBotRover bot;

#define threshold 100
#define LDRPin A2

void setup() 
{
    pinMode(LDRPin,INPUT);
    Serial.begin(9600);
}

void loop() 
{
  
    Serial.println(analogRead(LDRPin));
    if(analogRead(LDRPin)>threshold)
    {
        bot.motor(FORWARD,STOP);
    }
    else
    {
        bot.motor(STOP,FORWARD);
    }
    delay(10);
}