#include <Arduino.h>

#include "Pin.h"
#include "JoyStick.h"
#include "TFT_Display.h"
#include "img_RenderingData.h"

#define ORDER_WRTIEDATA     0x2c

void pushImage(const unsigned char *temp);

void setup()
{
  pinInit();

  tftInit();

  /*
  Serial.println(ESP.getCpuFreqMHz());
  Serial.println(ESP.getFlashChipSize());
  */
}

void loop()
{
  tftMenu();

  switch(getTftMenu())
  {
    case DISPLAY_WINDOW_NEW_PRINT:
      tftWindowPreNewPrintMission();
      tftWindowNewPrintMission();
      delay(500);
      break;

    case DISPLAY_WINDOW_PRINT_LIB:
      tftMenuPrintLib();
      tftWindowPrintLib(tftGetPrintLibMenu());
      delay(500);
      break;

    case DISPLAY_WINDOW_ABOUT:
      {
        while(1)
        {
          pushImage(uottawa);
          delay(5000);
          pushImage(introduction);
          delay(5000);
          pushImage(ig);
          delay(5000);
          pushImage(breadDog);
          delay(5000);
        }
      }
  }
}

void pushImage(const unsigned char *temp)
{
  tft.fillScreen(TFT_BLACK);
  delayMicroseconds(100);
  tft.writecommand(ORDER_WRTIEDATA);

  for(int i = 0; i < 115200; i++)
  {
    tft.writedata(temp[i]);
  }
}

