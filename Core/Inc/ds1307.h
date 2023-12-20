#ifndef __DS1307_H_
#define __DS1307_H_

#include <stdint.h>
#include "stm32f4xx.h"

#define DS3231_ADDRESS 0xD0 //RTC address
extern I2C_HandleTypeDef hi2c1;  // change your handler here accordingly


void Set_Time(uint8_t sec, uint8_t min, uint8_t hour, uint8_t dow, uint8_t dom, uint8_t month, uint8_t year);
uint8_t* getTime(void);
uint32_t bcdToDec(uint8_t val);

#endif
