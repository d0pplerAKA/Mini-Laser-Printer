#ifndef __PIN_H__
#define __PIN_H__

const static int pinMotorA[] = {GPIO_NUM_33, GPIO_NUM_21, GPIO_NUM_20, GPIO_NUM_19};
const int pinMotorB[] = {GPIO_NUM_15, GPIO_NUM_16, GPIO_NUM_17, GPIO_NUM_18};

#define pinLaser GPIO_NUM_1
#define pinLed GPIO_NUM_2
#define pinJoyStickX GPIO_NUM_4
#define pinJoyStickY GPIO_NUM_5
#define pinJoyStickSwitch GPIO_NUM_3

/*
#define pinSDA GPIO_NUM_8
#define pinSCL GPIO_NUM_9
*/

/*

#define TFT_CS   10 //     10 or 34
#define TFT_MOSI 11 //     11 or 35
#define TFT_SCLK 12 //     12 or 36
#define TFT_MISO 13 //     13 or 37

#define TFT_BL   3           // LED back-light control pin
#define TFT_DC   4
#define TFT_RST  5

#define TOUCH_CS 6     // Chip select pin (T_CS) of touch screen

*/

void pinInit(void);
void hintBlink(void);
void laserOn(void);
void laserOff(void);

#endif
