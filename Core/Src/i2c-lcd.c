
/** Put this in the src folder **/

#include "i2c-lcd.h"

extern I2C_HandleTypeDef hi2c1;  // change your handler here accordingly


static uint16_t lcdType;

void lcd16SetCusor(uint8_t col, uint8_t row);
void lcd20SetCusor(uint8_t col, uint8_t row);
void lcd_init(void);

/* */
void lcd_send_cmd(char cmd){
 char upperNibble, lowerNibble;
	uint8_t lcdData[4];
	upperNibble = (cmd&0xf0);
	lowerNibble = ((cmd<<4)&0xf0);
	lcdData[0] = upperNibble|0x0C;   //en=1, rw=0, rs=0 - 0b00001100
	lcdData[1] = upperNibble|0x08;  //en=0, rw=0, rs=0	- 0b00001000
	lcdData[2] = lowerNibble|0x0C;  //en=1, rw=0, rs=0	-	0b00001100
	lcdData[3] = lowerNibble|0x08;  //en=0, rw=0, rs=0	-	0b00001000
	HAL_I2C_Master_Transmit (&hi2c1, I2C_ADDR,(uint8_t *) lcdData, 4, 100);
}

/* */
void lcd_send_data(char data){
  char upperNibble, lowerNibble;
	uint8_t lcdData[4];
	upperNibble = (data&0xf0);
	lowerNibble = ((data<<4)&0xf0);
	lcdData[0] = upperNibble|0x0D;  //en=1, rw=0, rs=1	-	0b00001101
	lcdData[1] = upperNibble|0x09;  //en=0, rw=0, rs=1	-	0b00001001
	lcdData[2] = lowerNibble|0x0D;  //en=1, rw=0, rs=1	-	0b00001101
	lcdData[3] = lowerNibble|0x09;  //en=0, rw=0, rs=1	-	0b00001001
	HAL_I2C_Master_Transmit (&hi2c1, I2C_ADDR,(uint8_t *) lcdData, 4, 100);
}

/* */
void lcd_clear (void){
	
	lcd_send_cmd (0x01);
	HAL_Delay(500);
}

/* */
void lcd16SetCusor(uint8_t col, uint8_t row){
  
	if (row == 0 && col<16)
	lcd_send_cmd((col & 0x0F)|0x80);	
	else if (row == 1 && col<16)
	lcd_send_cmd((col & 0x0F)|0xC0);
}

/* */
void lcd20SetCusor(uint8_t col, uint8_t row){
  
	if (row == 0 && col<20)
	lcd_send_cmd((col & 0x0F)|0x80);	
	else if (row == 1 && col<20)
	lcd_send_cmd((col & 0x0F)|0xC0);
	else if (row == 2 && col<20)
	lcd_send_cmd((col & 0x0F)|0x94);	
	else if (row == 3 && col<20)
	lcd_send_cmd((col & 0x0F)|0xD4);
	else{}
}

/* */
void lcdSetCusor(uint8_t col, uint8_t row){
	
  if(lcdType == 2004){
	lcd20SetCusor(col, row);
	}else if(lcdType == 1602){
	lcd16SetCusor(col, row);
	}else{}
}

/* */
void lcd_init(void){
	
	lcd_send_cmd (0x30);
	HAL_Delay(5);  // wait for >4.1ms
	lcd_send_cmd (0x30);
	HAL_Delay(1);  // wait for >100us
	lcd_send_cmd (0x30);
	HAL_Delay(10);
	lcd_send_cmd (0x20);  // 4bit mode
	HAL_Delay(10);

	lcd_send_cmd (0x28); 
	HAL_Delay(1);
	lcd_send_cmd (0x08); 
	HAL_Delay(1);
	lcd_send_cmd (0x01);  // clear display
	HAL_Delay(1);
	lcd_send_cmd (0x06); 
	HAL_Delay(1);
	lcd_send_cmd (0x0C); 
	HAL_Delay(1);
	lcd_send_cmd (0x80); 
}

/* */
void lcdInit(uint8_t col, uint8_t row){
	
	if((col == 20) && (row == 4)){
		lcdType = 2004;
		lcd_init();
	}		
	else if((col == 16) && (row == 2)){
		lcdType = 1602;
		lcd_init();
	}
	else{}
}

/* */
void lcd_send_string (char *str){
	
	int i;
	for(i = 0; str[i] != 0; i++){		/* Send each char of str till its empty*/
		lcd_send_data(str[i]);
	}
}
