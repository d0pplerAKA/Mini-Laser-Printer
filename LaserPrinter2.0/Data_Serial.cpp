#include <Arduino.h>
#include <string.h>

#include "TFT_eSPI.h"
#include "Data_Serial.h"
#include "TFT_Display.h"
#include "Pin.h"

#define END_SIGN '&'

char dataBuff[11520];

void clearBuffer(void)
{
  while(Serial.read()>=0){}
}

uint32_t getImgData(void)
{
  uint32_t data_size = 0;
  char temp;
  bool flag = true;
  bool tempFlag = true;

  for(int i = 0; i < 11520; i++)
    dataBuff[i] = 0;

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0, 2);
  tft.setTextColor(TFT_WHITE);
  tft.println("Waiting for data transmission");

  clearBuffer();

  while(flag)
  {
    while(tempFlag)
    {      
      while(Serial.available() > 0)
      {
        temp = char(Serial.read());

        if(data_size == 0)
        {
          tft.setTextColor(TFT_YELLOW);
          tft.println("Receiving");
        }

        if(temp == END_SIGN)
        {
          tft.setTextColor(TFT_GREEN);
          tft.println("\nDone");

          clearBuffer();

          tempFlag = false;
          
          break;
        }
        else
        {
          dataBuff[data_size] = temp;
          data_size++;
        }
      }
    }

    while(1)
    {
      char a;

      tft.setTextFont(2);
      tft.setTextColor(TFT_GREENYELLOW);
      tft.println("\nNeed to correct image data? y/n");
      clearBuffer();

      while(1)
      {
        if(Serial.available() > 0)
        {
          a = Serial.read();
          break;
        }
      }

      tft.printf("%c\n", a);
      delay(1250);

      if(a == 'y')
      {
        tft.fillScreen(TFT_BLACK);
        tft.setCursor(0, 0, 2);
        tft.setTextColor(TFT_WHITE);
        tft.println("Waiting for data transmission");

        /*_*/
        clearBuffer();
        tempFlag = true;
        data_size = 0;

        break;
      }
      else
      {
        flag = false;

        break;
      }
    }
  }

  return data_size;
}

void strStatus(uint32_t data_size)
{
  tft.setTextColor(TFT_GREENYELLOW);
  tft.print("\nGot a string that has a total \nlength of ");
  tft.setTextColor(TFT_SKYBLUE);
  tft.printf("%d", data_size);
  tft.setTextColor(TFT_GREENYELLOW);
  tft.print("\n\nThat takes up ");
  tft.setTextColor(TFT_SKYBLUE);
  tft.printf("%.2f", (float(data_size) / 1024));
  tft.setTextColor(TFT_GREENYELLOW);
  tft.print("KB of the SRAM");

  delay(2500);
}

String decodeStr(char *str, int line)
{
  int index = 0;
  String strData = "";

  for(unsigned int i = (line * 96); i < ((line * 96) + 96); i++)
  {
    strData = strData + str[i];
    index++;
  }

  return strData;
}

bool proceedPrinting(void)
{
  char a;

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0, 2);
  tft.setTextColor(TFT_GREENYELLOW);
  tft.println("Proceed printing mission? y/n");

  clearBuffer();

  while(1)
  {
    if(Serial.available() > 0)
    {
      a = Serial.read();
      break;
    }
  }


  tft.printf("%c\n", a);
  delay(1250);

  if(a != 'y')
  {
    tft.setTextFont(2);
    tft.setTextColor(TFT_WHITE);
    tft.print("\nProgramme terminated... ");

    unsigned int x = tft.getCursorX();
    unsigned int y = tft.getCursorY();

    tft.drawString("3", x, y);
    delay(1150);
    tft.setTextColor(TFT_BLACK);
    tft.drawString("3", x, y);

    tft.setTextColor(TFT_WHITE);
    tft.drawString("2", x, y);
    delay(1000);
    tft.setTextColor(TFT_BLACK);
    tft.drawString("2", x, y);

    tft.setTextColor(TFT_WHITE);
    tft.drawString("1", x, y);
    delay(1000);
    tft.setTextColor(TFT_BLACK);
    tft.drawString("1", x, y);


    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 0);
    return false;
  }

  tft.setTextFont(2);
  tft.setTextColor(TFT_WHITE);
  tft.print("\nProceeding printing mission in... ");

  unsigned int x = tft.getCursorX();
  unsigned int y = tft.getCursorY();

  tft.drawString("3", x, y);
  delay(1150);
  tft.setTextColor(TFT_BLACK);
  tft.drawString("3", x, y);

  tft.setTextColor(TFT_WHITE);
  tft.drawString("2", x, y);
  delay(1000);
  tft.setTextColor(TFT_BLACK);
  tft.drawString("2", x, y);

  tft.setTextColor(TFT_WHITE);
  tft.drawString("1", x, y);
  delay(1000);
  tft.setTextColor(TFT_BLACK);
  tft.drawString("1", x, y);

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0);


  return true;
}

