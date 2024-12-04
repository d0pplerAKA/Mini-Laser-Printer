#include <Arduino.h>

#include "JoyStick.h"
#include "Pin.h"


/*
 * No operation range: [535, 625]
 * 
 * X-axis increasing: right (Decreasing: left)
 * Y-axis increasing: up (Decreasing down)
 * 
 * Switch on: 0;
 * Switch off: 1
 */

void joyStatus(void)
{
  int x = getXaxis();
  int y = getYaxis();
  int sw = getSwitch();

  Serial.print("X axis: ");
  Serial.print(getXaxis());
  Serial.println();
  Serial.print("Y axis: ");
  Serial.print(getYaxis());
  Serial.println();
  Serial.print("Switch: ");
  Serial.print(sw);
  Serial.println();
  Serial.println();
}

int getXaxis(void)
{
  int x = 0;

  for(int i = 0; i < 5; i++)
    x = x + analogRead(pinJoyStickX);

  return map(x/5, 0, 8191, -96, 96);
}

int getYaxis(void)
{
  int y = 0;

  for(int i = 0; i < 5; i++)
    y = y + analogRead(pinJoyStickY);

  return map(y/5, 0, 8191, -96, 96);
}

bool getSwitch(void)
{
  if(!digitalRead(pinJoyStickSwitch))
  {
    delayMicroseconds(250);
    if(!digitalRead(pinJoyStickSwitch))
      return false;
  }

  return true;
}
