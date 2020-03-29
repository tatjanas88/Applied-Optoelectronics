/*
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++... * ASMaster.c
 *
 *  Created on: 29 Jan 2020
 *      Author: tatjana
 */

#include "AS7261Sensor/ASMaster.h"

#include "AS7261Sensor/AS_Windows/TestDLG.h"
#include "AS7261Sensor/AS_Windows/Kolorimetrija.h"
#include <stdlib.h>

int keyPressed=100;
int ConnectOK=0;
WM_HWIN hWin;
int i=0;
//float Temperatura=0;
char TempMsg[5]={0};
char temp[30];
int m;
char h[5];
uint8_t IntTime;

int LUXceo=0,LUXdec=0;
int CCTceo=0,CCTdec=0;
uint8_t g=0;


uint8_t LEDind=0,LedDrv=0,LEDSet=0,LED0Read=0,LED1Read=0;


void Merenja()
{

	AS_Read_CCT(&CCTceo,&CCTdec);
	AS_Read_LUX(&LUXceo,&LUXdec);

	sprintf(TempMsg, "%d,%d",CCTceo,CCTdec);
	PROGBAR_SetValue(WM_GetDialogItem(hWin, ID_PROGBAR_0),CCTceo);
	EDIT_SetText(WM_GetDialogItem(hWin, ID_EDIT_0), TempMsg);


	sprintf(TempMsg, "%d,%d",LUXceo,LUXdec);
	PROGBAR_SetValue(WM_GetDialogItem(hWin, ID_PROGBAR_1),LUXceo);
	EDIT_SetText(WM_GetDialogItem(hWin, ID_EDIT_1), TempMsg);


	GUI_Exec();
}

void IntegrationTime()
{
	//STMPE610_read_xyz();
    //GUI_TOUCH_Exec();

	int nn = SLIDER_GetValue(WM_GetDialogItem(hWin, ID_SLIDER_0));
	sprintf(h,"%3d",nn);
	AS_Set_IntegrationTime(nn);
	EDIT_SetText(WM_GetDialogItem(hWin, ID_EDIT_2), h);
	GUI_Exec();


}
void Gain()
{
	//uint8_t ReadGain;
	uint8_t NumforSet;


		switch(DROPDOWN_GetSel(WM_GetDialogItem(hWin,ID_DROPDOWN_0)))
		{
		case 0: NumforSet=0;
		    sprintf(TempMsg, "%1d",(int)NumforSet);
		    EDIT_SetText(WM_GetDialogItem(hWin, ID_EDIT_3), "1X");
			AS_Set_Gain(NumforSet);
			GUI_Exec();
            break;
		case 1: NumforSet=1;
			 sprintf(TempMsg, "%1d",(int)NumforSet);
		 	 EDIT_SetText(WM_GetDialogItem(hWin, ID_EDIT_3), "3.7X");
			AS_Set_Gain(NumforSet);
			GUI_Exec();
		break;
		case 2: NumforSet=2;
			 sprintf(TempMsg, "%1d",(int)NumforSet);
			 EDIT_SetText(WM_GetDialogItem(hWin, ID_EDIT_3), "16X");
			 AS_Set_Gain(NumforSet);
			 GUI_Exec();
		break;
		case 3: NumforSet=3;
			sprintf(TempMsg, "%1d",(int)NumforSet);
			EDIT_SetText(WM_GetDialogItem(hWin, ID_EDIT_3), "64X");
			AS_Set_Gain(NumforSet);
			GUI_Exec();
		break;
		default: break;
		}
	}

void AS7261_Sensor() //test conn
{
	    int n=0;

		hWin = CreateTest();  //Kreiraj pocetni ekran -test

		GUI_Exec();
		//GUI_Delay(10);


		do{

		  STMPE610_read_xyz();
		  GUI_TOUCH_Exec();
		  keyPressed=GUI_GetKey();

		  if(keyPressed==ID_BUTTON_0)
			{
				i=0;
				while(i<30)
					{
						i++;
						PROGBAR_SetValue(WM_GetDialogItem(hWin,ID_PROGBAR_START),i);
						PROGBAR_SetText(WM_GetDialogItem(hWin,ID_PROGBAR_START), "Loading...");
						GUI_Exec();
						HAL_Delay(10);
					}

				ConnectOK=AS_Test();


				while(i<100)
					{
						i++;
						PROGBAR_SetValue(WM_GetDialogItem(hWin,ID_PROGBAR_START),i);
						GUI_Exec();
						HAL_Delay(20);
					}
				if(ConnectOK)
				{	PROGBAR_SetText(WM_GetDialogItem(hWin,ID_PROGBAR_START), "Successful! :)");
					EDIT_SetTextColor(WM_GetDialogItem(hWin, ID_EDIT_START),EDIT_CI_ENABLED,GUI_MAKE_COLOR(0x00E10011));
					EDIT_SetText(WM_GetDialogItem(hWin, ID_EDIT_START), "CONNECTION OK!");
					EDIT_SetTextAlign(WM_GetDialogItem(hWin, ID_EDIT_START), GUI_TA_HCENTER|GUI_TA_VCENTER);

					GUI_Exec();
					n=1;

				}
				else
				{
					PROGBAR_SetText(WM_GetDialogItem(hWin,ID_PROGBAR_START), ":(");
					EDIT_SetTextColor(WM_GetDialogItem(hWin, ID_EDIT_START),EDIT_CI_ENABLED,GUI_MAKE_COLOR(0x000000F4));
					EDIT_SetText(WM_GetDialogItem(hWin, ID_EDIT_START), "CONNECTION FAILED!");
					EDIT_SetTextAlign(WM_GetDialogItem(hWin, ID_EDIT_START), GUI_TA_HCENTER|GUI_TA_VCENTER);

					GUI_Exec();
				}

			}

			  GUI_Delay(10);

		  }while(n!=1);

		GUI_Delay(1000);
		GUI_Clear();

		hWin = CreateKolorimetrija();
		GUI_Exec();

		//STMPE610_read_xyz();
	    //GUI_TOUCH_Exec();
		AS_Read_IntegrationTime(&IntTime);
		sprintf(TempMsg, "%3d",(int)IntTime);
		EDIT_SetText(WM_GetDialogItem(hWin, ID_EDIT_2), TempMsg);
		SLIDER_SetValue(WM_GetDialogItem(hWin, ID_SLIDER_0),IntTime);
	    DROPDOWN_SetColor(WM_GetDialogItem(hWin,ID_DROPDOWN_0), DROPDOWN_CI_BUTTON,GUI_MAKE_COLOR(0x000000F4));
	    DROPDOWN_SetColor(WM_GetDialogItem(hWin,ID_DROPDOWN_0),DROPDOWN_CI_ARROW, GUI_MAKE_COLOR(0x00E10011));
	    SLIDER_SetWidth(WM_GetDialogItem(hWin,ID_SLIDER_0),20);
	    SLIDER_SetRange(WM_GetDialogItem(hWin,ID_SLIDER_0),1,255);
	    EDIT_SetTextAlign(WM_GetDialogItem(hWin,ID_EDIT_0), GUI_TA_HCENTER |GUI_TA_VCENTER );
	    EDIT_SetBkColor(WM_GetDialogItem(hWin,ID_EDIT_0), EDIT_CI_ENABLED, GUI_MAKE_COLOR(0xF1C232));
	    EDIT_SetTextAlign(WM_GetDialogItem(hWin,ID_EDIT_1), GUI_TA_HCENTER |GUI_TA_VCENTER );
	    EDIT_SetBkColor(WM_GetDialogItem(hWin,ID_EDIT_1), EDIT_CI_ENABLED, GUI_MAKE_COLOR(0xF1C232));
	    EDIT_SetTextAlign(WM_GetDialogItem(hWin,ID_EDIT_2), GUI_TA_HCENTER |GUI_TA_VCENTER);
	    EDIT_SetBkColor(WM_GetDialogItem(hWin,ID_EDIT_2), EDIT_CI_ENABLED, GUI_MAKE_COLOR(0xF1C232));
	    EDIT_SetTextAlign(WM_GetDialogItem(hWin,ID_EDIT_3), GUI_TA_HCENTER |GUI_TA_VCENTER);
	    EDIT_SetBkColor(WM_GetDialogItem(hWin,ID_EDIT_3), EDIT_CI_ENABLED, GUI_MAKE_COLOR(0xF1C232));
	    PROGBAR_SetMinMax(WM_GetDialogItem(hWin,ID_PROGBAR_0),2000,8000);
	    PROGBAR_SetMinMax(WM_GetDialogItem(hWin,ID_PROGBAR_1),40,3500);
		GUI_Exec();


		//GUI_Delay(10);
		while(1)
		{

		STMPE610_read_xyz();
	    GUI_TOUCH_Exec();

	    IntegrationTime();
	    GUI_Delay(10);
	    Merenja();
	    Gain();

		}
}
//}

