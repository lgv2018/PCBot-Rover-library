#include <PCBotRover.h>

PCBotRover bot;

void setup() 
{

}

void loop() 
{
    bot.motor(FORWARD);
    delay(500);
    bot.motor(BACKWARD);
    delay(500);
    bot.motor(FORWARD,BACKWARD);
    delay(500);
}
