#ifndef __MOTOR_H__
#define __MOTOR_H__

#define X_AXIS_START 24
#define Y_AXIS_START 24

#define X_AXIS_END 216
#define Y_AXIS_END 216

extern int motorAStep;
extern int motorBStep;

const int motorStatus[20][4] = {{1, 0, 0, 1}, {1, 0, 0, 1}, {1, 0, 0, 1}, {1, 0, 0, 0}, {1, 0, 0, 0}, 
                                {1, 0, 1, 0}, {1, 0, 1, 0}, {1, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, 
                                {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, 
                                {0, 1, 0, 1}, {0, 1, 0, 1}, {0, 1, 0, 1}, {0, 0 ,0, 1}, {0, 0 ,0, 1}};


void motorA(bool dir, int motorStep);
void motorB(bool dir, int motorStep);


void mA(int motorStatus);
void mB(int motorStatus);
void motorAPR(void);
void motorANR(void);
void motorBPR(void);
void motorBNR(void);
void motorAStop(void);
void motorBStop(void);
void motorStop(void);
void motorReset(void);

void prePrinting(void);

void printingMission_RAM(String lineString);
void printingMission_ROM(const byte decodeStr[][97]);

bool lineCheck_STRING(String str);
bool lineCheck_CHAR(const byte str[][97], int line, int size);

void tftDrawPixel(int32_t x, int32_t y, uint32_t color);

#endif
