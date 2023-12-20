#include "ds1307.h"


// Decimal to BCD converter
uint8_t decToBcd(uint32_t val){
	
  return (uint8_t)( (val/10*16) + (val%10) );
}
//BCD to Decimal Convereter
uint32_t bcdToDec(uint8_t val){
  return (int)( (val/16*10) + (val%16) );
}
// function to set time
void Set_Time (uint8_t sec, uint8_t min, uint8_t hour, uint8_t dow, uint8_t dom, uint8_t month, uint8_t year){
	
	uint8_t set_time[7];
	
	set_time[0] = decToBcd(sec);
	set_time[1] = decToBcd(min);
	set_time[2] = decToBcd(hour);
	set_time[3] = decToBcd(dow);
	set_time[4] = decToBcd(dom);
	set_time[5] = decToBcd(month);
	set_time[6] = decToBcd(year);

	HAL_I2C_Mem_Write(&hi2c1, DS3231_ADDRESS, 0x00, 1, set_time, 7, 1000);
}

uint8_t* getTime (void){
	static uint8_t get_time[7];
	HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDRESS, 0x00, 1, get_time, 7, 1000);
	return get_time;
}

