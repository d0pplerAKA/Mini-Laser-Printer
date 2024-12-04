#include <Arduino.h>

#include "Motor.h"
#include "Pin.h"
#include "TFT_Display.h"


int motorAStep = 0;
int motorBStep = 0;
int pixelY = 0;

/*
 * Please set a certain motor speed with following range:
 * [225, 500]
 * 
 * 270 perfect
 */

int motorSpeed = 2500;
const int motorTempSpeed = 50;

/*
 * Motor X which controls x axis.
 *
 * @dir: bool - Direction of motor
 *       True -> Positive
 * @motorStep: int - Motor Step
 *       Range [0, 100]
 *       Actual range is [0, 97]
 */
void motorA(bool dir, int motorStep)
{
  for(int i = 0; i < motorStep; i++)
    mA(!dir);
}

/*
 * Motor Y which controls x axis.
 *
 * @dir: bool - Direction of motor
 *       True -> Positive
 * @motorStep: int - Motor Step
 *       Range [0, 100]
 *       Actual range is [0, 97]
 */
void motorB(bool dir, int motorStep)
{
  for(int i = 0; i < motorStep; i++)
    mB(!dir);
}

void mA(int motorStatus)
{
  if(motorStatus != -1)
  {
    if(motorStatus)
    {
      motorAPR();

      delayMicroseconds(motorTempSpeed);
    }
    else
    {
      motorANR();

      delayMicroseconds(motorTempSpeed);
    }
  }
  else
    motorAStop();
}

void mB(int motorStatus)
{
  if(motorStatus != -1)
  {
    if(motorStatus)
    {
      motorBPR();

      delayMicroseconds(motorTempSpeed);
    }
    else
    {
      motorBNR();

      delayMicroseconds(motorTempSpeed);
    }
  }
  else
    motorBStop();
}

void motorAPR(void)
{
  for(int i = 0; i < 20; i++)
  {
    for(int j = 0; j < 4; j++)
      digitalWrite(pinMotorA[j], motorStatus[i][j]);

    delayMicroseconds(motorSpeed);
  }
  motorAStep++;
}

void motorANR(void)
{
  for(int i = 19; i >= 0; i--)
  {
    for(int j = 0; j < 4; j++)
      digitalWrite(pinMotorA[j], motorStatus[i][j]);

    delayMicroseconds(motorSpeed);
  }
  motorAStep--;
}

void motorBPR(void)
{
  for(int i = 0; i < 20; i++)
  {
    for(int j = 0; j < 4; j++)
      digitalWrite(pinMotorB[j], motorStatus[i][j]);

    delayMicroseconds(motorSpeed);
  }
  motorBStep++;
}

void motorBNR(void)
{
  for(int i = 19; i >= 0; i--)
  {
    for(int j = 0; j < 4; j++)
      digitalWrite(pinMotorB[j], motorStatus[i][j]);

    delayMicroseconds(motorSpeed);
  }
  motorBStep--;
}

void motorAStop(void)
{
  for(int i = 0; i < 4; i++)
    digitalWrite(pinMotorA[i], LOW);
}

void motorBStop(void)
{
  for(int i = 0; i < 4; i++)
    digitalWrite(pinMotorB[i], LOW);
}

void motorStop(void)
{
  motorAStop();
  motorBStop();
}

void motorReset(void)
{
  int x = motorAStep;
  int y = motorBStep;

  bool tempX = true;
  bool tempY = true;

  if(x == 0)
    tempX = false;
  
  if(y == 0)
    tempY = false;

  if(tempX)
  {
    if(x > 0)
      motorA(0, x);
  }
  
  if(tempY)
  {
    if(y > 0)
      motorB(0, y);
  }

  motorB(0, 96);
}

void prePrinting(void)
{
  motorSpeed = 8000;

  laserOff();

  delay(300);
  laserOn();

  delay(3);

  motorA(1, 96);
  tft.drawLine(22, 22, 218, 22, TFT_WHITE);

  motorB(1, 96);
  tft.drawLine(218, 22, 218, 218, TFT_WHITE);

  motorA(0, 96);
  tft.drawLine(218, 218, 22, 218, TFT_WHITE);

  motorB(0, 96);
  tft.drawLine(22, 218, 22, 22, TFT_WHITE);
  delay(3);

  laserOff();
}

void printingMission_RAM(String lineString)
{ 
  pixelY = 0;

  if(lineCheck_STRING(lineString))
  {
    Serial.println();
    motorSpeed = 3500;
    delay(3);
    motorB(1, 1);
    pixelY++;
  }
  else
  {
    for(int i = 0; i < 97; i++)
    {
      if(lineString.charAt(i) == '1')
      {
        Serial.print("1");
        motorSpeed = 11500;
        laserOn();
        delay(30);
        tftDrawPixel(2*i+X_AXIS_START, 2*pixelY+Y_AXIS_START, TFT_WHITE);
      }
      else
      {
        Serial.print("0");
        motorSpeed = 1800;
        laserOff();
        delay(3);
        tftDrawPixel(2*i+X_AXIS_START, 2*pixelY+Y_AXIS_START, TFT_BLACK);
      }
      motorA(1, 1);
    }

    Serial.println();
    motorSpeed = 1500;
    laserOff();
    delay(3);
    motorA(0, 96);
    motorB(1, 1);
    pixelY++;
    delay(25);
  }

  laserOff();
}

void printingMission_ROM(const byte decodeStr[][97])
{
  prePrinting();

  for(int i = 0; i < 97; i++)
  {
    if(lineCheck_CHAR(decodeStr, i, 96))
    {
      Serial.println();
      motorSpeed = 3500;
      delay(3);
      motorB(1, 1);
      
      continue;
    }
    else
    {
      for(int j = 0; j < 97; j++)
      {
        if(decodeStr[i][j] == '1')
        {
          Serial.print("1");
          motorSpeed = 11500;
          laserOn();
          delay(30);
          tftDrawPixel(j*2 + Y_AXIS_START, i*2 + X_AXIS_START, TFT_WHITE);
        }
        else
        {
          Serial.print("0");
          motorSpeed = 1800;
          laserOff();
          delay(3);
          tftDrawPixel(j*2 + Y_AXIS_START, i*2 + X_AXIS_START, TFT_BLACK);
        }
        
        motorA(1, 1);
      }
    }

    Serial.println();
    motorSpeed = 1500;
    laserOff();
    delay(3);
    motorA(0, 96);
    motorB(1, 1);
    delay(25);
  }

  laserOff();
  motorReset();
}

bool lineCheck_STRING(String str)
{
  for(int i = 0; i < str.length(); i++)
  {
    if(str.charAt(i) == '1')
      return false;    
  }

  return true;
}

bool lineCheck_CHAR(const byte str[][97], int line, int size)
{
  for(int i = 0; i < size; i++)
  {
    if(str[line][i] == '1')
      return false;
  }

  return true;
}

void tftDrawPixel(int32_t x, int32_t y, uint32_t color)
{
  tft.drawPixel(x, y, color);
  tft.drawPixel(x+1, y, color);
  tft.drawPixel(x, y+1, color);
  tft.drawPixel(x+1, y+1, color);
}
