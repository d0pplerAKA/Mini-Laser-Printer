#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <string.h>

#include "TFT_Display.h"
#include "Data_Serial.h"
#include "JoyStick.h"
#include "Motor.h"
#include "img_PrintingData.h"

TFT_eSPI tft = TFT_eSPI();


void tftInit(void)
{
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0, 4);

  tft.setTextColor(TFT_WHITE);
  tft.println("Initializing over.");
  tft.setTextColor(TFT_GREEN);
  tft.println("Hello World.");
  tft.println();
  tft.setTextColor(TFT_RED);
  tft.println("Mini Laser Printer.");
  tft.println();

  delay(2500);
}

void tftMenu(void)
{
  tft.fillScreen(TFT_BLACK);
  tft.setRotation(0);

  for(int i = 0; i < 4; i++)
    tft.drawLine(0, 79*i, 239, 79*i, TFT_WHITE);
  
  tft.setCursor(35, 32, 4);
  tft.setTextColor(TFT_GREEN);
  tft.println("New Print Mission");
  tft.fillCircle(16, 38, 5, TFT_GREEN);

  tft.setCursor(35, 112, 4);
  tft.setTextColor(TFT_YELLOW);
  tft.println("Print Library");
  tft.fillCircle(16, 118, 5, TFT_YELLOW);

  tft.setCursor(35, 188, 4);
  tft.setTextColor(TFT_YELLOW);
  tft.println("About this Project");
  tft.fillCircle(16, 196, 5, TFT_YELLOW);
}

void tftMenuRefresh(int sectionState)
{  
  if(sectionState == DISPLAY_WINDOW_NEW_PRINT)
  {
    tft.setCursor(35, 32, 4);
    tft.setTextColor(TFT_GREEN);
    tft.println("New Print Mission");
    tft.fillCircle(16, 38, 5, TFT_GREEN);

    tft.setCursor(35, 112, 4);
    tft.setTextColor(TFT_YELLOW);
    tft.println("Print Library");
    tft.fillCircle(16, 118, 5, TFT_YELLOW);

    tft.setCursor(35, 188, 4);
    tft.setTextColor(TFT_YELLOW);
    tft.println("About this Project");
    tft.fillCircle(16, 196, 5, TFT_YELLOW);
  }
  else if(sectionState == DISPLAY_WINDOW_PRINT_LIB)
  {
    tft.setCursor(35, 32, 4);
    tft.setTextColor(TFT_YELLOW);
    tft.println("New Print Mission");
    tft.fillCircle(16, 38, 5, TFT_YELLOW);

    tft.setCursor(35, 112, 4);
    tft.setTextColor(TFT_GREEN);
    tft.println("Print Library");
    tft.fillCircle(16, 118, 5, TFT_GREEN);

    tft.setCursor(35, 188, 4);
    tft.setTextColor(TFT_YELLOW);
    tft.println("About this Project");
    tft.fillCircle(16, 196, 5, TFT_YELLOW);
  }
  else
  {
    tft.setCursor(35, 32, 4);
    tft.setTextColor(TFT_YELLOW);
    tft.println("New Print Mission");
    tft.fillCircle(16, 38, 5, TFT_YELLOW);

    tft.setCursor(35, 112, 4);
    tft.setTextColor(TFT_YELLOW);
    tft.println("Print Library");
    tft.fillCircle(16, 118, 5, TFT_YELLOW);

    tft.setCursor(35, 188, 4);
    tft.setTextColor(TFT_GREEN);
    tft.println("About this Project");
    tft.fillCircle(16, 196, 5, TFT_GREEN);
  }

}

int getTftMenu(void)
{
  int refreshState = DISPLAY_WINDOW_NEW_PRINT;
  int y = 30;
  bool button = true;

  while(1)
  {
    if(y == 96)
    {
      refreshState--;

      if(refreshState < 0)
        refreshState = DISPLAY_WINDOW_ABOUT;

      tftMenuRefresh(refreshState);
    }

    
    if(y == -96)
    {
      refreshState++;

      if(refreshState > 2)
        refreshState = DISPLAY_WINDOW_NEW_PRINT;

      tftMenuRefresh(refreshState);
    }

    if(!button)
      break;

    delay(300);
    button = getSwitch();
    y = getYaxis();
  }

  return refreshState;
}


void tftWindowPreNewPrintMission(void)
{
  strStatus(getImgData());
}

void tftWindowNewPrintMission(void)
{
  if(proceedPrinting())
  {
    prePrinting();

    for(int i = 0; i < 97; i++)
      printingMission_RAM(decodeStr(dataBuff, i));
    
    motorReset();
    delay(8000);
  }
}

void tftMenuPrintLib(void)
{
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0, 4);
  tft.setTextColor(TFT_SKYBLUE);
  tft.println("Pick from img Lib:");

  tft.setCursor(35, 45, 4);
  tft.setTextColor(TFT_GREEN);
  tft.println("UO Logo");
  tft.fillCircle(16, 52, 5, TFT_GREEN);

  tft.setCursor(35, 75, 4);
  tft.setTextColor(TFT_YELLOW);
  tft.println("UO Telfer Logo");
  tft.fillCircle(16, 82, 5, TFT_YELLOW);

  tft.setCursor(35, 105, 4);
  tft.setTextColor(TFT_YELLOW);
  tft.println("UO GeeGee Logo");
  tft.fillCircle(16, 112, 5, TFT_YELLOW);

  tft.setCursor(35, 135, 4);
  tft.setTextColor(TFT_YELLOW);
  tft.println("Maple Leaf");
  tft.fillCircle(16, 142, 5, TFT_YELLOW);

  tft.setCursor(35, 165, 4);
  tft.setTextColor(TFT_YELLOW);
  tft.println("Fu (Blessing)");
  tft.fillCircle(16, 172, 5, TFT_YELLOW);
}

void tftMenuPrintLibRefresh(int sectionState)
{
  if(sectionState == DISPLAY_LIB_UO_LOGO)
  {
    tft.setCursor(35, 45, 4);
    tft.setTextColor(TFT_GREEN);
    tft.println("UO Logo");
    tft.fillCircle(16, 52, 5, TFT_GREEN);

    tft.setCursor(35, 75, 4);
    tft.setTextColor(TFT_YELLOW);
    tft.println("UO Telfer Logo");
    tft.fillCircle(16, 82, 5, TFT_YELLOW);

    tft.setCursor(35, 105, 4);
    tft.setTextColor(TFT_YELLOW);
    tft.println("UO GeeGee Logo");
    tft.fillCircle(16, 112, 5, TFT_YELLOW);

    tft.setCursor(35, 135, 4);
    tft.setTextColor(TFT_YELLOW);
    tft.println("Maple Leaf");
    tft.fillCircle(16, 142, 5, TFT_YELLOW);

    tft.setCursor(35, 165, 4);
    tft.setTextColor(TFT_YELLOW);
    tft.println("Fu (Blessing)");
    tft.fillCircle(16, 172, 5, TFT_YELLOW);
  }
  else if(sectionState == DISPLAY_LIB_UO_TELFER)
  {
    tft.setCursor(35, 45, 4);
    tft.setTextColor(TFT_YELLOW);
    tft.println("UO Logo");
    tft.fillCircle(16, 52, 5, TFT_YELLOW);

    tft.setCursor(35, 75, 4);
    tft.setTextColor(TFT_GREEN);
    tft.println("UO Telfer Logo");
    tft.fillCircle(16, 82, 5, TFT_GREEN);

    tft.setCursor(35, 105, 4);
    tft.setTextColor(TFT_YELLOW);
    tft.println("UO GeeGee Logo");
    tft.fillCircle(16, 112, 5, TFT_YELLOW);

    tft.setCursor(35, 135, 4);
    tft.setTextColor(TFT_YELLOW);
    tft.println("Maple Leaf");
    tft.fillCircle(16, 142, 5, TFT_YELLOW);

    tft.setCursor(35, 165, 4);
    tft.setTextColor(TFT_YELLOW);
    tft.println("Fu (Blessing)");
    tft.fillCircle(16, 172, 5, TFT_YELLOW);
  }
  else if(sectionState == DISPLAY_LIB_UO_GEE_LOGO)
  {
    tft.setCursor(35, 45, 4);
    tft.setTextColor(TFT_YELLOW);
    tft.println("UO Logo");
    tft.fillCircle(16, 52, 5, TFT_YELLOW);

    tft.setCursor(35, 75, 4);
    tft.setTextColor(TFT_YELLOW);
    tft.println("UO Telfer Logo");
    tft.fillCircle(16, 82, 5, TFT_YELLOW);

    tft.setCursor(35, 105, 4);
    tft.setTextColor(TFT_GREEN);
    tft.println("UO GeeGee Logo");
    tft.fillCircle(16, 112, 5, TFT_GREEN);

    tft.setCursor(35, 135, 4);
    tft.setTextColor(TFT_YELLOW);
    tft.println("Maple Leaf");
    tft.fillCircle(16, 142, 5, TFT_YELLOW);

    tft.setCursor(35, 165, 4);
    tft.setTextColor(TFT_YELLOW);
    tft.println("Fu (Blessing)");
    tft.fillCircle(16, 172, 5, TFT_YELLOW);
  }
  else if(sectionState == DISPLAY_LIB_UO_GEE_HORSE)
  {
    tft.setCursor(35, 45, 4);
    tft.setTextColor(TFT_YELLOW);
    tft.println("UO Logo");
    tft.fillCircle(16, 52, 5, TFT_YELLOW);

    tft.setCursor(35, 75, 4);
    tft.setTextColor(TFT_YELLOW);
    tft.println("UO Telfer Logo");
    tft.fillCircle(16, 82, 5, TFT_YELLOW);

    tft.setCursor(35, 105, 4);
    tft.setTextColor(TFT_YELLOW);
    tft.println("UO GeeGee Logo");
    tft.fillCircle(16, 112, 5, TFT_YELLOW);

    tft.setCursor(35, 135, 4);
    tft.setTextColor(TFT_GREEN);
    tft.println("Maple Leaf");
    tft.fillCircle(16, 142, 5, TFT_GREEN);

    tft.setCursor(35, 165, 4);
    tft.setTextColor(TFT_YELLOW);
    tft.println("Fu (Blessing)");
    tft.fillCircle(16, 172, 5, TFT_YELLOW);    
  }
  else
  {
    tft.setCursor(35, 45, 4);
    tft.setTextColor(TFT_YELLOW);
    tft.println("UO Logo");
    tft.fillCircle(16, 52, 5, TFT_YELLOW);

    tft.setCursor(35, 75, 4);
    tft.setTextColor(TFT_YELLOW);
    tft.println("UO Telfer Logo");
    tft.fillCircle(16, 82, 5, TFT_YELLOW);

    tft.setCursor(35, 105, 4);
    tft.setTextColor(TFT_YELLOW);
    tft.println("UO GeeGee Logo");
    tft.fillCircle(16, 112, 5, TFT_YELLOW);

    tft.setCursor(35, 135, 4);
    tft.setTextColor(TFT_YELLOW);
    tft.println("Maple Leaf");
    tft.fillCircle(16, 142, 5, TFT_YELLOW);

    tft.setCursor(35, 165, 4);
    tft.setTextColor(TFT_GREEN);
    tft.println("Fu (Blessing)");
    tft.fillCircle(16, 172, 5, TFT_GREEN);
  }
}


int tftGetPrintLibMenu(void)
{
    int refreshState = DISPLAY_LIB_UO_LOGO;
    int y = 30;
    bool button = true;
    
    while(1)
    {
      if(y == 96)
      {
        refreshState--;

        if(refreshState < 0)
          refreshState = DISPLAY_LIB_FU;

        tftMenuPrintLibRefresh(refreshState);
      }

      
      if(y == -96)
      {
        refreshState++;

        if(refreshState > 4)
          refreshState = DISPLAY_LIB_UO_LOGO;

        tftMenuPrintLibRefresh(refreshState);
      }

      if(!button)
        break;

      delay(300);
      button = getSwitch();
      y = getYaxis();
    }

  return refreshState;
}

void tftConfirmRefresh(bool sectionState)
{
  tft.setTextColor(TFT_SILVER);

  if(sectionState)
  {
    tft.drawRect(40, 120, 52, 32, TFT_GREEN);
    tft.drawRect(150, 120, 52, 32, TFT_DARKGREY);

    tft.setTextColor(TFT_GREEN);
    tft.drawString("YES", 41, 125, 4);

    tft.setTextColor(TFT_DARKGREY);
    tft.drawString("NO", 158, 125, 4);
  }
  else
  {
    tft.drawRect(40, 120, 52, 32, TFT_DARKGREY);
    tft.drawRect(150, 120, 52, 32, TFT_GREEN);

    tft.setTextColor(TFT_DARKGREY);
    tft.drawString("YES", 41, 125, 4);
    
    tft.setTextColor(TFT_GREEN);
    tft.drawString("NO", 158, 125, 4);
  }
}

void tftWindowPrintLib(int choice)
{
  bool sectionState = true;
  bool button = true;
  int x = 30;

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0, 4);
  tft.setTextColor(TFT_SILVER);
  tft.println("Proceed?\ny/n.");

  tft.drawRect(40, 120, 52, 32, TFT_GREEN);
  tft.drawRect(150, 120, 52, 32, TFT_DARKGREY);

  tft.setTextColor(TFT_GREEN);
  tft.drawString("YES", 41, 125, 4);

  tft.setTextColor(TFT_DARKGREY);
  tft.drawString("NO", 158, 125, 4);

  while(1)
  {
    if(x == 96)
    {
      sectionState = !sectionState;
      tftConfirmRefresh(sectionState);
    }

    if(x == -96)
    {
      sectionState = !sectionState;
      tftConfirmRefresh(sectionState);
    }

    if(!button)
      break;

    delay(300);
    button = getSwitch();
    x = getXaxis();
  }

  if(!sectionState)
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

    return;
  }
  else
  {
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
  }

  switch(choice)
  {
    case DISPLAY_LIB_UO_LOGO:
      printingMission_ROM(dataStr_uoLogo);
      break;
    case DISPLAY_LIB_UO_TELFER:
      printingMission_ROM(dataStr_uoTelfer);
      break;
    case DISPLAY_LIB_UO_GEE_LOGO:
      printingMission_ROM(dataStr_GgLogo);
      break;
    case DISPLAY_LIB_UO_GEE_HORSE:
      printingMission_ROM(dataStr_MapleLeaf);
      break;
    case DISPLAY_LIB_FU:
      printingMission_ROM(dataStr_Fu);
      break;
  }
}
