/*
 * AS_ATCommands.c
 *
 *  Created on: 29 Jan 2020
 *      Author: Tatjana
 */

//This function testing communication

#include "AS7261Sensor/AS_ATCommands.h"
#include "AS7261Sensor/ASMaster.h"
#include <stdlib.h>
#include "AS7261Sensor/StringFunction.h"

UART_HandleTypeDef huart6;

uint8_t AS_Test()//RADI
{
	uint8_t rx_data [6]={0};
	int t=0;
	while(t<3)
	{   //rx_data[0]='\0'; rx_data[1]='\0'; rx_data[2]='\0'; rx_data[3]='\0'; rx_data[4]='\0'; rx_data[5]='\0';
		HAL_Delay(10);
		t++;
		HAL_UART_Transmit(&huart6,(uint8_t*)"AT\r\n",4,100);
		HAL_UART_Receive(&huart6,rx_data,5,100);

		if(strstr((char*)rx_data,"OK"))
			return 1;
	}
	return 0;
}



uint8_t AS_Read_LUX(int *LUX,int *LUX1)
{

		char Rx_data[15]= {0};
		int l=0,l1=0;


			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3|GPIO_PIN_4, GPIO_PIN_SET); //LED ON

			HAL_UART_Transmit(&huart6,(uint8_t*)"ATLUXC\r",7,30); // Read DATA
			HAL_UART_Receive(&huart6,(uint8_t*)Rx_data,14,30);


			ClearSpace(Rx_data);

			DelateOKinMSG(Rx_data);

			ChangeCom(Rx_data);


			sscanf(Rx_data,"%d %d",&l,&l1);

			*LUX=l;
			*LUX1=l1;

			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3|GPIO_PIN_4, GPIO_PIN_RESET);  // LED OFF

			return 1;

}

uint8_t AS_Read_CCT(int *CCT,int *CCT1)
{
	char Rx_data[15]={0};
	int cct=0,cct1=0;


		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3|GPIO_PIN_4, GPIO_PIN_SET); //LED ON

		HAL_UART_Transmit(&huart6,(uint8_t*)"ATCCTC\r",7,30); // Read DATA
		HAL_UART_Receive(&huart6,(uint8_t*)Rx_data,14,30);


		ClearSpace(Rx_data);

		DelateOKinMSG(Rx_data);

		ChangeCom(Rx_data);


		sscanf(Rx_data,"%d %d",&cct,&cct1);

		*CCT=cct;
		*CCT1=cct1;

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3|GPIO_PIN_4, GPIO_PIN_RESET);  // LED OFF

		return 1;

}



uint8_t AS_Set_IntegrationTime(uint8_t Time)//RADI
{
	char Tx_data[15]={0};


			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3|GPIO_PIN_4, GPIO_PIN_SET); //LED ON
			HAL_Delay(50);

			if(Time>=255) Time=255;
			if(Time<=1) Time=1;

			sprintf(Tx_data,"ATINTTIME=%3d\r",(int)Time);

			HAL_UART_Transmit(&huart6,(uint8_t*)Tx_data,14,200); // Send DATA
			HAL_UART_Receive(&huart6,(uint8_t*)Tx_data,10,200); // Clear RXbuffer

			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3|GPIO_PIN_4, GPIO_PIN_RESET);  // LED OFF

			return 1;

}

uint8_t AS_Read_IntegrationTime(uint8_t *Time)//RADI
{
	char Rx_data[15] = {0};


		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3|GPIO_PIN_4, GPIO_PIN_SET); //LED ON
		HAL_Delay(50);

		HAL_UART_Transmit(&huart6,(uint8_t*)"ATINTTIME\r",10,200); // Read DATA
		HAL_UART_Receive(&huart6,(uint8_t*)Rx_data,10,200);

		DelateOKinMSG(Rx_data);  // Clear OK and /r

		(*Time)=(uint8_t)atoi(Rx_data);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3|GPIO_PIN_4, GPIO_PIN_RESET);  // LED OFF

		return 1;

}

uint8_t AS_Set_Gain(uint8_t Gain)//RADI
{
	char Tx_data[15] = {0};


	if(AS_Test())
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3|GPIO_PIN_4, GPIO_PIN_SET); //LED ON
		HAL_Delay(50);

		sprintf(Tx_data,"ATGAIN=%1d\r",(int)Gain);

		HAL_UART_Transmit(&huart6,(uint8_t*)Tx_data,9,200); // Send DATA
		HAL_UART_Receive(&huart6,(uint8_t*)Tx_data,10,200); // Clear RXbuffer

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3|GPIO_PIN_4, GPIO_PIN_RESET);  // LED OFF

		return 1;
	}
	else
		return 0;
}

uint8_t AS_Read_Gain(uint8_t *Gain)//RADI
{
		char Rx_data[15] = {0};



			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3|GPIO_PIN_4, GPIO_PIN_SET); //LED ON
			HAL_Delay(50);

			HAL_UART_Transmit(&huart6,(uint8_t*)"ATGAIN\r",7,200); // Read DATA
			HAL_UART_Receive(&huart6,(uint8_t*)Rx_data,10,200);

			DelateOKinMSG(Rx_data);  // Clear OK and /r

			(*Gain)=(uint8_t)atoi(Rx_data);

			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3|GPIO_PIN_4, GPIO_PIN_RESET);  // LED OFF

			return 1;

}






