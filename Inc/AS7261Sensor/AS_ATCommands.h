/*
 * AS_ATCommands.h
 *
 *  Created on: 1 Dec 2018
 *      Author: Bozic
 */

#ifndef AS7261SENSOR_AS_ATCOMMANDS_H_
#define AS7261SENSOR_AS_ATCOMMANDS_H_

#include "stm32f7xx_hal.h"
#include "STMPE610.h"
#include "SSD1963.h"
#include "GUI.h"
#include <stdint.h>
#include "string.h"


// This Functions are AT commands for sensor AS7261 (Mikroelektronika)

//typedef char uint8_t;
extern UART_HandleTypeDef huart6;


// All function return !=0 if function successful complete , otherwise return 0

// Calibrated Data
uint8_t AS_Read_XYZ(int *X,int *X1,int *Y,int *Y1,int *Z,int *Z1);
uint8_t AS_Read_LUX(int *LUX,int *LUX1);
uint8_t AS_Read_CCT(int *CCT,int *CCT1);
uint8_t AS_Read_SMAllxy(int *x,int *x1, int *y, int *y1);
uint8_t AS_Read_Up_Vp_U_V(float *Up,float *Vp,float *U,float *V);
uint8_t AS_READ_DUV(float *DUV);

// Raw Data
uint8_t AS_Read_XYZ_RAW(float *X,float *Y,float *Z);
uint8_t AS_Read_AllData_RAW(int *X,int *Y,int *Z,int *NIR,int *D,int *C);

//Sensor Configuration
uint8_t AS_Set_IntegrationTime(uint8_t Time);
uint8_t AS_Read_IntegrationTime(uint8_t *Time);
uint8_t AS_Set_Gain(uint8_t Gain);
uint8_t AS_Read_Gain(uint8_t *Gain);
uint8_t AS_Read_Temp(float *Temp);
uint8_t AS_Set_SensorMode(uint8_t Mode);
uint8_t AS_Read_SensorMode(uint8_t *Mode);
uint8_t AS_Set_SemplingInterval(uint8_t SemplingInterval);
uint8_t AS_Read_SemplingInterval(uint8_t *SemplingInterval);
uint8_t AS_Set_BURST(uint8_t BRST);


//LED driver
uint8_t AS_Set_LED_Indicate(uint8_t ONOFF);
uint8_t AS_Read_LED_Indicate(uint8_t *ONOFF);
uint8_t AS_Set_LED_DRV(uint8_t ONOFF);
uint8_t AS_Read_LED_DRV(uint8_t *ONOFF);
uint8_t AS_Set_LEDCurrent(uint8_t Current);
uint8_t AS_Read_LEDCurrent(uint8_t *CurrentLed0, uint8_t *CurrentLed1);

//General function
uint8_t AS_Test();
uint8_t AS_Reset();
uint8_t AS_VersionSS(uint8_t *Ver);
uint8_t AS_VersionSH(uint8_t *Ver);

//Firmware update
uint8_t AS_FirmwareInic(uint16_t Checksum);
uint8_t AS_FirmwareDownload(uint16_t Checksum);
uint8_t AS_FirmwareFWUpdate();
uint8_t AS_FirmwareWSUpdate();




#endif /* AS7261SENSOR_AS_ATCOMMANDS_H_ */
