#ifndef __TFT_DISPLAY_H__
#define __TFT_DISPLAY_H__

#include <TFT_eSPI.h>

#define DISPLAY_WINDOW_NEW_PRINT    0
#define DISPLAY_WINDOW_PRINT_LIB    1
#define DISPLAY_WINDOW_ABOUT        2

#define DISPLAY_LIB_UO_LOGO         0
#define DISPLAY_LIB_UO_TELFER       1
#define DISPLAY_LIB_UO_GEE_LOGO     2
#define DISPLAY_LIB_UO_GEE_HORSE    3
#define DISPLAY_LIB_FU              4

#define DISPLAY_ABOUT_QRCODE        0
#define DISPLAY_ABOUT_INS           1

extern TFT_eSPI tft;

void tftInit(void);


void tftMenu(void);
void tftMenuRefresh(int sectionState);
int getTftMenu(void);

void tftWindowPreNewPrintMission(void);
void tftWindowNewPrintMission(void);

void tftMenuPrintLib(void);
void tftMenuPrintLibRefresh(int sectionState);
int tftGetPrintLibMenu(void);

void tftWindowPrintLib(int choice);
void tftConfirmRefresh(bool sectionState);


#endif
