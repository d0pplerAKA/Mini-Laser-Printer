#ifndef __DATA_SERIAL_H__
#define __DATA_SERIAL_H__

#include <string.h>

extern char dataBuff[11520];

void clearBuffer(void);
uint32_t getImgData(void);
void strStatus(uint32_t data_size);
String decodeStr(char *str, int line);
bool proceedPrinting(void);


#endif
