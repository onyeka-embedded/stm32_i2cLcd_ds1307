#ifndef __LCD_H_
#define __LCD_H_

#include <stdint.h>
#include "stm32f4xx.h"

#define I2C_ADDR (0x27<<1U) // I2C address of the PCF8574


void ms_Delay(uint16_t delay);
void lcd_send_cmd(char cmd);
void lcd_send_data(char data);
void lcdInit(uint8_t col, uint8_t row);
void lcdSetCusor(uint8_t row, uint8_t col);
void lcd_send_string (char *str);
void lcd_clear(void);

#endif
