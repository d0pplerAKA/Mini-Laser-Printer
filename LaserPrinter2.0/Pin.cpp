#include <Arduino.h>

#include "Pin.h"
#include "Motor.h"
#include "Data_Serial.h"


void pinInit(void)
{  
  Serial.begin(115200);
  Serial.setTimeout(50000);
  clearBuffer();

  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, LOW);

  pinMode(pinLaser, OUTPUT);
  digitalWrite(pinLaser, LOW);

  for(int i = 0; i < 4; i++)
  {
     pinMode(pinMotorA[i], OUTPUT);
     digitalWrite(pinMotorA[i], LOW);
     
     pinMode(pinMotorB[i], OUTPUT);
     digitalWrite(pinMotorB[i], LOW);
  }

  pinMode(pinJoyStickX, INPUT);
  pinMode(pinJoyStickY, INPUT);
  pinMode(pinJoyStickSwitch, INPUT_PULLUP);


  delay(500);

  hintBlink();

  delay(1000);
}

void hintBlink(void)
{
  for(int i = 0; i < 3; i++)
  {
    digitalWrite(pinLed, HIGH);
    delay(100);
    digitalWrite(pinLed, LOW);
    delay(100);
  }
}

void laserOn(void)
{
  digitalWrite(pinLaser, HIGH);
}

void laserOff(void)
{
  digitalWrite(pinLaser, LOW);
}

